#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> //malloc, free�Լ�
#include<string.h>
#include<math.h>

//�����ϰ� �������͸� Ȯ���ϴ� �Լ��� �ۼ��غ���.

//�������� ����ü �����غ���
typedef struct _Student {
	char name[10];
	int age;
	double gpa;
}Student;

int inspection(Student* p);
void print_ar();

int main(int argc, char* argv[]) {
	int* g=NULL; //�������� �Ҵ�
	int size = 10;
	int* p;
	Student* sp;
	sp = (Student*)malloc(sizeof(Student)); //���� ����ü ����
	inspection(sp); //�����˻�
	p = (int*)malloc(sizeof(int)*size); //int4byteũ�� 10���� ���� �迭�� �����Ҵ�
	for (int i = 0; i < size; ++i) {
		p[i] = i;
		printf("%d\n", p[i]);
	}
	sp->age = 22;
	strcpy(sp->name, "kims");
	sp->gpa = 4.5;
	print_ar();
	
	free(p); //�Ҵ�����
	free(sp); //�Ҵ�����
	return 0;
}


int inspection(Student* p) {
	if (p == NULL) {
		fprintf(stderr, "����: �޸� ������ ������ �Ҵ����� ���߽��ϴ�.\n");
		return 0;
	}
	return 1;
}

void print_ar() {
	int size = 10;
	int* two;
	two = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i) {
		two[i] = (int)pow(2.0, i);
		printf("%d\n",two[i]);
	}
	free(two);
}