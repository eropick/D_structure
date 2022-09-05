#include "myQue.h"
#include<time.h>

void init_all_Queue(QueueType* q, int num); //모든 큐 초기화
int line_count(QueueType* q, int* svctime,int n); //직원 수와 큐를 받아 제일 적은 줄을 추려냄

//큐를 n개 만듬. 직원도 n명이므로 서비스 시간과 서비스 고객도 n명으로 처리.
//동적할당을 사용.
//기존의 직원1명일 때의 시뮬레이션을 n명일 때의 시뮬레이션으로 만듬

int main(int argc, char** argv) {
	int employee;
	int clock, minute = 60;
	int check; //명령이 실행되었는지 체크함.
	int total_wait = 0; //총 대기시간
	int total_customers = 0; //총 고객수
	int remain_customers = 0; //남은 고객
	int min_customers=0; //최소인원
	printf("직원 수를 입력하세요: ");
	scanf("%d", &employee);
	QueueType* line = (QueueType*)malloc(employee*sizeof(QueueType)); //직원 수만큼 동적할당.
	int* service_time = (int*)malloc(employee * sizeof(int)); //직원 수만큼 동적할당.
	int* service_customer = (int*)malloc(employee * sizeof(int)); //직원 수만큼 동적할당.
	init_all_Queue(line, employee); //모든 큐 초기화
	srand(time(NULL));
	for (clock = 0; clock < minute; ++clock) { //업무 반복 구간.
		check = 0;
		//0~10랜덤한 수가 3이하라면 고객이 온 것으로 처리
		if (rand() % 11 <= 3) {
			element customer = { ++total_customers, clock, rand() % 3 + 1 }; //고객생성
			min_customers = line_count(line,service_time,employee); 
			//대기열의 대기 인원을 계산해서 제일 적은 대기열을 반환
			enqueue(line+min_customers, customer); //제일 적은 대기열에 고객정보 삽입
			printf("(%d분)[System] 고객 [%d]님이 %d분에 대기열%d에 들어옵니다.(업무처리시간=%d분)\n\n",
				clock, customer.id, customer.arrival_time, min_customers+1,customer.service_time);
			check++;
		}
		//고객이 서비스를 받고있다면 서비스 시간을 줄인다.
		//모든 줄에 대해서 서비스 여부를 파악)
		for (int i = 0; i < employee; ++i) {
			if (service_time[i] > 0) {
				printf("(%d분)[System%d] 고객 [%d]님의 업무 처리중입니다.\n\n", clock,i+1, service_customer[i]);
				service_time[i]--;
				check++;
			}
			else { //서비스를 받고있는 고객이 없다면
				if (!is_empty(line+i)) { //대기열이 차 있다면
					element customer = dequeue(line+i); //대기열의 손님을 한 명 받는다.
					total_wait += clock - customer.arrival_time; //대기시간을 추가한다.
					service_time[i] = customer.service_time; //서비스 시간을 입력한다.
					service_customer[i] = customer.id; //고객 ID를 받는다.
					printf("(%d분)[System%d] 고객 [%d]님이 %d분에 서비스를 시작합니다.\n대기시간은 %d분 이었습니다.\n\n",
						clock,i+1, service_customer[i], clock, clock - customer.arrival_time);
					check++;
				}
			}
		}
		if (check > 0)printf("---------------------------------------------------\n\n"); //명령이 한 번이라도 실행되었다면 
		Sleep(1000);
	}
	for (int i = 0; i < employee; ++i) { //라인 수만큼 반복
		while(1) {
			if (!is_empty(line + i)) {
				//비어있지 않으면
				dequeue(line + i); //인원 빼줌
				remain_customers++; //남은 인원에 추가
			}
			else break;
		}
		if (service_time[i] > 0) remain_customers++; //서비스가 안 끝난 사람도 남은 인원
	}
	printf("총 대기시간: %d분\n 평균 대기시간: %d분\n남은 인원 수: %d명\n", total_wait,
		total_wait / total_customers,remain_customers);

	free(service_time);
	free(service_customer);
	free(line);
	return 0;
}

int line_count(QueueType* q, int* svctime, int n) { //제일 적은 줄을 골라냄
	int num = 0;
	int tmp = q[0].count;
	for (int i = 0; i < n; ++i) {
		if (q[i].count == 0 && svctime[i]==0) { //서비스를 받고있는 사람도 없고 줄도 없으면 그쪽으로 먼저
			num = i;
			break; //찾으면 바로 종료
		}
		if (tmp > q[i].count) { //제일 작은 요소 비교.
			tmp = q[i].count; //비교하는 수가 자기 자신보다 작을 때에만 넣음. 최솟값을 구하게 됨.
			num = i; //그 때의 i값을 가져옴.
		}
	}
	return num;
}

void init_all_Queue(QueueType* q,int num) {
	for (int i = 0; i < num; ++i) init_Queue(q + i); //n명의 큐 초기화
}