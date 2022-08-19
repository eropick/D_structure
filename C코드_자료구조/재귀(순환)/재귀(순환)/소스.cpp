#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int factorial(int n);
double slow_power1(double n,int m); //순환 거듭제곱
double slow_power2(double n, int m); //순환 거듭제곱
double fast_power(double n, int m); //반복 거듭제곱
int fibonacci(int n); //순환 피보나치
void hanoi_tower(int n,char from,char tmp,char to); //순환 하노이
int bino_coef(int n, int k);

int main() {
	int n;
	double x;
	//재귀함수 대명사 팩토리얼
	printf("숫자를 입력하세요!: ");
	scanf("%d", &n);
	//printf("%d!은 %d입니다\n", n, factorial(n)); 팩토리얼
	//printf("%.1lf의 10승은 %.1lf", x,slow_power1(x, 10)); 순환 거듭제곱
	//printf("%.1lf의 10승은 %.1lf", x, fast_power(x, 10)); 반복 거듭제곱
	//printf("%d의 피보나치 수열: %d", n, fibonacci(n)); 순환 피보나치 수열
	//hanoi_tower(n, 'A', 'B', 'C'); 순환 하노이탑
	//printf("이항계수: %d ",bino_coef(5, 2)); 순환 이항계수
	return 0;
}

int bino_coef(int n, int k) {
	if (k == 0 || k == n) return 1;
	else if (k > 0 && k < n) return bino_coef(n - 1, k - 1) + bino_coef(n - 1, k);
}

int factorial(int n) {
	printf("factorial(%d)\n", n); //순환이 어떻게 이루어지는지 보여준다.
	if (n >= 1) return n * factorial(n - 1);
	else return 1;
}

//순환으로 거듭제곱을 계산한다.
double slow_power1(double n,int m) {
	if (m == 0) return 1;
	else if(m%2==0) //짝수
		return slow_power1(n*n, m/2);
	else if(m%2==1) //홀수
		return n*slow_power1(n*n, (m-1)/ 2);
	//거듭제곱 횟수가 짝수일 때는 그냥 m의 크기만 절반으로 해주고
	//n만 '제곱'해서 호출했다가 m의 값이 홀수 일 때 제곱한 값을 곱해주는 방식으로 이어짐.
}
double slow_power2(double n, int m) {//순환 거듭제곱
	if (m == 0) return 1;
	else return n*slow_power2(n, --m);
} 

double fast_power(double n, int m) { //반복 거듭제곱
	double mul = 1;
	for (int i = 0; i < m; ++i) {
		mul = mul * n;
	}
	return mul;
}

int fibonacci(int n) { //피보나치 수열을 순환으로 구해보자
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return fibonacci(n - 2) + fibonacci(n - 1);
}

void hanoi_tower(int n, char from, char tmp, char to) {
	//가장 기본적인 형태로 원판이 1개라면 from에서 to로만 옮기면 된다.
	//또한 작은 원이 항상 맨 위에 있으므로 원판1이 항상 이동이 된다.
	if (n == 1) printf("원판1이 %c에서 %c로 이동했습니다.\n", from, to);
	else {
		//(n>1)인 경우에는 마지막 원판을 제외한 n-1을 일단 from에서 tmp로 옮겨야 한다.
		hanoi_tower(n - 1, from, to, tmp);
		//마지막에 남은 원판n을 to로 옮긴다.
		printf("원판%d를 %c에서 %c로 이동했습니다.\n", n, from, to);
		//tmp에 있는 n-1의 원판을 tmp에서 to로 옮긴다.
		hanoi_tower(n - 1, tmp, from, to);
		/*
		그렇다면 이 n-1의 원판은 어떻게 옮기는가? -> 이걸 순환으로 해결하는 것.
		n개의 원판을 옮기는 것안에 n-1개의 원판을 옮기는 것 
		n-1개의 원판을 옮기는 것안에 n-2개의 원판을 옮기는 것...
		1개의 원판을 옮기는 것으로 점점 줄어드는 형태이다.
		*/
	}
}
//ex) fibonacci(6)에 해당하는 값을 구한다고하면
/* fibonacci(4) + fibonacci(5) 로 나눠지고
fibonacci(4) -> fibonacci(2)+fibonacci(3) 으로 나뉘며
fibonacci(5) -> fibonacci(3) + fibonacci(4)로 나뉘어진다.
이렇게 중복된 호출이 여러번 생긴다.
이를 시간 복잡도로 보면 한 번 호출마다 2번의 호출이 추가적으로 생긴다.
O(2^n)이 된다.
*/