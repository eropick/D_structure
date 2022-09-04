#include "myQue.h"
#include<time.h>

int main(int argc, char** argv) {
	QueueType line;
	init_Queue(&line);
	int total_wait = 0; //총 대기시간
	int total_customers = 0; //총 고객수
	int service_time = 0; //고객의 서비스 시간이 들어감
	int service_customer = 0; //고객 ID가 들어감
	int minute = 60;
	int clock;
	int check; //명령이 실행되었는지 체크함.
	int remain_customers = 0; //남은 고객
	srand(time(NULL));
	for (clock = 0; clock < minute; ++clock) {
		check = 0;
		//0~10랜덤한 수가 3이하라면 고객이 온 것으로 처리
		if (rand() % 11 <= 3) {
			element customer = { ++total_customers, clock, rand() % 3 + 1 }; //고객생성
			//대기열에 넣음
			enqueue(&line, customer);
			printf("(%d분)[System] [%d]고객이 %d분에 대기열에 들어옵니다.(업무처리시간=%d분)\n\n", 
				clock,customer.id, customer.arrival_time, customer.service_time);
			check++;
		}
		//고객이 서비스를 받고있다면 서비스 시간을 줄인다.
		if (service_time > 0) {
			printf("(%d분)[System] 고객 [%d]님의 업무 처리중입니다.\n\n",clock,service_customer);
			service_time--;
			check++;
		}
		else { //서비스를 받고있는 고객이 없다면
			if (!is_empty(&line)) { //대기열이 차 있다면
				element customer = dequeue(&line); //대기열의 손님을 한 명 받는다.
				total_wait += clock - customer.arrival_time; //대기시간을 추가한다.
				service_time = customer.service_time; //서비스 시간을 입력한다.
				service_customer = customer.id; //고객 ID를 받는다.
				printf("(%d분)[System] 고객 [%d]님이 %d분에 서비스를 시작합니다.\n대기시간은 %d분 이었습니다.\n\n",
					clock,service_customer, clock, clock - customer.arrival_time);
				check++;
			}
		}
		if(check > 0 )printf("----------------------------------------\n\n");
		Sleep(1000);
	}
	for (int i = 0; ; ++i) {
		if (!is_empty(&line)) {
			//비어있지 않으면
			dequeue(&line); //인원 빼줌
			remain_customers++; //남은 인원에 추가
		}
		else break;
	}
	if(service_time>0) remain_customers++; //서비스가 안 끝난 사람도 남은 인원
	printf("총 대기시간: %d분\n 평균 대기시간: %d분\n남은 인원 수: %d명\n", total_wait, 
		total_wait/total_customers,remain_customers);
	return 0;
}