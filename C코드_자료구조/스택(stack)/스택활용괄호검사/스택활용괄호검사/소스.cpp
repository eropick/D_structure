#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0


typedef char element; //charŸ��
typedef int boolean; //��Ÿ��
typedef struct _StackType {
	element* data; //������ �����͸� �Ҵ�.
	int capacity;
	int top;
}StackType;

void init_stack(StackType* s); //���� �ʱ�ȭ
boolean is_empty(StackType* s); //���� ����ִ��� �˻�
boolean is_full(StackType* s); //���� ������ �ִ��� �˻�
void push(StackType* s, element item); //push
element pop(StackType* s); //pop
element peek(StackType* s); //peek
boolean check_matching(char* in); //���ڿ��� �Ķ���ͷ� ����.


int main(int argc, char* argv[]) {
	char p[100];
	printf("���ڿ� �Է�: ");
	gets_s(p, sizeof(p));
	if(check_matching(p)==TRUE)	printf("%s ��ȣ �˻� ����\n",p);
	else printf("%s ��ȣ �˻� ����\n", p);
	return 0;
}

void init_stack(StackType* s) {
	s->capacity = 1;
	s->top = -1; //�ƹ��͵� ���� ����
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

boolean is_empty(StackType* s) {
	return (s->top == -1);
	//���̸� true,�����̸� false ��ȯ
}

boolean is_full(StackType* s) {
	return (s->top == (s->capacity - 1));
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		s->capacity *= 2; //capacity�� ũ�⸦ �ι� �ø�.
		if (s->capacity >= MAX_STACK_SIZE) {
			fprintf(stderr, "�ִ� ����: �� �̻� ������ �߰��� �� ����.\n");
			return; //�� �Լ��� ����
		}
		else s->data = (element*)realloc(s->data, s->capacity * sizeof(element)); //���Ҵ�
	}
	s->data[++(s->top)] = item;
}
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1); //���μ��� ����
		//exit(0)�� ��� ���������, exit(1)�� ��� ������ ���� ����� �Ķ���ʹ� ��ȯ��.
	}
	else return s->data[(s->top)--]; //�� ��ȯ �� top-1
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}

boolean check_matching(char* in) {
	StackType s;
	init_stack(&s); //���� �ʱ�ȭ
	int rlen = strlen(in); //���ڿ� ���� ��ȯ.
	char ch,ch_pop; //�ӽ� ���ں���
	for (int i = 0; i < rlen; ++i) {//�ݺ�
		ch = in[i];
		switch (ch) {
			case '(': case '{': case '[': //���� ��ȣ ������ ���ÿ� ����
				push(&s, ch);
				break;
			case ')': case '}': case ']': //������ ��ȣ�� ������ ���
				//������ ��ȣ�� ������ ������ ������� Ȯ�� �� ������� ����
				if (is_empty(&s)) return FALSE;
				else { //���� ������� ������ POP�� ���� ch_pop�� ch�� ���ؼ� ���� ���� �ƴϸ� ����
					ch_pop = pop(&s); //���ÿ��� �ϳ��� ��ȯ(���ʰ�ȣ)
					if ((ch_pop == '(' && ch != ')') ||
						(ch_pop == '{' && ch != '}') ||
						(ch_pop == '[' && ch != ']')
						) return FALSE;
					//���� ���� �������� ������ false
				}
				break;
			default:
				break;
		}
	}
	//������ �� ���ȴµ� ������ ������� ������ ����.
	if (is_empty(&s)) return TRUE;
	else return FALSE;
	//���� �����µ� ������ ������� �ʰ� ���õ� ����ִٸ� ����
}