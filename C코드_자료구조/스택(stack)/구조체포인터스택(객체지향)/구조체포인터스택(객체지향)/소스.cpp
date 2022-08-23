#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100
#define MAX_STRING 100
#define TRUE (1)
#define FALSE (0)

//스택의 정보가 여러개가 있을 경우 구조체를 생성한다.
//예를들어 군인의 정보라고 해보자.
typedef struct _element {
	char name[MAX_STRING];
	char rank[MAX_STRING];
	int m_num;
}element;

typedef int boolean;

typedef struct _StackType {
	int top;
	element stack[MAX_STACK_SIZE]; 
}StackType;

typedef struct _StackType2{
	int top;
	int capacity; //현재 크기
	element* stack;
	/*이 요소를 따로 배열로 지정하지 않고 포인터 형식으로 만들어서
	이렇게 동적할당을 통해 스택이 필요할 때마다 메모리 공간을 할당받는 방법도 고려할 수 있다.
	단, 이렇게 해주면 init을 할 때 top=-1, element동적할당, capacity=1 로 지정해주고 
	push를 할 때 가득찬 경우 realloc()을 통해 재할당하는 방법을 사용한다.  
	*/
}StackType2;

void init(StackType* s);
void push(StackType* s,element items); //요소를 입력한다.
element pop(StackType* s); //요소를 제거 후 반환한다.
element peek(StackType* s); //요소를 반환한다.
void print_stack(StackType* s); //현재 스택에 있는 요소들을 출력한다.
boolean is_full(StackType* s); //현재 스택이 가득차 있는지를 판단한다. 
boolean is_empty(StackType* s); //현재 스택의 요소가 비어있는지를 판단한다.
element write_info(const char* name,const char* rank, int num); //스택의 요소 정보를 작성함.

int main(int argc, char* argv[]) {
	StackType s1;
	StackType* s; //이렇게 동적할당으로 스택을 생성하면 더 직관적으로 접근가능하다.
	s = (StackType*)malloc(sizeof(StackType));
	init(&s1);
	init(s);
	push(&s1, write_info("kimbap","private",10284));
	push(s, write_info("kimbap", "private", 10284));
	push(&s1, write_info("leebalso", "private firstclass", 20284));
	push(s, write_info("leebalso", "private firstclass", 20284));
	print_stack(&s1);
	print_stack(s);
	free(s);
	return 0;
}

element write_info(const char* name,const char* rank, int num) {
	element x;
	strcpy(x.name, name);
	strcpy(x.rank, rank);
	x.m_num = num;
	return x;
}

boolean is_full(StackType* s) {
	if (s->top >= MAX_STACK_SIZE) return TRUE;
	else return FALSE;
}

boolean is_empty(StackType* s) {
	if (s->top == -1) return TRUE;
	else return FALSE;
}

void push(StackType* s, element items) {
	if (is_full(s)) fprintf(stderr, "ERR!! StackOver\n");
	else s->stack[++(s->top)] = items;
}

element pop(StackType* s) {
	if (is_empty(s)) fprintf(stderr, "ERR!! StackEmpty\n");
	else return s->stack[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s)) fprintf(stderr, "ERR!! StackEmpty\n");
	else return s->stack[s->top];
}

void print_stack(StackType* s) {
	if(is_empty(s)) fprintf(stderr, "ERR!! StackEmpty\n");
	else for (int i = 0; i <= s->top; ++i) {
		printf("===================\n");
		printf("name: %s\nrank: %s\nmilitary number: %d\n", s->stack[i].name, s->stack[i].rank, s->stack[i].m_num);
		printf("===================\n");
	}
}

void init(StackType* s) {
	s->top = -1; //빈 스택을 초기화 함.
}