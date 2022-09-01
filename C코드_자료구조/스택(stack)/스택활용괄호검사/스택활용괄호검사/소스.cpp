#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0


typedef char element; //char타입
typedef int boolean; //불타입
typedef struct _StackType {
	element* data; //스택의 포인터를 할당.
	int capacity;
	int top;
}StackType;

void init_stack(StackType* s); //스택 초기화
boolean is_empty(StackType* s); //스택 비어있는지 검사
boolean is_full(StackType* s); //스택 가득차 있는지 검사
void push(StackType* s, element item); //push
element pop(StackType* s); //pop
element peek(StackType* s); //peek
boolean check_matching(char* in); //문자열을 파라미터로 받음.


int main(int argc, char* argv[]) {
	char p[100];
	printf("문자열 입력: ");
	gets_s(p, sizeof(p));
	if(check_matching(p)==TRUE)	printf("%s 괄호 검사 성공\n",p);
	else printf("%s 괄호 검사 실패\n", p);
	return 0;
}

void init_stack(StackType* s) {
	s->capacity = 1;
	s->top = -1; //아무것도 없는 빈스택
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

boolean is_empty(StackType* s) {
	return (s->top == -1);
	//참이면 true,거짓이면 false 반환
}

boolean is_full(StackType* s) {
	return (s->top == (s->capacity - 1));
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		s->capacity *= 2; //capacity의 크기를 두배 늘림.
		if (s->capacity >= MAX_STACK_SIZE) {
			fprintf(stderr, "최대 스택: 더 이상 스택을 추가할 수 없음.\n");
			return; //이 함수만 종료
		}
		else s->data = (element*)realloc(s->data, s->capacity * sizeof(element)); //재할당
	}
	s->data[++(s->top)] = item;
}
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1); //프로세스 종료
		//exit(0)의 경우 정상종료시, exit(1)의 경우 에러로 인한 종료시 파라미터는 반환값.
	}
	else return s->data[(s->top)--]; //값 반환 후 top-1
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

boolean check_matching(char* in) {
	StackType s;
	init_stack(&s); //스택 초기화
	int rlen = strlen(in); //문자열 길이 반환.
	char ch,ch_pop; //임시 문자변수
	for (int i = 0; i < rlen; ++i) {//반복
		ch = in[i];
		switch (ch) {
			case '(': case '{': case '[': //왼쪽 괄호 나오면 스택에 넣음
				push(&s, ch);
				break;
			case ')': case '}': case ']': //오른쪽 괄호가 나오는 경우
				//오른쪽 괄호가 나오면 스택이 비었는지 확인 후 비었으면 실패
				if (is_empty(&s)) return FALSE;
				else { //만약 비어있지 않으면 POP을 통해 ch_pop과 ch를 비교해서 같은 쌍이 아니면 실패
					ch_pop = pop(&s); //스택에서 하나를 반환(왼쪽괄호)
					if ((ch_pop == '(' && ch != ')') ||
						(ch_pop == '{' && ch != '}') ||
						(ch_pop == '[' && ch != ']')
						) return FALSE;
					//같은 쌍이 존재하지 않으면 false
				}
				break;
			default:
				break;
		}
	}
	//루프를 다 돌렸는데 스택이 비어있지 않으면 오류.
	if (is_empty(&s)) return TRUE;
	else return FALSE;
	//루프 돌리는데 오류로 종료되지 않고 스택도 비어있다면 정상
}