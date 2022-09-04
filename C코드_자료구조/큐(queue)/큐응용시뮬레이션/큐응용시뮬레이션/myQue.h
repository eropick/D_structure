#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#define MAX_SIZE 60

typedef struct _element {
	int id; //id
	int arrival_time; //도착시간
	int service_time; //서비스시간
}element;
typedef struct _Queue {
	int front;
	int rear;
	element data[MAX_SIZE];
}QueueType;

//선형큐와 원형큐 초기 값은 -1과 0으로 각각 다르지만
//front가 가리키는 값은 맨 앞 요소의 전, rear가 가리키는 값은 삽입한 요소로 동일하고
//삭제반환을 할 때에는 요소를 1증가시키고 반환, 삽입을 할 때에는 요소를 1증가시키고 삽입으로 동일하다.
//다만, 다시 초기로 돌려줘야 하기 때문에 modula연산이 필요하다.

void error(const char* str); //에러 메시지 출력 후 프로세스 종료.
void init_Queue(QueueType* q); //Q를 초기화 해준다.
void enqueue(QueueType* q, element item); //요소를 추가한다.
element dequeue(QueueType* q); //맨 앞에 있는 요소를 빼고 값 반환
element peek(QueueType* q); //맨 앞에 있는 값 반환.
boolean is_empty(QueueType* q); //공백상태확인
boolean is_full(QueueType* q); //포화상태 확인 
void Queue_print(QueueType* q); //원형큐 출력함수
//포화상태를 count요소가 max_size와 동일하고 rear와 front가 같다면 포화상태로 인정한다.
//대신 count를 enque나 deque때 가감연산을 해줘야한다.

//원형큐 
//size 5 => 0,1,2,3,4 다음 5가 나오면 0으로 감.

void init_Queue(QueueType* q) {
	q->front = 0;
	q->rear = 0;
}

boolean is_full(QueueType* q) {
	return (q->rear + 1) % MAX_SIZE == q->front;  //rear 다음이 front랑 같은지 판단해서 반환
}

boolean is_empty(QueueType* q) { //공백상태
	if (q->front == q->rear) return true;
	else return false;
}


void enqueue(QueueType* q, element item) {
	if (is_full(q)) error("큐가 포화상태 입니다.");
	else {
		q->rear = (q->rear + 1) % MAX_SIZE; //원형큐방식으로 최대값이 되면 0으로 가도록
		q->data[q->rear] = item;
	}
}

element dequeue(QueueType* q) {
	element item;
	if (is_empty(q)) error("큐가 공백상태입니다.");
	else {
		q->front = (q->front + 1) % MAX_SIZE;
		item = q->data[q->front];
	}
	return item;
}

element peek(QueueType* q) {
	element item;
	if (is_empty(q)) error("큐가 공백상태입니다.");
	else item = q->data[(q->front + 1) % MAX_SIZE]; //단순히 +1만해서 반환한다.
	return item;
}

void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}

void Queue_print(QueueType* q) {
	printf("Deque(front: %d, rear: %d ) Data = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front; //front값 넣음.
		do {
			i = (i + 1) % MAX_SIZE; //front에서 1증가 요소
			printf(" %d |", q->data[i].id);
		} while (i != q->rear); //i가 rear에 도착하면 반복종료
	}
	printf("\n");
}