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
	int front;
	int rear;
	element data[MAX_SIZE];
}QueueType;

//����ť�� ����ť �ʱ� ���� -1�� 0���� ���� �ٸ�����
//front�� ����Ű�� ���� �� �� ����� ��, rear�� ����Ű�� ���� ������ ��ҷ� �����ϰ�
//������ȯ�� �� ������ ��Ҹ� 1������Ű�� ��ȯ, ������ �� ������ ��Ҹ� 1������Ű�� �������� �����ϴ�.
//�ٸ�, �ٽ� �ʱ�� ������� �ϱ� ������ modula������ �ʿ��ϴ�.

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
}

boolean is_full(QueueType* q) {
	return (q->rear + 1) % MAX_SIZE == q->front;  //rear ������ front�� ������ �Ǵ��ؼ� ��ȯ
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
	}
}

element dequeue(QueueType* q) {
	element item;
	if (is_empty(q)) error("ť�� ��������Դϴ�.");
	else {
		q->front = (q->front + 1) % MAX_SIZE;
		item = q->data[q->front];
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