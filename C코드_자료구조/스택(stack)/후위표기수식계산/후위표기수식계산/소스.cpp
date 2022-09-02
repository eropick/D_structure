#define _CRT_SECURE_NO_WARNINGS
#include "myStack.h"
#include <string.h>
#include <ctype.h>
int eval(char exp[]);

int main(int argc, char* argv[]) {
	//atoi사용해서 문자열을 숫자로 변환 후 스택에 쌓음.
	char p[100];
	char* pf;
	printf("후위표기식은?: ");
	scanf("%[^\n]s", p);
	printf("결과값은? %d\n",eval(p));
	return 0;
}

int eval(char exp[]) {
	int op1, op2,rlen,value=0;
	char ch;
	StackType s;
	init_stack(&s);
	rlen = strlen(exp);
	for (int i = 0; i < rlen;) {
		ch=exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ',' && ch != ' ') { //연산자나 공백이나 ,가 아니라면 스택에 넣는다.
			if (!isdigit(ch)) { //숫자 문자가 아닌경우 오류.
				fprintf(stderr, "에러: 숫자가 아닌 값이 들어옴.\n");
				return 0;
			}
			value = atoi(exp+i); //문자열 숫자 값을 정수형 숫자로 변환
			push(&s, value);
			while (exp[i] != '\0') { //널문자가 나오면 반복 종료
				++i;
				if (!isdigit(exp[i])) break; //숫자 문자가 나오지 않는다면 증가 취소
			}
		}
		else if (ch == ' ' || ch == ',') ++i; //공백이나 ,가 들어가는 경우 i값만 1증가시킴.
		else { //연산자가 들어오는 경우
			op1 = pop(&s);
			op2 = pop(&s);
			switch (ch) {
				case '+':
					push(&s, op2 + op1);
					break;
				case '-':
					push(&s, op2 - op1);
					break;
				case '*':
					push(&s, op2 * op1);
					break;
				case '/':
					push(&s, op2 / op1);
					break;
			}
			++i;
		}
	}
	return pop(&s);
}