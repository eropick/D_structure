#include"myque.h"
#include<time.h>

int main(int argc, char* argv[]) {
	QueueType q;
	int num;
	init_Queue(&q);

	srand(time(NULL)); //시드 초기화

	//생산-소비 프로세스
	//20% 확률로 생산하고 10%확률로 소비.
	for (int i = 0; i < 100; ++i) { //100회 시행중 
		if (rand() % 5 == 0) enqueue(&q, rand() % 100); //5로 나누어떨어지는 수들은 20개 20%에 해당
		print_queue(&q);
		if(rand() % 10 == 0) num = dequeue(&q); //10으로 나누어떨어지는 수들은 10개 10%에 해당
		print_queue(&q);
	}

	return 0;
}