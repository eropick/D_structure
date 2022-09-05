#include"my_stack.h"

typedef struct _Queue {
	StackType* s1;
	StackType* s2;
}QueueType;

//���� �� ���� ť �����.
//enqueue�� �ϸ� 1�� ���ÿ� ��� �״´�.
//dequeue�� �ϰԵǸ� 2��  ������ ����ִ��� Ȯ���ϰ� ������ 2�� ���ÿ��� ��Ҹ� �ϳ� ��ȯ�Ѵ�.
//���࿡ ������ ��������� 1�� ���ÿ��� 2�� �������� ��ҵ��� push���� �ڿ� ��ȯ�Ѵ�. 
//�ٸ��� ���ÿ� �ִ� ��ҵ��� �ѹ� pop���ش�.

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
	push(q->s1, item); //������ ������ ���⼭ �߰���.
}

element dequeue(QueueType* q) {
	//2�� ������ ����ִ��� Ȯ���Ѵ�.
	if (is_empty(q->s2)) { //��������� 
		while (!is_empty(q->s1)) push(q->s2, pop(q->s1));
	}
	return pop(q->s2);
}

element get_item(QueueType* q) {
	//2�� ������ ����ִ��� Ȯ���Ѵ�.
	if (is_empty(q->s2)) { //��������� 
		while (!is_empty(q->s1)) push(q->s2, pop(q->s1));
	}
	return peek(q->s2);
}