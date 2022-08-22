#include<stdio.h>
#define SIZE 101

typedef struct _polynomial {
	int degree;
	double coef;
}polynomial;


void print_poly(polynomial* x);
void poly_sum(polynomial* x, polynomial* y);
polynomial result[SIZE] = { {0,0} }; //�ʱ�ȭ

//a,b���� �Űܼ� ���� �������� ���� �� ���߿� �ٸ� �������� �����ִ� ����� ���Ѵ�.

int main(int argc, char* argv[]) {
	polynomial a[SIZE] = { {5,1},{3,4},{1,5} }; 
	polynomial b[SIZE] = { {0,1},{2,6},{4,9},{3,4} };
	print_poly(a);
	print_poly(b);
	poly_sum(a, b);
	printf("-------------------------------\n");
	print_poly(result);
	return 0;
}

void poly_sum(polynomial* x, polynomial* y) {
	int count,i,j;
	int resultc = -1;
	polynomial tmp[SIZE]{ {0,0} }; //y�� ���� �ű�� ����.
	//���� result�� �� �� ���� ���� �Ҵ���
	for (i = 0; i < SIZE; ++i) {
		if(x[i].coef == 0 && x[i].degree == 0) break; //�������� �����ϰ�
		else {
			result[i].coef = x[i].coef; //����Ҵ�
			result[i].degree = x[i].degree; //�����Ҵ�
		}
		resultc++; //result�� �װ����� ����
	}
	for (i = 0; i < SIZE; ++i) {
		if (y[i].coef == 0 && y[i].degree == 0) break; //�������� �����ϰ�
		else {
			tmp[i].coef = y[i].coef; //����Ҵ�
			tmp[i].degree = y[i].degree; //�����Ҵ�
		}
	}

	for (i = 0; i < SIZE; ++i) { //result�� ���� ������ 
		if (result[i].coef == 0 && result[i].degree==0) break;
		for (j = 0; j < SIZE; ++j) { //y�� ���� ���ؼ� ����
			if(tmp[j].coef == 0 && tmp[j].degree == 0) break; //y�� ������ Ż��
			else if (result[i].degree == tmp[j].degree) { //�� �� ������ ���� ���
				result[i].coef += tmp[j].coef;
				tmp[j].coef = 0; //������ ���� ��� result�� ���Ĺ����� 
				tmp[j].degree = -1; //����� 0 ������ -1�� ����.
			}
		}
	}
	for (i = 0; i < SIZE; ++i) {
		if (tmp[i].coef == 0 && tmp[i].degree == 0) break;
		else if (tmp[i].coef == 0 && tmp[i].degree == -1) continue; //���� ���������� ��������
		else { //�ٸ� ������ ��� �߰����ش�.
			result[++resultc].coef = tmp[i].coef;
			result[resultc].degree = tmp[i].degree;
		}
	}
}

void print_poly(polynomial* x) {
	//���� Ž���� ���� ������ ��.
	int count,i,j;
	polynomial t[SIZE]; //������ ���� �迭;
	for (i = 0; i < SIZE; ++i) {  //ù ��° �� ����
		count = 0;
		if (x[i].coef == 0) {
			--i;
			break; //�������� �Ǹ� ��������
		}
		for (j = 0; j < SIZE; ++j) { //������ ��
			if (x[j].coef == 0) break; //���������� Ž���ϸ� ��������.
			else if (x[i].degree > x[j].degree) count++; //������ ���� �񱳴�󺸴� ũ�� �ε�������.
		}
		t[count].coef = x[i].coef;
		t[count].degree = x[i].degree;
	}
	//������ i�ε����� �������Ƿ�
	for (j = i; j >= 0; --j) {
		if (t[j].degree == 0) printf("%.1lf", t[j].coef); //������ ����� ���
		else if (j == 0) printf("%.1lfx^%d", t[j].coef, t[j].degree); //������ ����� �ƴ� ���̶��
		else printf("%.1lfx^%d + ", t[j].coef, t[j].degree); //����� ������ ���� �ƴ϶�� ���x^���� 
	}
	printf("\n");
}