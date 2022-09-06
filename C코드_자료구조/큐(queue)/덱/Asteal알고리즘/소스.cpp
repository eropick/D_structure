#include"myDeque.h"
#include<time.h>

int main() {
	int n=0,count=0,index=0,end=0;
	int clock=0;
	int second = 60;
	int random=0;
	printf("Cpu�� ������ �Է�: ");
	scanf("%d", &n);
	DequeType* Cpu = (DequeType*)malloc(n * sizeof(DequeType));
	element* proc_time = (element*)malloc(n * sizeof(element));
	srand(time(NULL));
	if (Cpu == NULL) exit(-1);
	if (proc_time == NULL) exit(-1);
	for (int i = 0; i < n; ++i) {
		init_Deque(&Cpu[i]); //�ʱ�ȭ
		random = rand() % 8 + 1; //1~8������ ������ ����
		for (int j = 0; j < random; ++j){ //�� ������ �� cpu�� ����� �ʱ� ������ ��.
			add_rear(Cpu + i, rand() % 4 + 1); //����� ������ ó���ð��� ����.
			printf("\nCpu[%d]�� %d��° ��Ұ� �߰��Ǿ����ϴ�.\n",i,j+1);
		}
		printf("\n-----------------------------------------------------\n");
	}
	for (clock = 0; clock < second; ++clock) { //60�ʵ��� ����
		end = 0;
		for (int j = 0; j < n; ++j) {  //��� cpuŽ��
			if (proc_time[j] > 0) { //�� Cpu�� �۾����̶��
				printf("\n(%d��) Cpu %d�� �۾� �� �Դϴ�.[%d�� ����]\n",clock,j,proc_time[j]);
				proc_time[j]--; //0���� ũ�� -�� ��.
				end++;
			}
			else { //�۾����� �ƴ϶��
				if (is_empty(Cpu + j)){ //����ִ� ���
					count = 0;
					index = -1;
					for (int k = 0; k < n; ++k) { //��Ұ� ���� ���� ���� �ε����� ����
						if ((Cpu + k)->count > count) {
							count = (Cpu + k)->count; //ī��Ʈ�� �ְ�
							index = k; //�ε����� ������.
						}
					}
					if (index == -1) { //���� ��Ұ� ���ٸ�
						printf("\nCpu%d �۾� ����\n",j);
						continue; //-1�̸� �׳� �ѱ�.
					}
					printf("\n(%d��) Cpu %d�� �۾��� ��� Cpu %d���� �۾��� �����ɴϴ�.\n",clock,j, index);
					add_front(Cpu + j, delete_rear(Cpu + index)); //��Ұ� ���� ���� ���� rear�� �����ͼ� �տ� ����.
				}
				proc_time[j] = delete_front(Cpu + j); //����� ó���ð��� ��ȯ��.
				printf("\n(%d��) Cpu %d�� �۾��� �����մϴ�.[%d�� ����]\n", clock,j,proc_time[j]);
				end++;
			}
			printf("\n<Cpu%d�� �۾� ���>",j);
			deque_print(Cpu + j);
			printf("\n<Cpu%d�� ���� �۾� �ð�: %d��\n", j, proc_time[j]);
		}
		if (end == 0) {
			printf("\n�۾��� ��� ���� �����մϴ�.\n");
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