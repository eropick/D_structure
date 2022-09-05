#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#define MAX_SIZE 60

typedef struct _element {
	int id; //id
	int arrival_time; //�����ð�
	int service_time; //���񽺽ð�
}element;
typedef struct _Queue {
	int front; //����
	int rear; //�Ĵ�
	int count; //��Ұ���
	element data[MAX_SIZE];
}QueueType;


void error(const char* str); //���� �޽��� ��� �� ���μ��� ����.
void init_Queue(QueueType* q); //Q�� �ʱ�ȭ ���ش�.
void enqueue(QueueType* q, element item); //��Ҹ� �߰��Ѵ�.
element dequeue(QueueType* q); //�� �տ� �ִ� ��Ҹ� ���� �� ��ȯ
element peek(QueueType* q); //�� �տ� �ִ� �� ��ȯ.
boolean is_empty(QueueType* q); //�������Ȯ��
boolean is_full(QueueType* q); //��ȭ���� Ȯ�� 
void Queue_print(QueueType* q); //����ť ����Լ�
//��ȭ���¸� count��Ұ� max_size�� �����ϰ� rear�� front�� ���ٸ� ��ȭ���·� �����Ѵ�.
//��� count�� enque�� deque�� ���������� ������Ѵ�.

//����ť 
//size 5 => 0,1,2,3,4 ���� 5�� ������ 0���� ��.

void init_Queue(QueueType* q) {
	q->front = 0;
	q->rear = 0;
	q->count = 0;
}

boolean is_full(QueueType* q) {
	return (q->count == MAX_SIZE) && (q->rear == q->front);  //��� ������ MAX_SIZE�̰� �� ���� ���ٸ� ��ȭ
}

boolean is_empty(QueueType* q) { //�������
	return (q->count == 0) && (q->rear == q->front); //��� ������ 0�̰� �� ���� ���ٸ� ����
}


void enqueue(QueueType* q, element item) {
	if (is_full(q)) error("ť�� ��ȭ���� �Դϴ�.");
	else {
		q->rear = (q->rear + 1) % MAX_SIZE; //����ť������� �ִ밪�� �Ǹ� 0���� ������
		q->data[q->rear] = item;
		q->count++;
	}
}

element dequeue(QueueType* q) {
	element item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else {
		q->front = (q->front + 1) % MAX_SIZE;
		item = q->data[q->front];
		q->count--;
	}
	return item;
}

element peek(QueueType* q) {
	element item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else item = q->data[(q->front + 1) % MAX_SIZE]; //�ܼ��� +1���ؼ� ��ȯ�Ѵ�.
	return item;
}

void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}

void Queue_print(QueueType* q) {
	printf("Deque(front: %d, rear: %d ) Data = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front; //front�� ����.
		do {
			i = (i + 1) % MAX_SIZE; //front���� 1���� ���
			printf(" %d |", q->data[i].id);
		} while (i != q->rear); //i�� rear�� �����ϸ� �ݺ�����
	}
	printf("\n");
}