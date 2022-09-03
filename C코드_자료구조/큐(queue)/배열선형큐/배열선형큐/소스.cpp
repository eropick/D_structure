#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#define MAX_SIZE 100

typedef int element; //요소 타입이 정수형
typedef struct _Queue {
	int front;
	int rear;
	element data[MAX_SIZE];
}QueueType;

void error(const char* str); //에러 메시지 출력 후 프로세스 종료.
void init_Queue(QueueType* q); //Q를 초기화 해준다.
void enqueue(QueueType* q, element item); //요소를 추가한다.
element dequeue(QueueType* q); //맨 앞에 있는 요소를 빼고 값 반환
element peek(QueueType* q); //맨 앞에 있는 값 반환.
boolean is_empty(QueueType* q); //공백상태확인
boolean is_full(QueueType* q); //포화상태 확인 

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
	if (is_full(q)) error("큐가 포화상태 입니다.");
	else q->data[++(q->rear)] = item;
}

element dequeue(QueueType* q) {
	int item;
	if (is_empty(q)) error("큐가 공백상태입니다.");
	else item = q->data[++(q->front)];
	return item;
}

element peek(QueueType* q) {
	int item;
	if (is_empty(q)) error("큐가 공백상태입니다.");
	else item = q->data[(q->front)+1]; //단순히 +1만해서 반환한다.
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
