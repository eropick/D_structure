#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>

//포인터로 구현한 리스트의 연결된 표현

typedef int element; //요소
typedef struct _NodeType {
	element data; //datafield
	struct _NodeType* link; //linkfield
}NodeType;

void error(const char* msg);
NodeType* insert_first(NodeType* head, element value); //insert할 때 동적할당한 메모리를 반환해야 하므로 반환자료형은 포인터
NodeType* insert(NodeType* head, NodeType* pre, element value); //삽입을 하기 위해서는 이전 노드의 주소가 반드시 필요하다.
NodeType* Delete_first(NodeType* head);
NodeType* Delete(NodeType* head, NodeType* pre); //삭제를 할 때도 이전 노드가 필요하다.
void print_list(NodeType* head);
void node_free(NodeType** head); //만들었던 노드들을 모두 해제 해준다.

//head => node1.link -> node2.link -> node3 ...
void error(const char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

//head가 가리키는 노드를 새로 만든 것으로 대체.
NodeType* insert_first(NodeType* head, element value) {
	NodeType* node = (NodeType*)malloc(sizeof NodeType);
	if (node == NULL) error("동적할당 실패\n");
	node->data = value;
	//node의 링크필드가 가리키는 주소는 이전 노드인 head가 가리키는 주소가 들어가야 한다.
	node->link = head;
	//그리고 head는 현 노드를 가리켜야 한다.
	head = node;
	return head;
}

//head라는 포인터 변수에 주소를 받았는데 node로 다시 바꿔썼으므로 반환을 해줘야 한다.

//이는 다음과 같다.
//단순히 변수의 값만 바꾼 것이기 때문에 반환을 해줘야한다.
//만약 call by reference의 형태로 처리하려면
//이중포인터를 사용해 매개변수로 받고 처리해야만 한다.
int ttt(int a, int b) {
	int c = a;
	a = c + 2;
	return a;
}

NodeType* insert(NodeType* head, NodeType* pre, element value) {
	NodeType* node = (NodeType*)malloc(sizeof NodeType);
	if (node == NULL) error("동적할당 실패\n");
	node->data = value;
	//node의 링크필드가 가리키는 주소는 이전 노드가 가리키는 주소가 들어가야 한다.
	node->link = pre->link;
	//그리고 이전노드는 현 노드를 가리켜야 한다.
	pre->link = node;
	return head; //그리고 수정된 head를 반환한다.
}

NodeType* Delete_first(NodeType* head) {
	NodeType* remove; //head가 가리키는 노드를 가져옴.
	if (head == NULL) return NULL;
	remove = head;
	head = head->link; //head는 이전 노드의 다음 링크를 가리키게 만듬.
	free(remove); //이전 노드를 동적할당 해제함.
	return head;
}
NodeType* Delete(NodeType* head, NodeType* pre) {
	NodeType* remove;
	if (head == NULL) return NULL;
	remove = pre->link; //pre이전 노드가 가리키는 다음노드; 즉, 현재 지울 노드를 remove에 담음.
	pre->link = remove->link; //이전 노드가 가리키는 링크를 현재 지울노드가 가리키는 노드로 교체;
	free(remove); //해제;
	return head; //변한 값을 반환
}


void print_list(NodeType* head) {
	//현재 포인터부터 시작 포인터가 NULL이 아닐 경우 반복 실행, 이후 p의 다음 링크로 교체
	for (NodeType* p = head; p != NULL; p = p->link) {
		printf("%d->", p->data);
	}
	printf("NULL\n");
}


void node_free(NodeType** head) {
	while ((*head) != NULL) (*head) = Delete_first((*head));
	//모든 값을 동적 해제시킴.
}