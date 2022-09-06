#include"myDeque.h"
#include<time.h>

int main() {
	int n=0,count=0,index=0,end=0;
	int clock=0;
	int second = 60;
	int random=0;
	printf("Cpu의 개수를 입력: ");
	scanf("%d", &n);
	DequeType* Cpu = (DequeType*)malloc(n * sizeof(DequeType));
	element* proc_time = (element*)malloc(n * sizeof(element));
	srand(time(NULL));
	if (Cpu == NULL) exit(-1);
	if (proc_time == NULL) exit(-1);
	for (int i = 0; i < n; ++i) {
		init_Deque(&Cpu[i]); //초기화
		random = rand() % 8 + 1; //1~8사이의 난수를 생성
		for (int j = 0; j < random; ++j){ //이 난수는 각 cpu에 요소의 초기 개수가 됨.
			add_rear(Cpu + i, rand() % 4 + 1); //요소의 랜덤한 처리시간을 넣음.
			printf("\nCpu[%d]의 %d번째 요소가 추가되었습니다.\n",i,j+1);
		}
		printf("\n-----------------------------------------------------\n");
	}
	for (clock = 0; clock < second; ++clock) { //60초동안 진행
		end = 0;
		for (int j = 0; j < n; ++j) {  //모든 cpu탐색
			if (proc_time[j] > 0) { //현 Cpu가 작업중이라면
				printf("\n(%d초) Cpu %d가 작업 중 입니다.[%d초 남음]\n",clock,j,proc_time[j]);
				proc_time[j]--; //0보다 크면 -빼 줌.
				end++;
			}
			else { //작업중이 아니라면
				if (is_empty(Cpu + j)){ //비어있는 경우
					count = 0;
					index = -1;
					for (int k = 0; k < n; ++k) { //요소가 가장 많은 곳의 인덱스를 구함
						if ((Cpu + k)->count > count) {
							count = (Cpu + k)->count; //카운트를 넣고
							index = k; //인덱스를 저장함.
						}
					}
					if (index == -1) { //전부 요소가 없다면
						printf("\nCpu%d 작업 종료\n",j);
						continue; //-1이면 그냥 넘김.
					}
					printf("\n(%d초) Cpu %d에 작업이 비어 Cpu %d에서 작업을 가져옵니다.\n",clock,j, index);
					add_front(Cpu + j, delete_rear(Cpu + index)); //요소가 가장 많은 곳의 rear를 가져와서 앞에 붙임.
				}
				proc_time[j] = delete_front(Cpu + j); //요소의 처리시간을 반환함.
				printf("\n(%d초) Cpu %d가 작업을 시작합니다.[%d초 남음]\n", clock,j,proc_time[j]);
				end++;
			}
			printf("\n<Cpu%d의 작업 출력>",j);
			deque_print(Cpu + j);
			printf("\n<Cpu%d의 남은 작업 시간: %d초\n", j, proc_time[j]);
		}
		if (end == 0) {
			printf("\n작업이 모두 끝나 종료합니다.\n");
			free(Cpu);
			free(proc_time);
			exit(1);
		}
		printf("\n-----------------------------------------------------\n");
		Sleep(1000);
	}
	free(Cpu);
	free(proc_time);
	return 0;
}