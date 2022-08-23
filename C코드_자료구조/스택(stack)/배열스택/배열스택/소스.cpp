#include<stdio.h>
#define MAX_STACK_SIZE 100
#define TRUE (1)
#define FALSE (0)

//������ ������ �ܼ��� ������,���ڶ�� �̷��� ���������� �����Ѵ�.
typedef int element;
typedef int boolean;
int top = -1;
element stack[MAX_STACK_SIZE];

void create(); //������ �ʱ�ȭ���ش�.
void push(element item); //��Ҹ� �Է��Ѵ�.
element pop(); //��Ҹ� ���� �� ��ȯ�Ѵ�.
element peek(); //��Ҹ� ��ȯ�Ѵ�.
void print_stack(); //���� ���ÿ� �ִ� ��ҵ��� ����Ѵ�.
boolean is_full(); //���� ������ ������ �ִ����� �Ǵ��Ѵ�. 
boolean is_empty(); //���� ������ ��Ұ� ����ִ����� �Ǵ��Ѵ�.

int main(int argc,char* argv[]) {
	create();
	print_stack();
	push(100);
	push(50);
	push(10);
	print_stack();
	printf("���� �� ��ȯ: %d\n", pop());
	printf("���� �� ��ȯ: %d\n", peek());
	printf("���� �� ��ȯ: %d\n", pop());
	print_stack();
	return 0;
}

void create() {
	for (int i = 0; i < MAX_STACK_SIZE; ++i) stack[i] = 0;
}

boolean is_full() {
	if (top >= MAX_STACK_SIZE) return TRUE; //���� �� ������
	else return FALSE;
}
boolean is_empty() {
	if (top < 0) return TRUE; //�ε��� -1�̸�
	else return FALSE;
}

void push(element item) {
	if (is_full()) printf("Err!! StackOver\n"); //����
	else stack[++top] = item; //top�� 1������Ų �ε����� ��� �߰�
}

element pop() {
	if (is_empty()) printf("Err!! StackEmpty\n"); //����
	else return stack[top--]; //���� ��Ҹ� ��ȯ �� top�� 1����
}
element peek() {
	if (is_empty()) printf("Err!! StackEmpty\n"); //����
	else return stack[top]; //���� ��� ��ȯ
}

void print_stack() {
	if(is_empty()) printf("Stack is Empty");
	else for (int i = 0; i <= top; ++i) printf("%d ", stack[i]);
	printf("\n");
}