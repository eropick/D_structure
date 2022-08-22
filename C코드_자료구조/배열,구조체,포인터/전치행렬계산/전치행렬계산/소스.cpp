#include<stdio.h>
#define ROW 3
#define COL 3
#define MAX 100

//먼저 방법1 전통적인 행렬방식이다
void transpose_matrix1(int(*A)[COL],int(*B)[COL]);
void print_matrix1(int A[ROW][COL]);
//두번째 방법2 행,열,값을 갖는 구조체 배열를 만들어 사용한다.

typedef struct _element {
	int row;
	int col;
	int val;
}element;

typedef struct _SparseMatrix {
	element Matrix[100];
	int rows; //행의 개수
	int cols; //열의 개수
	int vals; //항의 개수
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
	단순히 이것도 행과 열을 교체해주면 되지만
	작은 행과 열에서 큰 행과 열 순서로 쌓아야 하기 때문에 고민이 필요하다.
	행과 열이 서로 바뀌기 때문에 0열을 처리하고 다음은 1열인 것을 처리하는 순서로 하면
	0행 1행 순서대로 쌓일 것이다.
*/

SparseMatrix transpose_matrix2(SparseMatrix x) {
	SparseMatrix tmp = { 0, };
	tmp.cols = x.cols;
	tmp.rows = x.rows;
	tmp.vals = x.vals;
	int tmpindex = 0;
	if (tmp.vals > 0) { //항이 있을 때만 실행
		for (int i = 0; i < x.cols; ++i) { //열을 기준으로 추출
			for (int j = 0; j < x.vals; ++j) { //0항부터 n항까지 쌓기 위함.
				if (x.Matrix[j].col == i) { //x의 0항부터 n항까지 중 i열과 같으면
					tmp.Matrix[tmpindex].row = x.Matrix[j].col; //x의 열을 tmp행으로 바꾼다.
					tmp.Matrix[tmpindex].col = x.Matrix[j].row; //x의 행을 tmp열로 바꾼다.
					tmp.Matrix[tmpindex].val = x.Matrix[j].val; //값을 할당한다.
					tmpindex++; //index를 1증가시킨다.
				}
			}
		}
	}
	return tmp;
}