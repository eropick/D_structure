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

//원형큐의 연산을 조금씩만 수정한다.
//enqueue는 add_rear연산으로 바꿔준다.
//is_empty나 is_full은 똑같이 사용해 줄 수 있다.
//어디서 추가를 하던지 비어있거나 가득찬 상태는 동일하기 때문이다.
//항상 front는 첫 요소의 앞을 가리키고 rear는 마지막요소를 가리키고 있음을 이용.

void error(const char* str); //에러 메시지 출력 후 프로세스 종료.
void init_Deque(DequeType* q); //덱을 초기화 해준다.
boolean is_empty(DequeType* q); //공백상태확인
boolean is_full(DequeType* q); //포화상태 확인 
void add_rear(DequeType* q, element item); //rear에 요소를 추가한다.
void add_front(DequeType* q, element item); //기존에 원형큐에서 add_front연산을 추가한다
element delete_rear(DequeType* q); //기존에 원형큐에서 delete_rear연산을 추가한다
element delete_front(DequeType* q); //front에 요소를 삭제반환한다.
element get_rear(DequeType* q); //기존에 원형큐에서 get_rear연산을 추가한다
element get_front(DequeType* q); //front에 요소 값 반환한다.
void deque_print(DequeType* q); //원형덱 출력함수

void deque_print(DequeType* q) {
	printf("\nDeque(front: %d, rear: %d ) Data = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front; //front값 넣음.
		do {
			i = (i + 1) % MAX_SIZE; //front에서 1증가 요소
			printf(" %d |", q->data[i]);
		} while (i != q->rear); //i가 rear에 도착하면 반복종료
	}
	printf("\n");
}

void init_Deque(DequeType* q) {
	q->front = 0;
	q->rear = 0;
	q->count = 0;
}

boolean is_full(DequeType* q) {
	return (q->rear + 1) % MAX_SIZE == q->front;  //rear 다음이 front랑 같은지 판단해서 반환
}

boolean is_empty(DequeType* q) { //공백상태
	if (q->front == q->rear) return true;
	else return false;
}

void add_rear(DequeType* q, element item) {
	if (is_full(q)) error("큐가 포화상태 입니다.");
	else {
		q->rear = (q->rear + 1) % MAX_SIZE;
		q->data[q->rear] = item;
		q->count++;
	}
}

//마찬가지로 front에 추가를 해주면 -1씩 주소가 감소한다.
//역방향 회전을 하므로 delete_rear와 동일하게 연산한다.
//첫요소의 이전을 가리키므로 기존 주소에 추가한 뒤에 -1해준다

void add_front(DequeType* q, element item) {
	if (is_full(q)) error("큐가 포화상태 입니다.");
	else {
		q->data[q->front] = item;
		q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;
		q->count++;
	}
}

element delete_rear(DequeType* q) {
	element item;
	if (is_empty(q)) error("큐가 공백상태입니다.");
	else {
		/*기본적으로 rear는 마지막요소를 가리키므로 먼저 반환을 한 후 1감소 시킨다.
		하지만 이렇게 되는 경우 시계방향으로 회전하던 rear가 반시계방향이 되므로
		0->4라는 마지막요소로 가는 방법은 0에서 -1을 해줘서 음수가 되면
		MAX_SIZE를 다시 더해주면 된다.
		물론 조건 비교를 해서 할당을 해줄 수도 있지만 음수가 되지
		않을 때에는 -1을 해준뒤 그냥 MAX_SIZE로 나눈 나머지를 구하면 된다. */
		item = q->data[q->rear];
		q->rear = (q->rear - 1 + MAX_SIZE) % MAX_SIZE;
		//삼항연산자로 만든 식 q->rear = q->rear-1 < 0 ? q->rear-1 + MAX_SIZE : q->rear - 1;
		q->count--;
	}
	return item;
}

element delete_front(DequeType* q) {
	element item;
	if (is_empty(q)) error("큐가 공백상태입니다.");
	else {
		q->front = (q->front + 1) % MAX_SIZE;
		item = q->data[q->front];
		q->count--;
	}
	return item;
}

element get_rear(DequeType* q) {
	element item;
	if (is_empty(q)) error("큐가 공백상태입니다.");
	else item = q->data[q->rear]; //단순히 rear에 있는 요소를 반환한다.
	return item;
}

element get_front(DequeType* q) {
	element item;
	if (is_empty(q)) error("큐가 공백상태입니다.");
	else item = q->data[(q->front + 1) % MAX_SIZE]; //단순히 +1만해서 반환한다.
	return item;
}

void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}


