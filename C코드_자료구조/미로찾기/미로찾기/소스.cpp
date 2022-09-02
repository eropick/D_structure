#define _CRT_SECURE_NO_WARNINGS
#include "mystack.h"

void create_maze(int (*maze)[10]); //미로
void print_maze(int(*maze)[10]);
element Curen_Cordi(int x,int y); //현재 좌표를 찍는 함수.

//size: 10x10 size // 0은 막힌길 1은 갈 수 있는 길 -1은 갔던 길

/*
0 0 0 0 0 0 0 0 0 0 
1 1 1 1 1 1 0 1 1 0 
0 0 1 0 1 0 0 1 0 0
0 0 0 0 1 0 0 1 0 0
0 0 0 0 1 1 1 1 0 0
0 0 0 0 1 0 0 1 0 0
0 0 0 0 1 0 0 1 0 0
0 0 0 0 0 0 0 1 1 1
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
*/

int main(int argc, char** argv) {
	int maze[10][10];
	create_maze(maze);
	print_maze(maze);
	element item = Curen_Cordi(0, 3);
	return 0;
}

element Curen_Cordi(int x,int y) {
	element z = { x,y };
	return z;
}

void print_maze(int(*maze)[10]) {
	int i, j;
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) printf("%d ", maze[i][j]);
		printf("\n");
	}
}

void create_maze(int(*maze)[10]) {
	int i, j;
	for (i = 0; i < 10; ++i) for (j = 0; j < 10; ++j) maze[i][j] = 0; //초기화
	for (j = 0; j < 6; ++j) maze[1][j] = 1; //0~5까지 1
	maze[1][7] = 1; 
	maze[1][8] = 1;
	maze[2][2] = 1;
	maze[4][5] = 1;
	maze[4][6] = 1;
	maze[7][7] = 1;
	maze[7][8] = 1;
	maze[7][9] = 1;
	for (i = 2; i < 7; ++i) {
		maze[i][4] = 1;
		maze[i][7] = 1;
	}
}

