#define _CRT_SECURE_NO_WARNINGS
#include "mystack.h"
#define MAX 10

void create_maze(int (*maze)[MAX]); //미로
void print_maze(int(*maze)[MAX]); //미로 출력.
void run(); //미로찾기 실행
element get_Cordi(int x,int y); //좌표를 찍는 함수.
void write_value(int(*maze)[MAX], element cord); //값을 찍어주는 함수.
element get_pos(StackType* s); //현재 좌표를 가져오는 함수
int search(StackType *s, int(*maze)[MAX],element exit); 
//스택 맨 위에서 좌표를 꺼내고 쓴 뒤에 상하좌우를 검색해서 갈 수 있는 좌표를 스택에 쌓음.
//상: y-1 하: y+1  좌: x-1 우: x+1
boolean is_over(int x); //x값이 범위에서 벗어나는 지를 판단
//size: 10x10 size // 0은 막힌길 1은 갈 수 있는 길 2은 갔던 길
void print_cord(element pos); //현재 좌표위치.
void push_loc(StackType* s, int(*maze)[MAX],int x,int y); //푸시전 판별

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
	run();
	return 0;
}

void run() {
	int maze[MAX][MAX]; //10,10짜리 배열공간 생성
	StackType s; //좌표를 저장할 스택 생성
	init_stack(&s); //스택 초기화
	push(&s, get_Cordi(1, 0)); //초기 위치를 스택에 넣어줌.
	element exit = get_Cordi(7, 9); //출구 지정.
	//출구의 값을 따로 x라고 줘도 됨.
	create_maze(maze); //미로 생성
	print_maze(maze); //미로 출력
	if (search(&s, maze, exit)) printf("\n성공\n");
	else printf("\n실패\n");
}

boolean is_over(int x) {
	if (x < 0) return true; //0미만
	else if (x > 9) return true; //9초과
	else return false; //0이상 9이하
}

element get_pos(StackType* s) {
	return peek(s);
}

//상: y-1 하: y+1  좌: x-1 우: x+1

void push_loc(StackType* s, int(*maze)[MAX],int x, int y) {
	if (!is_over(x) && maze[x][y] != 2 && maze[x][y] == 1) push(s, get_Cordi(x, y));
}

int search(StackType* s, int(*maze)[MAX],element exit) {
	element pos = get_pos(s); //현재 좌표를 가져옴.
	write_value(maze, pop(s)); //초기 위치를 지정해 줌.
	print_maze(maze);
	while (pos.x!=exit.x || pos.y!=exit.y) { //현 위치가 출구랑 다르면
		push_loc(s,maze,pos.x,pos.y-1); //상
		push_loc(s, maze, pos.x, pos.y+1); //하
		push_loc(s, maze, pos.x-1, pos.y); //좌
		push_loc(s, maze, pos.x + 1, pos.y); //우
		//스택이 비어있다면
		if (is_empty(s)) return 0; //실패
		else { //스택 중 하나를 꺼내서 현재 위치로 만든다. 
			pos = peek(s); //현재 위치 저장.
			write_value(maze, pop(s)); //그리고 쓴뒤에
			print_maze(maze); //출력
		}
	}
	return 1; //성공
}

void print_cord(element pos) {
	printf("(%d, %d)\n", pos.x, pos.y);
}

void write_value(int(*maze)[MAX], element cord) {
	maze[cord.x][cord.y] = 2; //간 길이라고 표시.
}

element get_Cordi(int x,int y) {
	element z = { x,y };
	return z;
}

void print_maze(int(*maze)[MAX]) {
	int i, j;
	Sleep(1000); //1초 정지 후
	system("cls"); //기존에 있던 미로를 지움.
	for (i = 0; i < MAX; ++i) {
		for (j = 0; j < MAX; ++j) printf("%d ", maze[i][j]);
		printf("\n");
	}
}

void create_maze(int(*maze)[MAX]) {
	int i, j;
	for (i = 0; i < MAX; ++i) for (j = 0; j < MAX; ++j) maze[i][j] = 0; //초기화
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

