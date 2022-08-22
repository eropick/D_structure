#include<stdio.h>
#define ROW 3
#define COL 3
#define MAX 100

//���� ���1 �������� ��Ĺ���̴�
void transpose_matrix1(int(*A)[COL],int(*B)[COL]);
void print_matrix1(int A[ROW][COL]);
//�ι�° ���2 ��,��,���� ���� ����ü �迭�� ����� ����Ѵ�.

typedef struct _element {
	int row;
	int col;
	int val;
}element;

typedef struct _SparseMatrix {
	element Matrix[100];
	int rows; //���� ����
	int cols; //���� ����
	int vals; //���� ����
}SparseMatrix;

SparseMatrix transpose_matrix2(SparseMatrix x);
void print_matrix2(SparseMatrix x);

int main(int argc, char* argv[]) {
	int matrixA[ROW][COL] = { {2,3,0},
							{8,0,1},
							{0,2,1} };
	int matrixB[ROW][COL] = { 0, };
	SparseMatrix A = { {{0,0,2},{0,1,3},{1,0,8},{1,2,1},{2,1,2},{2,2,1}},
						ROW,COL,6 };
	SparseMatrix result = { 0, };
	transpose_matrix1(matrixA, matrixB);
	print_matrix1(matrixA);
	print_matrix1(matrixB);
	result = transpose_matrix2(A);
	print_matrix2(result);
	return 0;
}

void transpose_matrix1(int(*A)[COL], int(*B)[COL]) {
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COL; ++j)
			B[i][j] = A[j][i];
}

void print_matrix1(int A[ROW][COL]) {
	printf("==========\n");
	for (int i = 0; i < ROW; ++i){
		for (int j = 0; j < COL; ++j) printf("%d ", A[i][j]);
		printf("\n");
	}
	printf("==========\n");
}

void print_matrix2(SparseMatrix x) {
	for (int i = 0; i < x.vals; ++i) {
		printf("(%d, %d, %d)\n", x.Matrix[i].row, x.Matrix[i].col, x.Matrix[i].val);
	}
	printf("==========\n");
}

/*
	�ܼ��� �̰͵� ��� ���� ��ü���ָ� ������
	���� ��� ������ ū ��� �� ������ �׾ƾ� �ϱ� ������ ����� �ʿ��ϴ�.
	��� ���� ���� �ٲ�� ������ 0���� ó���ϰ� ������ 1���� ���� ó���ϴ� ������ �ϸ�
	0�� 1�� ������� ���� ���̴�.
*/

SparseMatrix transpose_matrix2(SparseMatrix x) {
	SparseMatrix tmp = { 0, };
	tmp.cols = x.cols;
	tmp.rows = x.rows;
	tmp.vals = x.vals;
	int tmpindex = 0;
	if (tmp.vals > 0) { //���� ���� ���� ����
		for (int i = 0; i < x.cols; ++i) { //���� �������� ����
			for (int j = 0; j < x.vals; ++j) { //0�׺��� n�ױ��� �ױ� ����.
				if (x.Matrix[j].col == i) { //x�� 0�׺��� n�ױ��� �� i���� ������
					tmp.Matrix[tmpindex].row = x.Matrix[j].col; //x�� ���� tmp������ �ٲ۴�.
					tmp.Matrix[tmpindex].col = x.Matrix[j].row; //x�� ���� tmp���� �ٲ۴�.
					tmp.Matrix[tmpindex].val = x.Matrix[j].val; //���� �Ҵ��Ѵ�.
					tmpindex++; //index�� 1������Ų��.
				}
			}
		}
	}
	return tmp;
}