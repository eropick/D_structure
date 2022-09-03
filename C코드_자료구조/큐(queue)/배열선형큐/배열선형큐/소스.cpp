#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#define MAX_SIZE 100

typedef int element; //��� Ÿ���� ������
typedef struct _Queue {
	int front;
	int rear;
	element data[MAX_SIZE];
}QueueType;

void error(const char* str); //���� �޽��� ��� �� ���μ��� ����.
void init_Queue(QueueType* q); //Q�� �ʱ�ȭ ���ش�.
void enqueue(QueueType* q, element item); //��Ҹ� �߰��Ѵ�.
element dequeue(QueueType* q); //�� �տ� �ִ� ��Ҹ� ���� �� ��ȯ
element peek(QueueType* q); //�� �տ� �ִ� �� ��ȯ.
boolean is_empty(QueueType* q); //�������Ȯ��
boolean is_full(QueueType* q); //��ȭ���� Ȯ�� 

int main(int argc, char* argv[]) {
	QueueType q;
	init_Queue(&q);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	enqueue(&q, 4);
	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));
	printf("%d\n", peek(&q));
	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));
	return 0;
}

boolean is_full(QueueType* q) {
	if (q->rear == MAX_SIZE - 1) return true;
	else return false;
}

boolean is_empty(QueueType* q) {
	if (q->front == q->rear) return true;
	else return false;
}


void enqueue(QueueType* q, element item) {
	if (is_full(q)) error("ť�� ��ȭ���� �Դϴ�.");
	else q->data[++(q->rear)] = item;
}

element dequeue(QueueType* q) {
	int item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else item = q->data[++(q->front)];
	return item;
}

element peek(QueueType* q) {
	int item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else item = q->data[(q->front)+1]; //�ܼ��� +1���ؼ� ��ȯ�Ѵ�.
	return item;
}

void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}

void init_Queue(QueueType* q) {
	q->front = -1;
	q->rear = -1;
}
