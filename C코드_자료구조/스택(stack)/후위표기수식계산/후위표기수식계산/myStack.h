#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100


typedef int element;
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


void init_stack(StackType* s) {
	s->capacity = 1;
	s->top = -1; //����
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