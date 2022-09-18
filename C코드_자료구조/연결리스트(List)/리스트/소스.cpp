#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>

#define MAX_LIST_SIZE 100

//배열로 구현한 리스트의 순차적 표현

typedef int element; //요소
typedef struct _ArrayListType {
	element array[MAX_LIST_SIZE]; //요소가 들어갈 리스트
	int size; //요소의 개수
}ArrayListType;

void error(const char* msg); //오류처리함수
void clear(ArrayListType* L);
boolean is_empty(ArrayListType* L);
boolean is_full(ArrayListType* L);
boolean is_badpos(ArrayListType* L,int pos); //위치가 나쁜지 판단.
void insert(ArrayListType* L , int pos, element item);
void insert_last(ArrayListType* L, element item);
void insert_first(ArrayListType* L, element item);
element Delete(ArrayListType* L, int pos); //삭제후 반환
element get_entry(ArrayListType* L, int pos);
int get_length(ArrayListType* L);
void print_list(ArrayListType* L);


int main() {
	ArrayListType list;
	clear(&list);
	insert(&list,0,100);
	insert(&list,0,200);
	insert(&list,0,300);
	print_list(&list);
	printf("%d\n", Delete(&list,1));
	print_list(&list);
	return 0;
}

void error(const char* msg) {
	fprintf(stderr,"%s\n", msg);
	exit(1);
}

void clear(ArrayListType* L) {
	L->size = 0;
}
boolean is_empty(ArrayListType* L) {
	return L->size == 0; //크기가 0이면 1 아니면 0
}
boolean is_full(ArrayListType* L) {
	return L->size == MAX_LIST_SIZE; //크기가 maxsize와 같다면 1 아니면 0
}
boolean is_badpos(ArrayListType* L,int pos) {
	return (pos<0) && (pos >= L->size); //범위를 벗어나면 
}
void insert(ArrayListType* L, int pos, element item) {
	if (is_full(L)) error("리스트 오버 플로우");
	else if (is_badpos(L,pos)) error("위치 오류");
	L->size++; //크기를 1증가 시켜둠.
	//여기서 부터는 요소를 옮김.
	for (int i = L->size - 1; i > pos; --i) {
		L->array[i] = L->array[i - 1]; //이전 값을 할당.
	}
	L->array[pos] = item; //그 pos에 요소 할당.
}
void insert_last(ArrayListType* L, element item) {
	if (is_full(L)) error("리스트 오버 플로우");
	L->array[++L->size] = item; //size증가 시킨 곳에 담음.
}
void insert_first(ArrayListType* L, element item) {
	insert(L, 0, item); //0번째 처음에 넣음.
}
element Delete(ArrayListType* L, int pos) {
	element temp;
	if (is_empty(L)) error("리스트가 비어있음\n");
	else if (is_badpos(L, pos)) error("위치 오류");
	temp = L->array[pos]; //현재 위치에 있는 값 반환
	L->size--; //size를 1줄임.
	for (int i = pos; i < L->size; ++i) {
		L->array[i] = L->array[i + 1]; //이 후 값을 넣어줌.
	}
	return temp;
}
element get_entry(ArrayListType* L, int pos) {
	element temp;
	if (is_empty(L)) error("리스트가 비어있음\n");
	else if (is_badpos(L, pos)) error("위치 오류");
	temp = L->array[pos]; //현재 위치에 있는 값 반환
	return temp;
}
int get_length(ArrayListType* L) {
	return L->size;
}
void print_list(ArrayListType* L) {
	for (int i = 0; i < L->size; ++i)
		printf("List:%d번째, %d\n", i, L->array[i]);
}