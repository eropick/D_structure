#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>

//�����ͷ� ������ ����Ʈ�� ����� ǥ��

typedef int element; //���
typedef struct _NodeType {
	element data; //datafield
	struct _NodeType* link; //linkfield
}NodeType;

void error(const char* msg);
NodeType* insert_first(NodeType* head, element value); //insert�� �� �����Ҵ��� �޸𸮸� ��ȯ�ؾ� �ϹǷ� ��ȯ�ڷ����� ������
NodeType* insert(NodeType* head, NodeType* pre, element value); //������ �ϱ� ���ؼ��� ���� ����� �ּҰ� �ݵ�� �ʿ��ϴ�.
NodeType* Delete_first(NodeType* head);
NodeType* Delete(NodeType* head, NodeType* pre); //������ �� ���� ���� ��尡 �ʿ��ϴ�.
void print_list(NodeType* head);
void node_free(NodeType** head); //������� ������ ��� ���� ���ش�.

//head => node1.link -> node2.link -> node3 ...
void error(const char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

//head�� ����Ű�� ��带 ���� ���� ������ ��ü.
NodeType* insert_first(NodeType* head, element value) {
	NodeType* node = (NodeType*)malloc(sizeof NodeType);
	if (node == NULL) error("�����Ҵ� ����\n");
	node->data = value;
	//node�� ��ũ�ʵ尡 ����Ű�� �ּҴ� ���� ����� head�� ����Ű�� �ּҰ� ���� �Ѵ�.
	node->link = head;
	//�׸��� head�� �� ��带 �����Ѿ� �Ѵ�.
	head = node;
	return head;
}

//head��� ������ ������ �ּҸ� �޾Ҵµ� node�� �ٽ� �ٲ�����Ƿ� ��ȯ�� ����� �Ѵ�.

//�̴� ������ ����.
//�ܼ��� ������ ���� �ٲ� ���̱� ������ ��ȯ�� ������Ѵ�.
//���� call by reference�� ���·� ó���Ϸ���
//���������͸� ����� �Ű������� �ް� ó���ؾ߸� �Ѵ�.
int ttt(int a, int b) {
	int c = a;
	a = c + 2;
	return a;
}

NodeType* insert(NodeType* head, NodeType* pre, element value) {
	NodeType* node = (NodeType*)malloc(sizeof NodeType);
	if (node == NULL) error("�����Ҵ� ����\n");
	node->data = value;
	//node�� ��ũ�ʵ尡 ����Ű�� �ּҴ� ���� ��尡 ����Ű�� �ּҰ� ���� �Ѵ�.
	node->link = pre->link;
	//�׸��� �������� �� ��带 �����Ѿ� �Ѵ�.
	pre->link = node;
	return head; //�׸��� ������ head�� ��ȯ�Ѵ�.
}

NodeType* Delete_first(NodeType* head) {
	NodeType* remove; //head�� ����Ű�� ��带 ������.
	if (head == NULL) return NULL;
	remove = head;
	head = head->link; //head�� ���� ����� ���� ��ũ�� ����Ű�� ����.
	free(remove); //���� ��带 �����Ҵ� ������.
	return head;
}
NodeType* Delete(NodeType* head, NodeType* pre) {
	NodeType* remove;
	if (head == NULL) return NULL;
	remove = pre->link; //pre���� ��尡 ����Ű�� �������; ��, ���� ���� ��带 remove�� ����.
	pre->link = remove->link; //���� ��尡 ����Ű�� ��ũ�� ���� �����尡 ����Ű�� ���� ��ü;
	free(remove); //����;
	return head; //���� ���� ��ȯ
}


void print_list(NodeType* head) {
	//���� �����ͺ��� ���� �����Ͱ� NULL�� �ƴ� ��� �ݺ� ����, ���� p�� ���� ��ũ�� ��ü
	for (NodeType* p = head; p != NULL; p = p->link) {
		printf("%d->", p->data);
	}
	printf("NULL\n");
}


void node_free(NodeType** head) {
	while ((*head) != NULL) (*head) = Delete_first((*head));
	//��� ���� ���� ������Ŵ.
}