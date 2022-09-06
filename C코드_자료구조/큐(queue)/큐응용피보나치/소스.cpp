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
	//�ʱⰪ �Ҵ�
	enqueue(q, 0); //F(0)
	enqueue(q, 1); //F(1)
	if (n == 0) return dequeue(q);
	else if (n == 1) {
		dequeue(q); //0������
		return dequeue(q); //1����
	}
	else {
		for (int i = 1; i < n; ++i) {
			//���� ó���� �ϳ� ������ �� ��° �Ŵ� �׳� ���� �����ͼ� ���� �� �װ��� ť�� ���� 
			enqueue(q, dequeue(q) + peek(q));
		}
		dequeue(q);
		//q�� �������� ���� ��Ұ� ��.
		return dequeue(q);
	}
}