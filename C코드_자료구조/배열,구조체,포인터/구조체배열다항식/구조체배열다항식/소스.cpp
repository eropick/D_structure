#include<stdio.h>
#define SIZE 101

typedef struct _polynomial {
	int degree;
	double coef;
}polynomial;


void print_poly(polynomial* x);
void poly_sum(polynomial* x, polynomial* y);
polynomial result[SIZE] = { {0,0} }; //초기화

//a,b식을 옮겨서 같은 차수먼저 더한 후 나중에 다른 차수들을 합쳐주는 방식을 취한다.

int main(int argc, char* argv[]) {
	polynomial a[SIZE] = { {5,1},{3,4},{1,5} }; 
	polynomial b[SIZE] = { {0,1},{2,6},{4,9},{3,4} };
	print_poly(a);
	print_poly(b);
	poly_sum(a, b);
	printf("-------------------------------\n");
	print_poly(result);
	return 0;
}

void poly_sum(polynomial* x, polynomial* y) {
	int count,i,j;
	int resultc = -1;
	polynomial tmp[SIZE]{ {0,0} }; //y의 식을 옮기기 위함.
	//먼저 result에 한 쪽 식의 값을 할당함
	for (i = 0; i < SIZE; ++i) {
		if(x[i].coef == 0 && x[i].degree == 0) break; //마지막을 제외하고
		else {
			result[i].coef = x[i].coef; //계수할당
			result[i].degree = x[i].degree; //차수할당
		}
		resultc++; //result의 항개수를 구함
	}
	for (i = 0; i < SIZE; ++i) {
		if (y[i].coef == 0 && y[i].degree == 0) break; //마지막을 제외하고
		else {
			tmp[i].coef = y[i].coef; //계수할당
			tmp[i].degree = y[i].degree; //차수할당
		}
	}

	for (i = 0; i < SIZE; ++i) { //result의 값을 추출함 
		if (result[i].coef == 0 && result[i].degree==0) break;
		for (j = 0; j < SIZE; ++j) { //y의 값과 비교해서 더함
			if(tmp[j].coef == 0 && tmp[j].degree == 0) break; //y의 끝에는 탈출
			else if (result[i].degree == tmp[j].degree) { //두 개 차수가 같은 경우
				result[i].coef += tmp[j].coef;
				tmp[j].coef = 0; //차수가 같은 경우 result로 합쳐버리고 
				tmp[j].degree = -1; //계수를 0 차수를 -1로 만듬.
			}
		}
	}
	for (i = 0; i < SIZE; ++i) {
		if (tmp[i].coef == 0 && tmp[i].degree == 0) break;
		else if (tmp[i].coef == 0 && tmp[i].degree == -1) continue; //동일 차수였으면 다음으로
		else { //다른 차수는 모두 추가해준다.
			result[++resultc].coef = tmp[i].coef;
			result[resultc].degree = tmp[i].degree;
		}
	}
}

void print_poly(polynomial* x) {
	//먼저 탐색을 통해 정렬해 줌.
	int count,i,j;
	polynomial t[SIZE]; //정렬을 위한 배열;
	for (i = 0; i < SIZE; ++i) {  //첫 번째 항 추출
		count = 0;
		if (x[i].coef == 0) {
			--i;
			break; //마지막이 되면 빠져나옴
		}
		for (j = 0; j < SIZE; ++j) { //끝까지 비교
			if (x[j].coef == 0) break; //마지막까지 탐색하면 빠져나옴.
			else if (x[i].degree > x[j].degree) count++; //추출한 값이 비교대상보다 크면 인덱스증가.
		}
		t[count].coef = x[i].coef;
		t[count].degree = x[i].degree;
	}
	//마지막 i인덱스를 구했으므로
	for (j = i; j >= 0; --j) {
		if (t[j].degree == 0) printf("%.1lf", t[j].coef); //상수라면 계수만 출력
		else if (j == 0) printf("%.1lfx^%d", t[j].coef, t[j].degree); //마지막 상수가 아닌 항이라면
		else printf("%.1lfx^%d + ", t[j].coef, t[j].degree); //상수나 마지막 값이 아니라면 계수x^차수 
	}
	printf("\n");
}