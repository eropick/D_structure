#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#define MAX_SIZE 60

typedef int element;
typedef struct _Queue {
	int front;
	int rear;
	int count;
	element data[MAX_SIZE];
}DequeType;

//����ť�� ������ ���ݾ��� �����Ѵ�.
//enqueue�� add_rear�������� �ٲ��ش�.
//is_empty�� is_full�� �Ȱ��� ����� �� �� �ִ�.
//��� �߰��� �ϴ��� ����ְų� ������ ���´� �����ϱ� �����̴�.
//�׻� front�� ù ����� ���� ����Ű�� rear�� ��������Ҹ� ����Ű�� ������ �̿�.

void error(const char* str); //���� �޽��� ��� �� ���μ��� ����.
void init_Deque(DequeType* q); //���� �ʱ�ȭ ���ش�.
boolean is_empty(DequeType* q); //�������Ȯ��
boolean is_full(DequeType* q); //��ȭ���� Ȯ�� 
void add_rear(DequeType* q, element item); //rear�� ��Ҹ� �߰��Ѵ�.
void add_front(DequeType* q, element item); //������ ����ť���� add_front������ �߰��Ѵ�
element delete_rear(DequeType* q); //������ ����ť���� delete_rear������ �߰��Ѵ�
element delete_front(DequeType* q); //front�� ��Ҹ� ������ȯ�Ѵ�.
element get_rear(DequeType* q); //������ ����ť���� get_rear������ �߰��Ѵ�
element get_front(DequeType* q); //front�� ��� �� ��ȯ�Ѵ�.
void deque_print(DequeType* q); //������ ����Լ�

void deque_print(DequeType* q) {
	printf("\nDeque(front: %d, rear: %d ) Data = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front; //front�� ����.
		do {
			i = (i + 1) % MAX_SIZE; //front���� 1���� ���
			printf(" %d |", q->data[i]);
		} while (i != q->rear); //i�� rear�� �����ϸ� �ݺ�����
	}
	printf("\n");
}

void init_Deque(DequeType* q) {
	q->front = 0;
	q->rear = 0;
	q->count = 0;
}

boolean is_full(DequeType* q) {
	return (q->rear + 1) % MAX_SIZE == q->front;  //rear ������ front�� ������ �Ǵ��ؼ� ��ȯ
}

boolean is_empty(DequeType* q) { //�������
	if (q->front == q->rear) return true;
	else return false;
}

void add_rear(DequeType* q, element item) {
	if (is_full(q)) error("ť�� ��ȭ���� �Դϴ�.");
	else {
		q->rear = (q->rear + 1) % MAX_SIZE;
		q->data[q->rear] = item;
		q->count++;
	}
}

//���������� front�� �߰��� ���ָ� -1�� �ּҰ� �����Ѵ�.
//������ ȸ���� �ϹǷ� delete_rear�� �����ϰ� �����Ѵ�.
//ù����� ������ ����Ű�Ƿ� ���� �ּҿ� �߰��� �ڿ� -1���ش�

void add_front(DequeType* q, element item) {
	if (is_full(q)) error("ť�� ��ȭ���� �Դϴ�.");
	else {
		q->data[q->front] = item;
		q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;
		q->count++;
	}
}

element delete_rear(DequeType* q) {
	element item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else {
		/*�⺻������ rear�� ��������Ҹ� ����Ű�Ƿ� ���� ��ȯ�� �� �� 1���� ��Ų��.
		������ �̷��� �Ǵ� ��� �ð�������� ȸ���ϴ� rear�� �ݽð������ �ǹǷ�
		0->4��� ��������ҷ� ���� ����� 0���� -1�� ���༭ ������ �Ǹ�
		MAX_SIZE�� �ٽ� �����ָ� �ȴ�.
		���� ���� �񱳸� �ؼ� �Ҵ��� ���� ���� ������ ������ ����
		���� ������ -1�� ���ص� �׳� MAX_SIZE�� ���� �������� ���ϸ� �ȴ�. */
		item = q->data[q->rear];
		q->rear = (q->rear - 1 + MAX_SIZE) % MAX_SIZE;
		//���׿����ڷ� ���� �� q->rear = q->rear-1 < 0 ? q->rear-1 + MAX_SIZE : q->rear - 1;
		q->count--;
	}
	return item;
}

element delete_front(DequeType* q) {
	element item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else {
		q->front = (q->front + 1) % MAX_SIZE;
		item = q->data[q->front];
		q->count--;
	}
	return item;
}

element get_rear(DequeType* q) {
	element item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else item = q->data[q->rear]; //�ܼ��� rear�� �ִ� ��Ҹ� ��ȯ�Ѵ�.
	return item;
}

element get_front(DequeType* q) {
	element item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else item = q->data[(q->front + 1) % MAX_SIZE]; //�ܼ��� +1���ؼ� ��ȯ�Ѵ�.
	return item;
}

void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}


