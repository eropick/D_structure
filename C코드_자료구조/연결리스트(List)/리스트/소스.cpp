#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>

#define MAX_LIST_SIZE 100

//�迭�� ������ ����Ʈ�� ������ ǥ��

typedef int element; //���
typedef struct _ArrayListType {
	element array[MAX_LIST_SIZE]; //��Ұ� �� ����Ʈ
	int size; //����� ����
}ArrayListType;

void error(const char* msg); //����ó���Լ�
void clear(ArrayListType* L);
boolean is_empty(ArrayListType* L);
boolean is_full(ArrayListType* L);
boolean is_badpos(ArrayListType* L,int pos); //��ġ�� ������ �Ǵ�.
void insert(ArrayListType* L , int pos, element item);
void insert_last(ArrayListType* L, element item);
void insert_first(ArrayListType* L, element item);
element Delete(ArrayListType* L, int pos); //������ ��ȯ
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
	return L->size == 0; //ũ�Ⱑ 0�̸� 1 �ƴϸ� 0
}
boolean is_full(ArrayListType* L) {
	return L->size == MAX_LIST_SIZE; //ũ�Ⱑ maxsize�� ���ٸ� 1 �ƴϸ� 0
}
boolean is_badpos(ArrayListType* L,int pos) {
	return (pos<0) && (pos >= L->size); //������ ����� 
}
void insert(ArrayListType* L, int pos, element item) {
	if (is_full(L)) error("����Ʈ ���� �÷ο�");
	else if (is_badpos(L,pos)) error("��ġ ����");
	L->size++; //ũ�⸦ 1���� ���ѵ�.
	//���⼭ ���ʹ� ��Ҹ� �ű�.
	for (int i = L->size - 1; i > pos; --i) {
		L->array[i] = L->array[i - 1]; //���� ���� �Ҵ�.
	}
	L->array[pos] = item; //�� pos�� ��� �Ҵ�.
}
void insert_last(ArrayListType* L, element item) {
	if (is_full(L)) error("����Ʈ ���� �÷ο�");
	L->array[++L->size] = item; //size���� ��Ų ���� ����.
}
void insert_first(ArrayListType* L, element item) {
	insert(L, 0, item); //0��° ó���� ����.
}
element Delete(ArrayListType* L, int pos) {
	element temp;
	if (is_empty(L)) error("����Ʈ�� �������\n");
	else if (is_badpos(L, pos)) error("��ġ ����");
	temp = L->array[pos]; //���� ��ġ�� �ִ� �� ��ȯ
	L->size--; //size�� 1����.
	for (int i = pos; i < L->size; ++i) {
		L->array[i] = L->array[i + 1]; //�� �� ���� �־���.
	}
	return temp;
}
element get_entry(ArrayListType* L, int pos) {
	element temp;
	if (is_empty(L)) error("����Ʈ�� �������\n");
	else if (is_badpos(L, pos)) error("��ġ ����");
	temp = L->array[pos]; //���� ��ġ�� �ִ� �� ��ȯ
	return temp;
}
int get_length(ArrayListType* L) {
	return L->size;
}
void print_list(ArrayListType* L) {
	for (int i = 0; i < L->size; ++i)
		printf("List:%d��°, %d\n", i, L->array[i]);
}