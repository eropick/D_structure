#define _CRT_SECURE_NO_WARNINGS
#include "mystack.h"
#define MAX 10

void create_maze(int(*maze)[MAX]); //�̷�
void print_maze(int(*maze)[MAX]); //�̷� ���.
void run(); //�̷�ã�� ����
element get_Cordi(int x, int y, int flag); //��ǥ�� ��� �Լ�.
void write_value(int(*maze)[MAX], element cord); //���� ����ִ� �Լ�.
element get_pos(StackType* s); //���� ��ǥ�� �������� �Լ�
int search(StackType* s, int(*maze)[MAX], element exit);
//���� �� ������ ��ǥ�� ������ �� �ڿ� �����¿츦 �˻��ؼ� �� �� �ִ� ��ǥ�� ���ÿ� ����.
//��: y-1 ��: y+1  ��: x-1 ��: x+1
boolean is_over(int x); //x���� �������� ����� ���� �Ǵ�
//size: 10x10 size // 0�� ������ 1�� �� �� �ִ� �� 2�� ���� ��
void print_cord(element pos); //���� ��ǥ��ġ.
int push_loc(StackType* s, int(*maze)[MAX], int x, int y); //Ǫ���� �Ǻ�
void path(StackType* s); //������ �����ؼ� flag�� 1�� ���ø��� ǥ���ϸ� ��ΰ� ��. 
element change_flag(element x); //flag����

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
	push(&s, get_Cordi(1, 0, 0)); //�ʱ� ��ġ�� ���ÿ� �־���.
	element exit = get_Cordi(7, 9, 0); //�ⱸ ����.
	//�ⱸ�� ���� ���� x��� �൵ ��.
	create_maze(maze); //�̷� ����
	print_maze(maze); //�̷� ���
	if (search(&s, maze, exit)) printf("\n����\n");
	else printf("\n����\n");
	path(&s);
}

boolean is_over(int x) {
	if (x < 0) return true; //0�̸�
	else if (x > 9) return true; //9�ʰ�
	else return false; //0�̻� 9����
}

void path(StackType* s) {
	StackType p;
	init_stack(&p);
	while (!is_empty(s)) { //������ �������� �ݺ�
		if (peek(s).flag == 1)	push(&p, pop(s)); //flag�� 1�� ���ø� push�� ��.
		else pop(s); //�׷��� ���� ���� �׳� ����.
	}
	printf("<<<maze path>>>\n"); //���
	for (int i = p.top; i >= 0; --i) { //top�� ��ŭ.
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

//x�� �� y�� ��
//��: x-1 ��: x+1  ��: y-1 ��: y+1

int push_loc(StackType* s, int(*maze)[MAX], int x, int y) {
	if (!is_over(x) && maze[x][y] != 7 && maze[x][y] == 1) {
		push(s, get_Cordi(x, y, 0)); //flag�� 0���� push
		return 1;
	}
	else return 0;
}

//�켱 �� �� �ִ� ���� ������ flag�� 0�� �ؼ� ��� push�� ��.
//�׸��� ���� �� ���� �ִ� ���� pop�ؼ� flag�� 1�� �ٲٰ�(���� ��) push �� ���� ��ġ ����
//�����Դ� ����� 7�� ó����.(maze�� �ݿ�)
//���࿡ ���� ���� ��� ���ÿ� �ִ� flag�� 1�� ��Ҹ� flag�� 0�� �б����� ���� ������ pop�� ��.
//�׸��� flag�� 0�� ������ ���� pop�ؼ� flag�� 1�� �ٲٰ� �ٽ� push �� ���� ��ġ ����

int search(StackType* s, int(*maze)[MAX], element exit) {
	element pos = change_flag(get_pos(s)); //�ʱ� ��Ҹ� �������� flag�� �ٲ���. 
	write_value(maze, pop(s)); //���� �� ǥ��
	push(s, pos); //�ٲ� flag�� �� push
	print_maze(maze);
	while (pos.x != exit.x || pos.y != exit.y) { //�� ��ġ�� �ⱸ�� �ٸ���
		int count = 0;
		count += push_loc(s, maze, pos.x - 1, pos.y); //��
		count += push_loc(s, maze, pos.x + 1, pos.y); //��
		count += push_loc(s, maze, pos.x, pos.y - 1); //��
		count += push_loc(s, maze, pos.x, pos.y + 1); //��
		if (count == 0) { //���� �����ٸ�
			while (1) {
				if (is_empty(s)) return 0; //���� flag�� ��� ���µ� ��ã�´ٸ� ����
				pos = pop(s); //flag�� 0�� ���� ������ 1�� ������ �ݺ��ؼ� pop�� ���ش�.
				if (pos.flag == 0) { //0�� ���̸� 
					push(s, pos); //�� ��Ҹ� �ٽ� push���ְ� break;
					break;
				}
			}
		}
		//���� �ϳ��� �ִٸ� �ϴ� �׿����� ���̰� �� ���� �ִ� ���� pop�� flag�� ������ push
		pos = change_flag(peek(s)); //�� �� ���� flag �ٲ㼭 pos��ġ��Ŵ
		write_value(maze, pop(s)); //�׸��� ���� �Է��� �ڿ� pop�� ����.
		push(s, pos); //���������� �ٲ� �÷��׸� push�� ��.
		print_maze(maze); //���
	}

	return 1; //����
}

void print_cord(element pos) {
	printf("(%d, %d)\n", pos.x, pos.y);
}

void write_value(int(*maze)[MAX], element cord) { //�ܼ��� �游 ǥ��
	maze[cord.x][cord.y] = 7; //�� ���̶�� ǥ��.
}

element get_Cordi(int x, int y, int flag) {
	element z = { x,y,flag };
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