#include<stdio.h>
#define WHITE 0
#define BLACK 1

void print(); 
void part_fill();
void full_fill(int x,int y);
int read_pixel(int x, int y); //픽셀의 값을 반환
void write_pixel(int x, int y,int color); //픽셀에 값을 쓴다.
int area[10][10] = {0, };

int main(int argc, char* argv[]) {
	//영역채우기 알고리즘
	print();
	part_fill();
	print();
	full_fill(3,5);
	print();
	return 0;
}

void print() {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			printf("%d ", area[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void part_fill() {
	int i, j;
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 10; ++j)
			area[i][j] = BLACK;
	for (i = 3; i < 10; ++i)
		for (j = 0; j < 3; ++j)
			area[i][j] = BLACK;
	for (i = 4; i < 10; ++i)
		for (j = 8; j < 10; ++j)
			area[i][j] = BLACK;
	for (i = 5; i < 7; ++i)
		for (j = 3; j < 8; ++j)
			area[i][j] = BLACK;
}

int read_pixel(int x, int y) {
	return area[x][y];
}

void write_pixel(int x, int y, int color) {
	area[x][y] = color;
}

void full_fill(int x, int y) {
	if (read_pixel(x, y) == WHITE) { //흰색이면 색칠함
		write_pixel(x, y, BLACK);
		full_fill(x + 1, y);
		full_fill(x - 1, y);
		full_fill(x, y + 1);
		full_fill(x, y - 1);
	}
}