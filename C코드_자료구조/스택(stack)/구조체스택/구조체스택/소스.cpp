#include<stdio.h>
#define MAX_STACK_SIZE 100
#define MAX_STRING 100
#define TRUE (1)
#define FALSE (0)

//������ ������ �������� ���� ��� ����ü�� �����Ѵ�.
//������� ������ ������� �غ���.
typedef struct _element {
	char name[MAX_STRING];
	char rank[MAX_STRING];
	int m_num;
}element;
typedef int boolean;
int top = -1;
element stack[MAX_STACK_SIZE];

void push(element item); //��Ҹ� �Է��Ѵ�.
element pop(); //��Ҹ� ���� �� ��ȯ�Ѵ�.
element peek(); //��Ҹ� ��ȯ�Ѵ�.
void print_stack(); //���� ���ÿ� �ִ� ��ҵ��� ����Ѵ�.
boolean is_full(); //���� ������ ������ �ִ����� �Ǵ��Ѵ�. 
boolean is_empty(); //���� ������ ��Ұ� ����ִ����� �Ǵ��Ѵ�.

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
	if (top >= MAX_STACK_SIZE) return TRUE; //���� �� ������
	else return FALSE;
}
boolean is_empty() {
	if (top < 0) return TRUE; //�ε��� -1�̸�
	else return FALSE;
}

void push(element item) {
	if (is_full()) fprintf(stderr,"Err!! StackOver\n");
	else stack[++top] = item; //top�� 1������Ų �ε����� ��� �߰�
}

element pop() {
	if (is_empty()) fprintf(stderr, "Err!! StackEmpty\n");
	else return stack[top--]; //���� ��Ҹ� ��ȯ �� top�� 1����
}
element peek() {
	if (is_empty()) fprintf(stderr, "Err!! StackEmpty\n");
	else return stack[top]; //���� ��� ��ȯ
}

void print_stack() {
	if (is_empty()) fprintf(stderr, "Err!! StackEmpty\n");
	else for (int i = 0; i <= top; ++i) printf("name: %s\nrank: %s\nmilitary number: %d\n=========================\n", stack[i].name, stack[i].rank, stack[i].m_num);
	printf("\n");
}