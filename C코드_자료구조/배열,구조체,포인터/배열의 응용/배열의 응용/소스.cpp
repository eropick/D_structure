#include<stdio.h>
#define MAX_DEGREE 101
#define LARGE_DEGREE(a,b) ((a)>(b))?(a):(b)

//�ܼ��� �迭�� �̿��� ���׽� ����ó���ε�
/*
�迭�� �Ķ���ͷ� �ѱ� ���� ���� �ּ�, �����ͷ� ó�����ִ��Ϳ� ���� Call by reference
����ü�� �Ķ���ͷ� �ѱ� ���� ����ü �ȿ� �迭 ����� ���� �״�� �Ѿ�� ������
Call by value�� �����ϴ�.
*/

typedef struct _polynomial {
	int degree; //���׽� ����
	int coef[MAX_DEGREE]; //���׽� ���
}polynomial;

void print_poly(polynomial p);
polynomial add(polynomial x, polynomial y);
void add2(int x[10], int y[10]);

//�迭�� ����ü�� �����ؼ� ���׽��� ������ ó���غ���
//3x^5 + 2x^3 + 1 �� 2x^4 + 10x �� �����̴�. 
int main(int argc, char* argv[]) {
	polynomial a = { 5,{3,0,2,0,0,1} };
	polynomial b = { 4,{2,0,0,10,0} };
	polynomial c;
	print_poly(a);
	print_poly(b);
	c=add(a, b);
	printf("\n-------------------------\n");
	print_poly(c);
	return 0;
}


void print_poly(polynomial p) {
	for (int i = 0; i <= p.degree; ++i) {
		if (i == p.degree && p.coef[i]!=0) { //����̰� 0�� �ƴ� ��� 
			printf("%d\n", p.coef[i]); //����� 0�� �ƴ� ���
			break; //�ݺ���
		}
		else if(p.coef[i]!=0) printf("%dx^%d", p.coef[i], p.degree - i); //0�� �ƴ� �� 
		if (p.coef[i + 1] != 0) printf("+"); //�������� 0�� �ƴ� ��츸 +�� �� ��.
	}
}

polynomial add(polynomial x, polynomial y) {
	polynomial C;
	int xpos = 0, ypos = 0, cpos = 0;
	int xdegree = x.degree;
	int ydegree = y.degree;
	C.degree = LARGE_DEGREE(xdegree, ydegree); //�ְ������� �Ҵ�
	while (xpos <= x.degree && ypos <= y.degree){ //��ġ�� ������ �� ������ �ݺ�
		if (xdegree > ydegree) { //x������ �� ū ���
			C.coef[cpos++] = x.coef[xpos++]; //x����� c����� �ְ� ������ ����
			xdegree--; //x��������
		}
		else if (xdegree == ydegree) { //�� ������ ���� ���
			C.coef[cpos++] = x.coef[xpos++] + y.coef[ypos++]; //�� ���� ����
			xdegree--; //x,y��������
			ydegree--;
		}
		else { //y������ �� ū ���
			C.coef[cpos++] = y.coef[ypos++]; //y����� c����� �ְ� ������ ����
			ydegree--; //y��������
		}
	}
	return C;
}