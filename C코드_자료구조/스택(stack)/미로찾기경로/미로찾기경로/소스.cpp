#define _CRT_SECURE_NO_WARNINGS
#include "mystack.h"
#define MAX 10

void create_maze(int(*maze)[MAX]); //미로
void print_maze(int(*maze)[MAX]); //미로 출력.
void run(); //미로찾기 실행
element get_Cordi(int x, int y, int flag); //좌표를 찍는 함수.
void write_value(int(*maze)[MAX], element cord); //값을 찍어주는 함수.
element get_pos(StackType* s); //현재 좌표를 가져오는 함수
int search(StackType* s, int(*maze)[MAX], element exit);
//스택 맨 위에서 좌표를 꺼내고 쓴 뒤에 상하좌우를 검색해서 갈 수 있는 좌표를 스택에 쌓음.
//상: y-1 하: y+1  좌: x-1 우: x+1
boolean is_over(int x); //x값이 범위에서 벗어나는 지를 판단
//size: 10x10 size // 0은 막힌길 1은 갈 수 있는 길 2은 갔던 길
void print_cord(element pos); //현재 좌표위치.
int push_loc(StackType* s, int(*maze)[MAX], int x, int y); //푸시전 판별
void path(StackType* s); //스택을 조사해서 flag가 1인 스택만을 표시하면 경로가 됨. 
element change_flag(element x); //flag변경

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
	push(&s, get_Cordi(1, 0, 0)); //초기 위치를 스택에 넣어줌.
	element exit = get_Cordi(7, 9, 0); //출구 지정.
	//출구의 값을 따로 x라고 줘도 됨.
	create_maze(maze); //미로 생성
	print_maze(maze); //미로 출력
	if (search(&s, maze, exit)) printf("\n성공\n");
	else printf("\n실패\n");
	path(&s);
}

boolean is_over(int x) {
	if (x < 0) return true; //0미만
	else if (x > 9) return true; //9초과
	else return false; //0이상 9이하
}

void path(StackType* s) {
	StackType p;
	init_stack(&p);
	while (!is_empty(s)) { //스택이 빌때까지 반복
		if (peek(s).flag == 1)	push(&p, pop(s)); //flag가 1인 스택만 push해 줌.
		else pop(s); //그렇지 않은 것은 그냥 버림.
	}
	printf("<<<maze path>>>\n"); //경로
	for (int i = p.top; i >= 0; --i) { //top번 만큼.
		printf("(%d, %d)\n", peek(&p).x,peek(&p).y);
		pop(&p);
		if(is_empty(&p)) break;
	}
}

element get_pos(StackType* s) {
	return peek(s);
}

element change_flag(element x) {
	element z = x;
	if (z.flag == 0) z.flag = 1;
	else z.flag = 0;
	return z;
}

//x가 행 y가 열
//상: x-1 하: x+1  좌: y-1 우: y+1

int push_loc(StackType* s, int(*maze)[MAX], int x, int y) {
	if (!is_over(x) && maze[x][y] != 7 && maze[x][y] == 1) {
		push(s, get_Cordi(x, y, 0)); //flag를 0으로 push
		return 1;
	}
	else return 0;
}

//우선 갈 수 있는 길이 나오면 flag를 0로 해서 모두 push를 함.
//그리고 가장 맨 위에 있는 것을 pop해서 flag를 1로 바꾸고(가는 길) push 후 현재 위치 변경
//지나왔던 길들은 7로 처리함.(maze에 반영)
//만약에 길이 없는 경우 스택에 있는 flag가 1인 요소를 flag가 0인 분기점이 나올 때까지 pop해 줌.
//그리고 flag가 0이 나오는 순간 pop해서 flag를 1로 바꾸고 다시 push 후 현재 위치 변경

int search(StackType* s, int(*maze)[MAX], element exit) {
	element pos = change_flag(get_pos(s)); //초기 요소를 가져오고 flag를 바꿔줌. 
	write_value(maze, pop(s)); //갔던 길 표시
	push(s, pos); //바뀐 flag의 길 push
	print_maze(maze);
	while (pos.x != exit.x || pos.y != exit.y) { //현 위치가 출구랑 다르면
		int count = 0;
		count += push_loc(s, maze, pos.x - 1, pos.y); //상
		count += push_loc(s, maze, pos.x + 1, pos.y); //하
		count += push_loc(s, maze, pos.x, pos.y - 1); //좌
		count += push_loc(s, maze, pos.x, pos.y + 1); //우
		if (count == 0) { //길이 막혔다면
			while (1) {
				if (is_empty(s)) return 0; //실패 flag을 모두 뺐는데 못찾는다면 실패
				pos = pop(s); //flag가 0이 보일 때까지 1인 스택을 반복해서 pop을 해준다.
				if (pos.flag == 0) { //0이 보이면 
					push(s, pos); //그 요소를 다시 push해주고 break;
					break;
				}
			}
		}
		//길이 하나라도 있다면 일단 쌓여있을 것이고 맨 위에 있는 값을 pop후 flag를 세워서 push
		pos = change_flag(peek(s)); //맨 위 값에 flag 바꿔서 pos위치시킴
		write_value(maze, pop(s)); //그리고 길을 입력한 뒤에 pop를 해줌.
		push(s, pos); //마지막으로 바뀐 플래그를 push해 줌.
		print_maze(maze); //출력
	}

	return 1; //성공
}

void print_cord(element pos) {
	printf("(%d, %d)\n", pos.x, pos.y);
}

void write_value(int(*maze)[MAX], element cord) { //단순히 길만 표시
	maze[cord.x][cord.y] = 7; //간 길이라고 표시.
}

element get_Cordi(int x, int y, int flag) {
	element z = { x,y,flag };
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