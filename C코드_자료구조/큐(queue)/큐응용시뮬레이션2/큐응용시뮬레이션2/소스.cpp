#include "myQue.h"
#include<time.h>

void init_all_Queue(QueueType* q, int num); //��� ť �ʱ�ȭ
int line_count(QueueType* q, int* svctime,int n); //���� ���� ť�� �޾� ���� ���� ���� �߷���

//ť�� n�� ����. ������ n���̹Ƿ� ���� �ð��� ���� ���� n������ ó��.
//�����Ҵ��� ���.
//������ ����1���� ���� �ùķ��̼��� n���� ���� �ùķ��̼����� ����

int main(int argc, char** argv) {
	int employee;
	int clock, minute = 60;
	int check; //����� ����Ǿ����� üũ��.
	int total_wait = 0; //�� ���ð�
	int total_customers = 0; //�� ����
	int remain_customers = 0; //���� ��
	int min_customers=0; //�ּ��ο�
	printf("���� ���� �Է��ϼ���: ");
	scanf("%d", &employee);
	QueueType* line = (QueueType*)malloc(employee*sizeof(QueueType)); //���� ����ŭ �����Ҵ�.
	int* service_time = (int*)malloc(employee * sizeof(int)); //���� ����ŭ �����Ҵ�.
	int* service_customer = (int*)malloc(employee * sizeof(int)); //���� ����ŭ �����Ҵ�.
	init_all_Queue(line, employee); //��� ť �ʱ�ȭ
	srand(time(NULL));
	for (clock = 0; clock < minute; ++clock) { //���� �ݺ� ����.
		check = 0;
		//0~10������ ���� 3���϶�� ���� �� ������ ó��
		if (rand() % 11 <= 3) {
			element customer = { ++total_customers, clock, rand() % 3 + 1 }; //������
			min_customers = line_count(line,service_time,employee); 
			//��⿭�� ��� �ο��� ����ؼ� ���� ���� ��⿭�� ��ȯ
			enqueue(line+min_customers, customer); //���� ���� ��⿭�� ������ ����
			printf("(%d��)[System] �� [%d]���� %d�п� ��⿭%d�� ���ɴϴ�.(����ó���ð�=%d��)\n\n",
				clock, customer.id, customer.arrival_time, min_customers+1,customer.service_time);
			check++;
		}
		//���� ���񽺸� �ް��ִٸ� ���� �ð��� ���δ�.
		//��� �ٿ� ���ؼ� ���� ���θ� �ľ�)
		for (int i = 0; i < employee; ++i) {
			if (service_time[i] > 0) {
				printf("(%d��)[System%d] �� [%d]���� ���� ó�����Դϴ�.\n\n", clock,i+1, service_customer[i]);
				service_time[i]--;
				check++;
			}
			else { //���񽺸� �ް��ִ� ���� ���ٸ�
				if (!is_empty(line+i)) { //��⿭�� �� �ִٸ�
					element customer = dequeue(line+i); //��⿭�� �մ��� �� �� �޴´�.
					total_wait += clock - customer.arrival_time; //���ð��� �߰��Ѵ�.
					service_time[i] = customer.service_time; //���� �ð��� �Է��Ѵ�.
					service_customer[i] = customer.id; //�� ID�� �޴´�.
					printf("(%d��)[System%d] �� [%d]���� %d�п� ���񽺸� �����մϴ�.\n���ð��� %d�� �̾����ϴ�.\n\n",
						clock,i+1, service_customer[i], clock, clock - customer.arrival_time);
					check++;
				}
			}
		}
		if (check > 0)printf("---------------------------------------------------\n\n"); //����� �� ���̶� ����Ǿ��ٸ� 
		Sleep(1000);
	}
	for (int i = 0; i < employee; ++i) { //���� ����ŭ �ݺ�
		while(1) {
			if (!is_empty(line + i)) {
				//������� ������
				dequeue(line + i); //�ο� ����
				remain_customers++; //���� �ο��� �߰�
			}
			else break;
		}
		if (service_time[i] > 0) remain_customers++; //���񽺰� �� ���� ����� ���� �ο�
	}
	printf("�� ���ð�: %d��\n ��� ���ð�: %d��\n���� �ο� ��: %d��\n", total_wait,
		total_wait / total_customers,remain_customers);

	free(service_time);
	free(service_customer);
	free(line);
	return 0;
}

int line_count(QueueType* q, int* svctime, int n) { //���� ���� ���� ���
	int num = 0;
	int tmp = q[0].count;
	for (int i = 0; i < n; ++i) {
		if (q[i].count == 0 && svctime[i]==0) { //���񽺸� �ް��ִ� ����� ���� �ٵ� ������ �������� ����
			num = i;
			break; //ã���� �ٷ� ����
		}
		if (tmp > q[i].count) { //���� ���� ��� ��.
			tmp = q[i].count; //���ϴ� ���� �ڱ� �ڽź��� ���� ������ ����. �ּڰ��� ���ϰ� ��.
			num = i; //�� ���� i���� ������.
		}
	}
	return num;
}

void init_all_Queue(QueueType* q,int num) {
	for (int i = 0; i < num; ++i) init_Queue(q + i); //n���� ť �ʱ�ȭ
}