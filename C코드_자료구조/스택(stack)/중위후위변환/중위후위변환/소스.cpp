#define _CRT_SECURE_NO_WARNINGS
#include "postfixop.h" //후위수식 계산 함수
#include "my_stack.h" //스택

void in_post(char* in,char* post); //중위 수식을 후위수식으로 변환
int op_priority(char op); //우선순위를 구한다.

int main(int argc, char** argv) {
	char infix[100];
	char* postfix;
	printf("중위 수식 입력: ");
	scanf("%[^\n]s", infix);
	postfix = (char*)calloc(strlen(infix) * 2 , sizeof(char));
	in_post(infix, postfix);
	printf("후위수식: %s\n", postfix);
	printf("계산결과: %d\n", eval(postfix));
	free(postfix);
	return 0;
}

void in_post(char* in, char* post) {
	int rlen = strlen(in);
	int p = -1; //post 포인터
	char ch;
	StackType op;
	init_stack(&op); //스택 초기화.'
	//(40+5)/9
	for (int i = 0; i < rlen;) {
		ch = in[i];
		switch (ch) {
			// ex)3*4+1 => 34*1+
			// ex)3-4+1 => 34-1+
			case '+':case '-':case '*':case '/': //연산자인 경우 
				while (!is_empty(&op) && (op_priority(peek(&op)) >= op_priority(ch))) { 
					//기본적으로 가장 마지막에 스캔된 값이 먼저 출력되어야 한다. 그러기 위해선 우선순위가 커야한다.
					//스택에 있는 우선순위가 더 크거나 같다면 먼저 출력해야 하기 때문에 다 pop해준다. 
					//우선순위가 같은경우는 앞에 온 게 먼저 계산되는 우선순위를 갖기 때문에
					//스택이 비어있거나 ch 우선순위가 더 클 경우 스택에 계속 쌓게 된다. 
					post[++p]=pop(&op); //pop후 후위수식배열에 넣음.
				}
				push(&op, ch); //push
				++i;
				break;
			case '(': //왼쪽 괄호의 경우 일단 쌓는다.
				//어차피 우선순위가 제일 낮아서 위에 수식에서도 ch가 더 커지기 때문에 괄호 위에 쌓이게 된다.
				push(&op, ch); //스택에 쌓음.
				++i;
				break;
			case ')': //오른쪽 괄호의 경우
				while (peek(&op) != '(') {
					//peek가 (가 될 때까지 
					post[++p] = pop(&op); //pop후 후위수식배열에 넣음.
				}
				//peek가 (이 되면 
				pop(&op);
				++i;
				break;;
			default: //피연산자인 경우 후위수식에 계속 넣음.
				if (p >= 0 && isdigit(post[p])) { //이전값이 피연산자라면 ,를 할당
					post[++p] = ',';
				}//이전 값이 숫자 문자였다면 ,를 붙여줌.
				while (in[i] != '\0') {
					post[++p] = in[i];
					++i;
					if (!isdigit(in[i])) break; //숫자가 아니면 빠져나옴
				}
				break;
		}
	}
	//마지막에는 스택에 남아있는 모든 연산자를 쏟아냄.
	while (!is_empty(&op)) post[++p] = pop(&op);
	post[++p] = '\0'; //마지막에는 널문자로 마무리 함.
}


int op_priority(char op) { //우선순위 반환
	switch (op) {
		case '(': case ')':
			return 0;
		case '+': case '-':
			return 1;
		case '*': case '/':
			return 2;
	}
	return -1;
}