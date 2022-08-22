#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> //malloc, free함수
#include<string.h>
#include<math.h>

//간단하게 널포인터를 확인하는 함수를 작성해보자.

//동적으로 구조체 선언해보기
typedef struct _Student {
	char name[10];
	int age;
	double gpa;
}Student;

int inspection(Student* p);
void print_ar();

int main(int argc, char* argv[]) {
	int* g=NULL; //널포인터 할당
	int size = 10;
	int* p;
	Student* sp;
	sp = (Student*)malloc(sizeof(Student)); //동적 구조체 선언
	inspection(sp); //오류검사
	p = (int*)malloc(sizeof(int)*size); //int4byte크기 10개를 갖는 배열의 동적할당
	for (int i = 0; i < size; ++i) {
		p[i] = i;
		printf("%d\n", p[i]);
	}
	sp->age = 22;
	strcpy(sp->name, "kims");
	sp->gpa = 4.5;
	print_ar();
	
	free(p); //할당해제
	free(sp); //할당해제
	return 0;
}


int inspection(Student* p) {
	if (p == NULL) {
		fprintf(stderr, "오류: 메모리 공간이 부족해 할당하지 못했습니다.\n");
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