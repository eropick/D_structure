#include "myQue.h"
#include<time.h>

int main(int argc, char** argv) {
	QueueType line;
	init_Queue(&line);
	int total_wait = 0; //�� ���ð�
	int total_customers = 0; //�� ����
	int service_time = 0; //���� ���� �ð��� ��
	int service_customer = 0; //�� ID�� ��
	int minute = 60;
	int clock;
	int check; //����� ����Ǿ����� üũ��.
	int remain_customers = 0; //���� ��
	srand(time(NULL));
	for (clock = 0; clock < minute; ++clock) {
		check = 0;
		//0~10������ ���� 3���϶�� ���� �� ������ ó��
		if (rand() % 11 <= 3) {
			element customer = { ++total_customers, clock, rand() % 3 + 1 }; //������
			//��⿭�� ����
			enqueue(&line, customer);
			printf("(%d��)[System] [%d]���� %d�п� ��⿭�� ���ɴϴ�.(����ó���ð�=%d��)\n\n", 
				clock,customer.id, customer.arrival_time, customer.service_time);
			check++;
		}
		//���� ���񽺸� �ް��ִٸ� ���� �ð��� ���δ�.
		if (service_time > 0) {
			printf("(%d��)[System] �� [%d]���� ���� ó�����Դϴ�.\n\n",clock,service_customer);
			service_time--;
			check++;
		}
		else { //���񽺸� �ް��ִ� ���� ���ٸ�
			if (!is_empty(&line)) { //��⿭�� �� �ִٸ�
				element customer = dequeue(&line); //��⿭�� �մ��� �� �� �޴´�.
				total_wait += clock - customer.arrival_time; //���ð��� �߰��Ѵ�.
				service_time = customer.service_time; //���� �ð��� �Է��Ѵ�.
				service_customer = customer.id; //�� ID�� �޴´�.
				printf("(%d��)[System] �� [%d]���� %d�п� ���񽺸� �����մϴ�.\n���ð��� %d�� �̾����ϴ�.\n\n",
					clock,service_customer, clock, clock - customer.arrival_time);
				check++;
			}
		}
		if(check > 0 )printf("----------------------------------------\n\n");
		Sleep(1000);
	}
	for (int i = 0; ; ++i) {
		if (!is_empty(&line)) {
			//������� ������
			dequeue(&line); //�ο� ����
			remain_customers++; //���� �ο��� �߰�
		}
		else break;
	}
	if(service_time>0) remain_customers++; //���񽺰� �� ���� ����� ���� �ο�
	printf("�� ���ð�: %d��\n ��� ���ð�: %d��\n���� �ο� ��: %d��\n", total_wait, 
		total_wait/total_customers,remain_customers);
	return 0;
}