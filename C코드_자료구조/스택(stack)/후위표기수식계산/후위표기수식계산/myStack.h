#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100


typedef int element;
typedef int boolean; //불타입
typedef struct _StackType {
	element* data; //스택의 포인터를 할당.
	int capacity;
	int top;
}StackType;

void init_stack(StackType* s); //스택 초기화
boolean is_empty(StackType* s); //스택 비어있는지 검사
boolean is_full(StackType* s); //스택 가득차 있는지 검사
void push(StackType* s, element item); //push
element pop(StackType* s); //pop
element peek(StackType* s); //peek


void init_stack(StackType* s) {
	s->capacity = 1;
	s->top = -1; //빈스택
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

boolean is_empty(StackType* s) {
	return (s->top == -1);
	//참이면 true,거짓이면 false 반환
}

boolean is_full(StackType* s) {
	return (s->top == (s->capacity - 1));
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		s->capacity *= 2; //capacity의 크기를 두배 늘림.
		if (s->capacity >= MAX_STACK_SIZE) {
			fprintf(stderr, "최대 스택: 더 이상 스택을 추가할 수 없음.\n");
			return; //이 함수만 종료
		}
		else s->data = (element*)realloc(s->data, s->capacity * sizeof(element)); //재할당
	}
	s->data[++(s->top)] = item;
}
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1); //프로세스 종료
		//exit(0)의 경우 정상종료시, exit(1)의 경우 에러로 인한 종료시 파라미터는 반환값.
	}
	else return s->data[(s->top)--]; //값 반환 후 top-1
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}