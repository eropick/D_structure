#include<stdio.h>
#define MAX_DEGREE 101
#define LARGE_DEGREE(a,b) ((a)>(b))?(a):(b)

//단순히 배열을 이용한 다항식 연산처리인데
/*
배열을 파라미터로 넘길 때는 따로 주소, 포인터로 처리해주던것에 비해 Call by reference
구조체를 파라미터로 넘길 때는 구조체 안에 배열 연산과 값이 그대로 넘어가기 때문에
Call by value가 가능하다.
*/

typedef struct _polynomial {
	int degree; //다항식 차수
	int coef[MAX_DEGREE]; //다항식 계수
}polynomial;

void print_poly(polynomial p);
polynomial add(polynomial x, polynomial y);
void add2(int x[10], int y[10]);

//배열과 구조체를 응용해서 다항식의 연산을 처리해보자
//3x^5 + 2x^3 + 1 과 2x^4 + 10x 의 덧셈이다. 
int main(int argc, char* argv[]) {
	polynomial a = { 5,{3,0,2,0,0,1} };
	polynomial b = { 4,{2,0,0,10,0} };
	polynomial c;
	print_poly(a);
	print_poly(b);
	c=add(a, b);
	printf("\n-------------------------\n");
	print_poly(c);
	return 0;
}


void print_poly(polynomial p) {
	for (int i = 0; i <= p.degree; ++i) {
		if (i == p.degree && p.coef[i]!=0) { //상수이고 0이 아닌 경우 
			printf("%d\n", p.coef[i]); //상수가 0이 아닌 경우
			break; //반복끝
		}
		else if(p.coef[i]!=0) printf("%dx^%d", p.coef[i], p.degree - i); //0이 아닌 값 
		if (p.coef[i + 1] != 0) printf("+"); //다음값이 0이 아닌 경우만 +를 해 줌.
	}
}

polynomial add(polynomial x, polynomial y) {
	polynomial C;
	int xpos = 0, ypos = 0, cpos = 0;
	int xdegree = x.degree;
	int ydegree = y.degree;
	C.degree = LARGE_DEGREE(xdegree, ydegree); //최고차수를 할당
	while (xpos <= x.degree && ypos <= y.degree){ //위치가 차수가 될 때까지 반복
		if (xdegree > ydegree) { //x차수가 더 큰 경우
			C.coef[cpos++] = x.coef[xpos++]; //x계수를 c계수에 넣고 포지션 증가
			xdegree--; //x차수감소
		}
		else if (xdegree == ydegree) { //두 차수가 같은 경우
			C.coef[cpos++] = x.coef[xpos++] + y.coef[ypos++]; //두 값을 더함
			xdegree--; //x,y차수감소
			ydegree--;
		}
		else { //y차수가 더 큰 경우
			C.coef[cpos++] = y.coef[ypos++]; //y계수를 c계수에 넣고 포지션 증가
			ydegree--; //y차수감소
		}
	}
	return C;
}