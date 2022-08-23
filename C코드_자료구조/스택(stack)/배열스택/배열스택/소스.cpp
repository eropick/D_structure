#include<stdio.h>
#define MAX_STACK_SIZE 100
#define TRUE (1)
#define FALSE (0)

//스택의 정보가 단순히 정수나,문자라면 이렇게 전역변수로 설정한다.
typedef int element;
typedef int boolean;
int top = -1;
element stack[MAX_STACK_SIZE];

void create(); //스택을 초기화해준다.
void push(element item); //요소를 입력한다.
element pop(); //요소를 제거 후 반환한다.
element peek(); //요소를 반환한다.
void print_stack(); //현재 스택에 있는 요소들을 출력한다.
boolean is_full(); //현재 스택이 가득차 있는지를 판단한다. 
boolean is_empty(); //현재 스택의 요소가 비어있는지를 판단한다.

int main(int argc,char* argv[]) {
	create();
	print_stack();
	push(100);
	push(50);
	push(10);
	print_stack();
	printf("스택 값 반환: %d\n", pop());
	printf("스택 값 반환: %d\n", peek());
	printf("스택 값 반환: %d\n", pop());
	print_stack();
	return 0;
}

void create() {
	for (int i = 0; i < MAX_STACK_SIZE; ++i) stack[i] = 0;
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
	if (is_full()) printf("Err!! StackOver\n"); //에러
	else stack[++top] = item; //top을 1증가시킨 인덱스에 요소 추가
}

element pop() {
	if (is_empty()) printf("Err!! StackEmpty\n"); //에러
	else return stack[top--]; //현재 요소를 반환 후 top을 1줄임
}
element peek() {
	if (is_empty()) printf("Err!! StackEmpty\n"); //에러
	else return stack[top]; //현재 요소 반환
}

void print_stack() {
	if(is_empty()) printf("Stack is Empty");
	else for (int i = 0; i <= top; ++i) printf("%d ", stack[i]);
	printf("\n");
}