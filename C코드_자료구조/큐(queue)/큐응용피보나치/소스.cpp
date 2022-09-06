#include "myQue.h"

element Fibo(QueueType* q, int n);

int main() {
	int n;
	element t;
	QueueType* q = (QueueType*)malloc(sizeof QueueType);
	init_Queue(q);
	printf("input: n of F(n): ");
	scanf("%d", &n);
	t=Fibo(q,n);
	printf("F(%d) = %d\n",n,t);
	free(q);
	return 0;
}

element Fibo(QueueType* q,int n) {
	//초기값 할당
	enqueue(q, 0); //F(0)
	enqueue(q, 1); //F(1)
	if (n == 0) return dequeue(q);
	else if (n == 1) {
		dequeue(q); //0꺼내고
		return dequeue(q); //1꺼냄
	}
	else {
		for (int i = 1; i < n; ++i) {
			//제일 처음꺼 하나 꺼내고 두 번째 거는 그냥 값만 가져와서 더한 뒤 그값을 큐에 넣음 
			enqueue(q, dequeue(q) + peek(q));
		}
		dequeue(q);
		//q에 마지막에 넣은 요소가 답.
		return dequeue(q);
	}
}