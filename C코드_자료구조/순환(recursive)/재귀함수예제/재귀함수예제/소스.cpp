#include<stdio.h>

int sum(int n);
int recursive1(int n);
int recursive2(int n);
void recursive3(int n);
void asterisk(int i);
void unknown();
int custom_sum(int n);
double custom_sum2(int i);
int fibo(int n);
int ackermann(int m, int n); //��ȯ��Ŀ���Լ�
int Wackermann(int m,int n); //�ݺ���Ŀ���Լ�

int main(int argc, char* argv[]) {
	printf("��ȯ����: %d\n", sum(5));
	//5~0���� ī��Ʈ�� ���� ��ȯ���� 5+4+3+2+1+1�̴�.
	printf("��ȯ����: %d\n", recursive1(5));
	/*5~0���� ī��Ʈ�� ���� ��ȯ���� n�� 0���� �پ�� ���� ��������
	=2*(2*(2*(2*(2*2+1)+1)+1)+1)+1 �̷��� ���¸� ���.
	=2*(2*(2*(2*5+1)+1)+1)+1
	=2*(2*(2*11+1)+1)+1
	=2*(2*23+1)+1
	=2*47+1
	=95
	*/
	printf("��ȯ����: %d\n", recursive2(10));
	/*10,7,4,1,-2 ������ -3�� �� ���� ��µȴ�. ��ȯ���� n=-2�� �� ��������
	(-1+1)+1+1+1�� ��ȯ���� 4�� +1�� �ȴ�.
	=3
	*/
	recursive3(5);
	/* n�� 1�� �ƴϸ� n - 1�� ����ؼ� �Լ��� ȣ����.
	���⿡�� n�� 1�� �Ǵ� ���� ����� �ϰ� �Լ�����
	���� �Լ��� �ּ� ���� �׸��� 2���...5���� ��� ���� 1~5���� ������� */
	asterisk(5);
	/* i�� 1���� ũ�� i���� �������� ������ �ٽ� �Լ��� �� �� ȣ����. 
	5��� 5/2 = asterisk(2)�� �� �� ȣ��.
	asterisk(2)�� ���� 2/2 = asterisk(1)�� ���� �� �� ȣ��
	asterisk(1)�� if�� �������� �����Ƿ� *�� �� ���� ��� *4��
	��� �� ���� asterisk(2)�� *��� �� ���� �� ��° asterisk(2)�� *��� �� ����
	������ asterisk(5)�� * ��� �� ����� �� �ϰ����� *�� ��µ�.
	���� *******�� ���´�.
	*/
	printf("\n");
	unknown();
	/* ������ �Լ��� �Է��� ���۽�Ʈ������ ���ڸ� �ϳ��޾Ƽ� �װ� ������ �ƴϸ�
	�ٽ� �ڱ��ڽ��� ȣ���ϴ� �Լ��ε� ���ڹ��۽�Ʈ������ �������� ������ ������
	��ȯȣ���� �̷������ �ʰ� ���๮�ڸ� ���� ����� �� ���ʴ�� �Լ� ȣ���� ����Ǹ鼭
	���ڸ� �Է��� �ݴ� ������ �ϳ��� ��µǴ� �۾��� �̷��.
	���� �� �� ������ �� ���ڰ� �Ųٷ� ��µȴ�.
	*/
	printf("\n1~5������ ��: %d\n",custom_sum(5));
	//������ 1+2+...+n������ ���� ���ϴ� ��ȯ�Լ���.
	printf("1~1/5������ ��: %.2lf\n", custom_sum2(5));
	//������ 1+1/2+...+1/n������ ���� ���ϴ� ��ȯ�Լ���.
	fibo(3);
	//������ �Ǻ���ġ������ �Լ� ��ȯ������ �����ϱ� ���� �Լ���.
	printf("��Ŀ���Լ�: %d\n",ackermann(0, 0));
	//������ �Է��� ���� ��� �ſ� ������ �����ϴ� ��Ŀ���Լ���.
	printf("��Ŀ���Լ�: %d\n",Wackermann(0, 0));
}

int Wackermann(int m, int n) { //�ݺ���Ŀ���Լ�
	int stackm[10000]={0,}; //m�� ���� �Ҵ�� �迭�����̴�. ����� ũ�� �������.
	int head = -1; //������ head�̴�. �⺻���� -1���� �����ؼ� �߰��ɶ����� +1
	while (n >= 0 && m >= 0)
	{
		if (m == 0 && n > 0) {
			if (head != -1) m = stackm[head--]; //������ �ִٸ� �������� ������ �ϳ�����
			else {
				n++;
				break;
			} // m�� 0�ε� ������ ������ n�� ���� �� ����
			n++; //n�ǰ� 1����
		}
		else if (m > 0 && n == 0)
		{
			--m; //m�� 1�� ����
			n = 1; //n�� ���� 1�� ����
		}
		else if (n > 0 && m > 0) {
			stackm[++head] = m - 1; //head�� m-1����
			--n; //n���� 1��
		}
		else break;
	}
	return n;
}

int ackermann(int m, int n) { //��ȯ��Ŀ���Լ�
	if (m == 0 && n > 0) return n + 1;
	else if (m > 0 && n == 0) return ackermann(m - 1, 1);
	else if (n > 0 && m > 0) return ackermann(m - 1, ackermann(m, n - 1));
	else return 0;
}

/*
A(2,2)
(1,(2,1))
(1,(1,(2,0)))
(1,(1,(1,1)))
(1,(1,(0,(1,0))))
(1,(1,(0,(0,1))))
(1,(1,(0,2)))
(1,(1,3))
(1,(0,(1,2)))
(1,(0,(0,(1,1))))
(1,(0,(0,(0,(1,0)))))
(1,(0,(0,(0,(0,1)))))
(1,5)
(0,(0,(0,(0,(1,1))))))
(0,(0,(0,(0,(0,(1,0)))))))
(0,(0,(0,(0,(0,(0,1)))))))
=7
*/

int fibo(int n) {
	printf("fibo(%d) is called\n", n);
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return fibo(n - 1) + fibo(n - 2);
	//fibo(n-1) ���� ���� �� ���� ������ n-2�� ����Ǵ� ���´�.
	//���� �ٲ۴ٸ� ȣ�� ������ �޶�����.
}

int custom_sum(int n) {
	if (n == 1) return 1;
	else return n + custom_sum(n - 1);
}

double custom_sum2(int i) {
	if (i == 1) return 1;
	else return 1.0 / i + custom_sum2(i - 1);
}

int sum(int n) {
	printf("%d\n", n);
	if (n < 1) return 1;
	else return(n+sum(n-1));
}

int recursive1(int n) {
	printf("%d\n", n);
	if (n < 1) return 2;
	else return (2 * recursive1(n - 1) + 1);
}

int recursive2(int n) {
	printf("%d\n", n);
	if (n < 1) return -1;
	else return ( recursive2(n - 3)+1);
}

void recursive3(int n) {
	if (n != 1) recursive3(n-1);
	printf("%d\n", n);
}

void asterisk(int i) {
	if (i > 1) {
		asterisk(i / 2);
		asterisk(i / 2);
	}
	printf("*");
}

void unknown() {
	int ch;
	if ((ch = getchar()) != '\n') unknown();
	putchar(ch);
}