#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int factorial(int n);
double slow_power1(double n,int m); //��ȯ �ŵ�����
double slow_power2(double n, int m); //��ȯ �ŵ�����
double fast_power(double n, int m); //�ݺ� �ŵ�����
int fibonacci(int n); //��ȯ �Ǻ���ġ
void hanoi_tower(int n,char from,char tmp,char to); //��ȯ �ϳ���
int bino_coef(int n, int k);

int main() {
	int n;
	double x;
	//����Լ� ���� ���丮��
	printf("���ڸ� �Է��ϼ���!: ");
	scanf("%d", &n);
	//printf("%d!�� %d�Դϴ�\n", n, factorial(n)); ���丮��
	//printf("%.1lf�� 10���� %.1lf", x,slow_power1(x, 10)); ��ȯ �ŵ�����
	//printf("%.1lf�� 10���� %.1lf", x, fast_power(x, 10)); �ݺ� �ŵ�����
	//printf("%d�� �Ǻ���ġ ����: %d", n, fibonacci(n)); ��ȯ �Ǻ���ġ ����
	//hanoi_tower(n, 'A', 'B', 'C'); ��ȯ �ϳ���ž
	//printf("���װ��: %d ",bino_coef(5, 2)); ��ȯ ���װ��
	return 0;
}

int bino_coef(int n, int k) {
	if (k == 0 || k == n) return 1;
	else if (k > 0 && k < n) return bino_coef(n - 1, k - 1) + bino_coef(n - 1, k);
}

int factorial(int n) {
	printf("factorial(%d)\n", n); //��ȯ�� ��� �̷�������� �����ش�.
	if (n >= 1) return n * factorial(n - 1);
	else return 1;
}

//��ȯ���� �ŵ������� ����Ѵ�.
double slow_power1(double n,int m) {
	if (m == 0) return 1;
	else if(m%2==0) //¦��
		return slow_power1(n*n, m/2);
	else if(m%2==1) //Ȧ��
		return n*slow_power1(n*n, (m-1)/ 2);
	//�ŵ����� Ƚ���� ¦���� ���� �׳� m�� ũ�⸸ �������� ���ְ�
	//n�� '����'�ؼ� ȣ���ߴٰ� m�� ���� Ȧ�� �� �� ������ ���� �����ִ� ������� �̾���.
}
double slow_power2(double n, int m) {//��ȯ �ŵ�����
	if (m == 0) return 1;
	else return n*slow_power2(n, --m);
} 

double fast_power(double n, int m) { //�ݺ� �ŵ�����
	double mul = 1;
	for (int i = 0; i < m; ++i) {
		mul = mul * n;
	}
	return mul;
}

int fibonacci(int n) { //�Ǻ���ġ ������ ��ȯ���� ���غ���
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return fibonacci(n - 2) + fibonacci(n - 1);
}

void hanoi_tower(int n, char from, char tmp, char to) {
	//���� �⺻���� ���·� ������ 1����� from���� to�θ� �ű�� �ȴ�.
	//���� ���� ���� �׻� �� ���� �����Ƿ� ����1�� �׻� �̵��� �ȴ�.
	if (n == 1) printf("����1�� %c���� %c�� �̵��߽��ϴ�.\n", from, to);
	else {
		//(n>1)�� ��쿡�� ������ ������ ������ n-1�� �ϴ� from���� tmp�� �Űܾ� �Ѵ�.
		hanoi_tower(n - 1, from, to, tmp);
		//�������� ���� ����n�� to�� �ű��.
		printf("����%d�� %c���� %c�� �̵��߽��ϴ�.\n", n, from, to);
		//tmp�� �ִ� n-1�� ������ tmp���� to�� �ű��.
		hanoi_tower(n - 1, tmp, from, to);
		/*
		�׷��ٸ� �� n-1�� ������ ��� �ű�°�? -> �̰� ��ȯ���� �ذ��ϴ� ��.
		n���� ������ �ű�� �;ȿ� n-1���� ������ �ű�� �� 
		n-1���� ������ �ű�� �;ȿ� n-2���� ������ �ű�� ��...
		1���� ������ �ű�� ������ ���� �پ��� �����̴�.
		*/
	}
}
//ex) fibonacci(6)�� �ش��ϴ� ���� ���Ѵٰ��ϸ�
/* fibonacci(4) + fibonacci(5) �� ��������
fibonacci(4) -> fibonacci(2)+fibonacci(3) ���� ������
fibonacci(5) -> fibonacci(3) + fibonacci(4)�� ����������.
�̷��� �ߺ��� ȣ���� ������ �����.
�̸� �ð� ���⵵�� ���� �� �� ȣ�⸶�� 2���� ȣ���� �߰������� �����.
O(2^n)�� �ȴ�.
*/