#include"my_stack.h"

typedef struct _Queue {
	StackType* s1;
	StackType* s2;
}QueueType;

//스택 두 개로 큐 만들기.
//enqueue를 하면 1번 스택에 계속 쌓는다.
//dequeue를 하게되면 2번  스택이 비어있는지 확인하고 있으면 2번 스택에서 요소를 하나 반환한다.
//만약에 스택이 비어있으면 1번 스택에서 2번 스택으로 요소들을 push해준 뒤에 반환한다. 
//다른쪽 스택에 있는 요소들을 한번 pop해준다.

void init_queue(QueueType* q);
void enqueue(QueueType* q,element item);
element dequeue(QueueType* q);
element get_item(QueueType* q);

int main(int argc, char* argv[]) {
	QueueType q;
	init_queue(&q);
	enqueue(&q, 3);
	printf("%d\n", dequeue(&q));
	free(q.s1->data);
	free(q.s2->data);
	free(q.s1);
	free(q.s2);
	return 0;
}

void init_queue(QueueType* q) {
	q->s1 = (StackType*)malloc(sizeof(StackType));
	q->s2 = (StackType*)malloc(sizeof(StackType));
	init_stack(q->s1); 
	init_stack(q->s2);
}

void enqueue(QueueType* q, element item) {
	push(q->s1, item); //어차피 에러를 여기서 발견함.
}

element dequeue(QueueType* q) {
	//2번 스택이 비어있는지 확인한다.
	if (is_empty(q->s2)) { //비어있으면 
		while (!is_empty(q->s1)) push(q->s2, pop(q->s1));
	}
	return pop(q->s2);
}

element get_item(QueueType* q) {
	//2번 스택이 비어있는지 확인한다.
	if (is_empty(q->s2)) { //비어있으면 
		while (!is_empty(q->s1)) push(q->s2, pop(q->s1));
	}
	return peek(q->s2);
}