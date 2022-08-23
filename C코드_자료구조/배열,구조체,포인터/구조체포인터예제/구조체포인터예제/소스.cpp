#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Complex_struct {
	double real;
	double imagi;
}Complex;

typedef struct _MyStruct {
	int n;
	char arr[20];
}MyStruct;

Complex complex_add(Complex x, Complex y);
void print_cmpl(Complex x);
void insert(int Array[], int loc, int value,int items);
void Delete(int Array[], int loc, int items);
void print_array(int Array[], int items);

//���Ҽ��� ���� ����ü

int main(int argc,char* argv[])
{
	Complex c1 = {2,3};
	Complex c2 = { 4,5 };
	MyStruct* p = (MyStruct*)malloc(sizeof(MyStruct));
	int* arr;
	int items;
	p->n = 100;
	strcpy(p->arr, "just testing");
	printf("%d//%s\n", p->n, p->arr);
	Complex z = complex_add(c1, c2);
	print_cmpl(z);
	printf("�迭 ũ�⸦ �Է��ϼ���: ");
	scanf_s("%d", &items);
	arr = (int*)malloc(sizeof(int) * items); //�����Ҵ�.
	if (arr == NULL) {
		fprintf(stderr, "����: �ΰ��� ��.");
		return 0;
	}
	for (int i = 0; i < items; ++i) arr[i] = 0;
	print_array(arr,items);
	insert(arr, 2, 4, items);
	print_array(arr, items);
	insert(arr, 0, 5, items);
	print_array(arr, items);
	Delete(arr, 0, items);
	print_array(arr, items);
	free(arr);
	free(p);
	return 0;
}

Complex complex_add(Complex x, Complex y) {
	Complex result;
	result.real = x.real + y.real;
	result.imagi = x.imagi + y.imagi;
	return result;
}

void print_cmpl(Complex x) {
	printf("%.2lf + %.2lfi\n", x.real, x.imagi);
}

void insert(int Array[], int loc, int value, int items) {
	if (loc >= items && loc < 0) {
		printf("����: ��ġ�� ������ ����ϴ�.\n");
		return; //���Ұ������� ��ġ�� ũ�� ����
	}
	for (int i = items-1;i>=loc; --i) {
		if (i == loc){
			Array[i] = value; //�� �Ҵ�.
			break;
		}
		Array[i] = Array[i - 1]; //�� �������� ��� �������� �����ٰ� �Ҵ���.
	}
}

void Delete(int Array[], int loc, int items) {
	if (loc >= items && loc<0) {
		printf("����: ��ġ�� ������ ����ϴ�.\n");
		return; //���Ұ������� ��ġ�� ũ�� ����
	}
	for (int i = loc; i < items; ++i) {
		if (i + 1 == items) {
			Array[i] = 0; //�������̸� 0�� �Ҵ�.
			break;
		}
		Array[i] = Array[i + 1];
	}

}

void print_array(int Array[],int items){
	for (int i = 0; i < items; ++i) {
		printf("%d ",Array[i]);
	}
	printf("\n\n");
}