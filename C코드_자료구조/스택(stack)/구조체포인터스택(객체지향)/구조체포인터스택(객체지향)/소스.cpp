#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

typedef struct _StackType {
	int top;
	element stack[MAX_STACK_SIZE]; 
}StackType;

typedef struct _StackType2{
	int top;
	int capacity; //���� ũ��
	element* stack;
	/*�� ��Ҹ� ���� �迭�� �������� �ʰ� ������ �������� ����
	�̷��� �����Ҵ��� ���� ������ �ʿ��� ������ �޸� ������ �Ҵ�޴� ����� ����� �� �ִ�.
	��, �̷��� ���ָ� init�� �� �� top=-1, element�����Ҵ�, capacity=1 �� �������ְ� 
	push�� �� �� ������ ��� realloc()�� ���� ���Ҵ��ϴ� ����� ����Ѵ�.  
	*/
}StackType2;

void init(StackType* s);
void push(StackType* s,element items); //��Ҹ� �Է��Ѵ�.
element pop(StackType* s); //��Ҹ� ���� �� ��ȯ�Ѵ�.
element peek(StackType* s); //��Ҹ� ��ȯ�Ѵ�.
void print_stack(StackType* s); //���� ���ÿ� �ִ� ��ҵ��� ����Ѵ�.
boolean is_full(StackType* s); //���� ������ ������ �ִ����� �Ǵ��Ѵ�. 
boolean is_empty(StackType* s); //���� ������ ��Ұ� ����ִ����� �Ǵ��Ѵ�.
element write_info(const char* name,const char* rank, int num); //������ ��� ������ �ۼ���.

int main(int argc, char* argv[]) {
	StackType s1;
	StackType* s; //�̷��� �����Ҵ����� ������ �����ϸ� �� ���������� ���ٰ����ϴ�.
	s = (StackType*)malloc(sizeof(StackType));
	init(&s1);
	init(s);
	push(&s1, write_info("kimbap","private",10284));
	push(s, write_info("kimbap", "private", 10284));
	push(&s1, write_info("leebalso", "private firstclass", 20284));
	push(s, write_info("leebalso", "private firstclass", 20284));
	print_stack(&s1);
	print_stack(s);
	free(s);
	return 0;
}

element write_info(const char* name,const char* rank, int num) {
	element x;
	strcpy(x.name, name);
	strcpy(x.rank, rank);
	x.m_num = num;
	return x;
}

boolean is_full(StackType* s) {
	if (s->top >= MAX_STACK_SIZE) return TRUE;
	else return FALSE;
}

boolean is_empty(StackType* s) {
	if (s->top == -1) return TRUE;
	else return FALSE;
}

void push(StackType* s, element items) {
	if (is_full(s)) fprintf(stderr, "ERR!! StackOver\n");
	else s->stack[++(s->top)] = items;
}

element pop(StackType* s) {
	if (is_empty(s)) fprintf(stderr, "ERR!! StackEmpty\n");
	else return s->stack[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s)) fprintf(stderr, "ERR!! StackEmpty\n");
	else return s->stack[s->top];
}

void print_stack(StackType* s) {
	if(is_empty(s)) fprintf(stderr, "ERR!! StackEmpty\n");
	else for (int i = 0; i <= s->top; ++i) {
		printf("===================\n");
		printf("name: %s\nrank: %s\nmilitary number: %d\n", s->stack[i].name, s->stack[i].rank, s->stack[i].m_num);
		printf("===================\n");
	}
}

void init(StackType* s) {
	s->top = -1; //�� ������ �ʱ�ȭ ��.
}