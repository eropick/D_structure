#define _CRT_SECURE_NO_WARNINGS
#include "mystack.h"
#define MAX 10

void create_maze(int (*maze)[MAX]); //�̷�
void print_maze(int(*maze)[MAX]); //�̷� ���.
void run(); //�̷�ã�� ����
element get_Cordi(int x,int y); //��ǥ�� ��� �Լ�.
void write_value(int(*maze)[MAX], element cord); //���� ����ִ� �Լ�.
element get_pos(StackType* s); //���� ��ǥ�� �������� �Լ�
int search(StackType *s, int(*maze)[MAX],element exit); 
//���� �� ������ ��ǥ�� ������ �� �ڿ� �����¿츦 �˻��ؼ� �� �� �ִ� ��ǥ�� ���ÿ� ����.
//��: y-1 ��: y+1  ��: x-1 ��: x+1
boolean is_over(int x); //x���� �������� ����� ���� �Ǵ�
//size: 10x10 size // 0�� ������ 1�� �� �� �ִ� �� 2�� ���� ��
void print_cord(element pos); //���� ��ǥ��ġ.
void push_loc(StackType* s, int(*maze)[MAX],int x,int y); //Ǫ���� �Ǻ�

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
	int maze[MAX][MAX]; //10,10¥�� �迭���� ����
	StackType s; //��ǥ�� ������ ���� ����
	init_stack(&s); //���� �ʱ�ȭ
	push(&s, get_Cordi(1, 0)); //�ʱ� ��ġ�� ���ÿ� �־���.
	element exit = get_Cordi(7, 9); //�ⱸ ����.
	//�ⱸ�� ���� ���� x��� �൵ ��.
	create_maze(maze); //�̷� ����
	print_maze(maze); //�̷� ���
	if (search(&s, maze, exit)) printf("\n����\n");
	else printf("\n����\n");
}

boolean is_over(int x) {
	if (x < 0) return true; //0�̸�
	else if (x > 9) return true; //9�ʰ�
	else return false; //0�̻� 9����
}

element get_pos(StackType* s) {
	return peek(s);
}

//��: y-1 ��: y+1  ��: x-1 ��: x+1

void push_loc(StackType* s, int(*maze)[MAX],int x, int y) {
	if (!is_over(x) && maze[x][y] != 2 && maze[x][y] == 1) push(s, get_Cordi(x, y));
}

int search(StackType* s, int(*maze)[MAX],element exit) {
	element pos = get_pos(s); //���� ��ǥ�� ������.
	write_value(maze, pop(s)); //�ʱ� ��ġ�� ������ ��.
	print_maze(maze);
	while (pos.x!=exit.x || pos.y!=exit.y) { //�� ��ġ�� �ⱸ�� �ٸ���
		push_loc(s,maze,pos.x,pos.y-1); //��
		push_loc(s, maze, pos.x, pos.y+1); //��
		push_loc(s, maze, pos.x-1, pos.y); //��
		push_loc(s, maze, pos.x + 1, pos.y); //��
		//������ ����ִٸ�
		if (is_empty(s)) return 0; //����
		else { //���� �� �ϳ��� ������ ���� ��ġ�� �����. 
			pos = peek(s); //���� ��ġ ����.
			write_value(maze, pop(s)); //�׸��� ���ڿ�
			print_maze(maze); //���
		}
	}
	return 1; //����
}

void print_cord(element pos) {
	printf("(%d, %d)\n", pos.x, pos.y);
}

void write_value(int(*maze)[MAX], element cord) {
	maze[cord.x][cord.y] = 2; //�� ���̶�� ǥ��.
}

element get_Cordi(int x,int y) {
	element z = { x,y };
	return z;
}

void print_maze(int(*maze)[MAX]) {
	int i, j;
	Sleep(1000); //1�� ���� ��
	system("cls"); //������ �ִ� �̷θ� ����.
	for (i = 0; i < MAX; ++i) {
		for (j = 0; j < MAX; ++j) printf("%d ", maze[i][j]);
		printf("\n");
	}
}

void create_maze(int(*maze)[MAX]) {
	int i, j;
	for (i = 0; i < MAX; ++i) for (j = 0; j < MAX; ++j) maze[i][j] = 0; //�ʱ�ȭ
	for (j = 0; j < 6; ++j) maze[1][j] = 1; //0~5���� 1
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

