#include"myque.h"
#include<time.h>

int main(int argc, char* argv[]) {
	QueueType q;
	int num;
	init_Queue(&q);

	srand(time(NULL)); //�õ� �ʱ�ȭ

	//����-�Һ� ���μ���
	//20% Ȯ���� �����ϰ� 10%Ȯ���� �Һ�.
	for (int i = 0; i < 100; ++i) { //100ȸ ������ 
		if (rand() % 5 == 0) enqueue(&q, rand() % 100); //5�� ����������� ������ 20�� 20%�� �ش�
		print_queue(&q);
		if(rand() % 10 == 0) num = dequeue(&q); //10���� ����������� ������ 10�� 10%�� �ش�
		print_queue(&q);
	}

	return 0;
}