#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#define MAX_SIZE 5

typedef int element; //��� Ÿ���� ������
typedef struct _Queue {
	int front;
	int rear;
	int count; //����� ����
	element data[MAX_SIZE];
}QueueType;

//����ť�� ����ť �ʱ� ���� -1�� 0���� ���� �ٸ�����
//front�� ����Ű�� ���� �� �� ����� ��, rear�� ����Ű�� ���� ������ ��ҷ� �����ϰ�
//������ȯ�� �� ������ ��Ҹ� 1������Ű�� ��ȯ, ������ �� ������ ��Ҹ� 1������Ű�� �������� �����ϴ�.
//�ٸ�, �ٽ� �ʱ�� ������� �ϱ� ������ modula������ �ʿ��ϴ�.

void error(const char* str); //���� �޽��� ��� �� ���μ��� ����.
void print_queue(QueueType* q); //����ť ���
void init_Queue(QueueType* q); //Q�� �ʱ�ȭ ���ش�.
void enqueue(QueueType* q, element item); //��Ҹ� �߰��Ѵ�.
element dequeue(QueueType* q); //�� �տ� �ִ� ��Ҹ� ���� �� ��ȯ
element peek(QueueType* q); //�� �տ� �ִ� �� ��ȯ.
boolean is_empty(QueueType* q); //�������Ȯ��
boolean is_full(QueueType* q); //��ȭ���� Ȯ�� 
boolean is_full2(QueueType* q);
//��ȭ���¸� count��Ұ� max_size�� �����ϰ� rear�� front�� ���ٸ� ��ȭ���·� �����Ѵ�.
//��� count�� enque�� deque�� ���������� ������Ѵ�.

//����ť 
//size 5 => 0,1,2,3,4 ���� 5�� ������ 0���� ��.

void init_Queue(QueueType* q) {
	q->front = 0;
	q->rear = 0;
	q->count = 0;
}

void print_queue(QueueType* q) {
	printf("Queue(front: %d rear: %d) DATA: ", q->front, q->rear);
	if (!is_empty(q)) { //����������� Ȯ��
		int i = q->front;
		do {
			i = (i + 1) % MAX_SIZE; //����
			printf("|%d ", q->data[i]);
			if (i == q->rear) break;
		} while (i != q->front);
	}
	printf("\n");
}

boolean is_full(QueueType* q) {
	return (q->rear + 1) % MAX_SIZE == q->front;  //rear ������ front�� ������ �Ǵ��ؼ� ��ȯ
}

boolean is_full2(QueueType* q) {
	return is_empty(q) && (q->count == MAX_SIZE); //front�� rear�� ��ġ�� ���� count�� MAX_SIZE���� �Ǵ��ؼ� ��ȯ
}

boolean is_empty(QueueType* q) { //�������
	if (q->front == q->rear) return true;
	else return false;
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
	int item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else {
		q->front = (q->front + 1) % MAX_SIZE;
		item = q->data[q->front];
		q->count--;
	}
	return item;
}

element peek(QueueType* q) {
	int item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else item = q->data[(q->front + 1) % MAX_SIZE]; //�ܼ��� +1���ؼ� ��ȯ�Ѵ�.
	return item;
}

void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}


