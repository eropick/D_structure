#include<stdio.h>
#define MAX_STACK_SIZE 100
#define MAX_STRING 100
#define TRUE (1)
#define FALSE (0)

//스택의 정보가 여러개가 있을 경우 구조체를 생성한다.
//예를들어 군인의 정보라고 해보자.
typedef struct _element {
	char name[MAX_STRING];
	char rank[MAX_STRING];
	int m_num;
}element;
typedef int boolean;
int top = -1;
element stack[MAX_STACK_SIZE];

void push(element item); //요소를 입력한다.
element pop(); //요소를 제거 후 반환한다.
element peek(); //요소를 반환한다.
void print_stack(); //현재 스택에 있는 요소들을 출력한다.
boolean is_full(); //현재 스택이 가득차 있는지를 판단한다. 
boolean is_empty(); //현재 스택의 요소가 비어있는지를 판단한다.

int main(int argc, char* argv[]) {
	element kim = { "kimbap","private",20284 };
	element lee = { "leebalso","private firstclass",10284 };
	element kim2;
	push(kim);
	push(lee);
	print_stack();
	pop();
	kim2 = pop();
	push(lee);
	push(kim2);
	print_stack();
	return 0;
}

boolean is_full() {
	if (top >= MAX_STACK_SIZE) return TRUE; //가득 차 있으면
	else return FALSE;
}
boolean is_empty() {
	if (top < 0) return TRUE; //인덱스 -1이면
	else return FALSE;
}

void push(element item) {
	if (is_full()) fprintf(stderr,"Err!! StackOver\n");
	else stack[++top] = item; //top을 1증가시킨 인덱스에 요소 추가
}

element pop() {
	if (is_empty()) fprintf(stderr, "Err!! StackEmpty\n");
	else return stack[top--]; //현재 요소를 반환 후 top을 1줄임
}
element peek() {
	if (is_empty()) fprintf(stderr, "Err!! StackEmpty\n");
	else return stack[top]; //현재 요소 반환
}

void print_stack() {
	if (is_empty()) fprintf(stderr, "Err!! StackEmpty\n");
	else for (int i = 0; i <= top; ++i) printf("name: %s\nrank: %s\nmilitary number: %d\n=========================\n", stack[i].name, stack[i].rank, stack[i].m_num);
	printf("\n");
}