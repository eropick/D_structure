#include<stdio.h>

int sum(int n);
int recursive1(int n);
int recursive2(int n);
void recursive3(int n);
void asterisk(int i);
void unknown();
int custom_sum(int n);
double custom_sum2(int i);
int fibo(int n);
int ackermann(int m, int n); //순환아커만함수
int Wackermann(int m,int n); //반복아커만함수

int main(int argc, char* argv[]) {
	printf("반환값은: %d\n", sum(5));
	//5~0까지 카운트를 세고 반환값은 5+4+3+2+1+1이다.
	printf("반환값은: %d\n", recursive1(5));
	/*5~0까지 카운트를 세고 반환값은 n이 0으로 줄어들 때를 기점으로
	=2*(2*(2*(2*(2*2+1)+1)+1)+1)+1 이러한 형태를 띈다.
	=2*(2*(2*(2*5+1)+1)+1)+1
	=2*(2*(2*11+1)+1)+1
	=2*(2*23+1)+1
	=2*47+1
	=95
	*/
	printf("반환값은: %d\n", recursive2(10));
	/*10,7,4,1,-2 순서로 -3을 한 값이 출력된다. 반환값은 n=-2일 때 기점으로
	(-1+1)+1+1+1로 반환값에 4번 +1이 된다.
	=3
	*/
	recursive3(5);
	/* n이 1이 아니면 n - 1을 계속해서 함수를 호출함.
	여기에서 n이 1이 되는 순간 출력을 하고 함수종료
	이전 함수로 주소 복귀 그리고 2출력...5까지 출력 따라서 1~5까지 순차출력 */
	asterisk(5);
	/* i가 1보다 크면 i값을 절반으로 때려서 다시 함수를 두 번 호출함. 
	5라면 5/2 = asterisk(2)를 두 번 호출.
	asterisk(2)두 번은 2/2 = asterisk(1)을 각각 두 번 호출
	asterisk(1)은 if를 만족하지 않으므로 *를 한 번씩 출력 *4번
	출력 후 종료 asterisk(2)가 *출력 후 종료 두 번째 asterisk(2)가 *출력 후 종료
	마지막 asterisk(5)가 * 출력 후 종료로 총 일곱번의 *가 출력됨.
	따라서 *******가 나온다.
	*/
	printf("\n");
	unknown();
	/* 다음의 함수는 입력한 버퍼스트림에서 문자를 하나받아서 그게 개행이 아니면
	다시 자기자신을 호출하는 함수인데 문자버퍼스트림에서 언젠가는 개행을 만나면
	순환호출은 이루어지지 않고 개행문자를 먼저 출력한 후 차례대로 함수 호출이 종료되면서
	문자를 입력한 반대 순서로 하나씩 출력되는 작업을 이룬다.
	따라서 한 번 개행한 후 문자가 거꾸로 출력된다.
	*/
	printf("\n1~5까지의 합: %d\n",custom_sum(5));
	//다음은 1+2+...+n까지의 합을 구하는 순환함수다.
	printf("1~1/5까지의 합: %.2lf\n", custom_sum2(5));
	//다음은 1+1/2+...+1/n까지의 합을 구하는 순환함수다.
	fibo(3);
	//다음은 피보나치수열의 함수 순환순서를 이해하기 위한 함수다.
	printf("아커만함수: %d\n",ackermann(0, 0));
	//다음은 입력의 값이 적어도 매우 빠르게 증가하는 아커만함수다.
	printf("아커만함수: %d\n",Wackermann(0, 0));
}

int Wackermann(int m, int n) { //반복아커만함수
	int stackm[10000]={0,}; //m의 값이 할당될 배열스택이다. 충분히 크게 만들었다.
	int head = -1; //스택의 head이다. 기본값은 -1부터 시작해서 추가될때마다 +1
	while (n >= 0 && m >= 0)
	{
		if (m == 0 && n > 0) {
			if (head != -1) m = stackm[head--]; //스택이 있다면 가져오고 스택을 하나지움
			else {
				n++;
				break;
			} // m이 0인데 스택이 없으면 n값 증가 후 종료
			n++; //n의값 1증가
		}
		else if (m > 0 && n == 0)
		{
			--m; //m을 1개 빼고
			n = 1; //n의 값을 1로 만듬
		}
		else if (n > 0 && m > 0) {
			stackm[++head] = m - 1; //head에 m-1축적
			--n; //n에서 1뺌
		}
		else break;
	}
	return n;
}

int ackermann(int m, int n) { //순환아커만함수
	if (m == 0 && n > 0) return n + 1;
	else if (m > 0 && n == 0) return ackermann(m - 1, 1);
	else if (n > 0 && m > 0) return ackermann(m - 1, ackermann(m, n - 1));
	else return 0;
}

/*
A(2,2)
(1,(2,1))
(1,(1,(2,0)))
(1,(1,(1,1)))
(1,(1,(0,(1,0))))
(1,(1,(0,(0,1))))
(1,(1,(0,2)))
(1,(1,3))
(1,(0,(1,2)))
(1,(0,(0,(1,1))))
(1,(0,(0,(0,(1,0)))))
(1,(0,(0,(0,(0,1)))))
(1,5)
(0,(0,(0,(0,(1,1))))))
(0,(0,(0,(0,(0,(1,0)))))))
(0,(0,(0,(0,(0,(0,1)))))))
=7
*/

int fibo(int n) {
	printf("fibo(%d) is called\n", n);
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return fibo(n - 1) + fibo(n - 2);
	//fibo(n-1) 먼저 실행 후 다음 복귀후 n-2가 실행되는 형태다.
	//만약 바꾼다면 호출 순서가 달라진다.
}

int custom_sum(int n) {
	if (n == 1) return 1;
	else return n + custom_sum(n - 1);
}

double custom_sum2(int i) {
	if (i == 1) return 1;
	else return 1.0 / i + custom_sum2(i - 1);
}

int sum(int n) {
	printf("%d\n", n);
	if (n < 1) return 1;
	else return(n+sum(n-1));
}

int recursive1(int n) {
	printf("%d\n", n);
	if (n < 1) return 2;
	else return (2 * recursive1(n - 1) + 1);
}

int recursive2(int n) {
	printf("%d\n", n);
	if (n < 1) return -1;
	else return ( recursive2(n - 3)+1);
}

void recursive3(int n) {
	if (n != 1) recursive3(n-1);
	printf("%d\n", n);
}

void asterisk(int i) {
	if (i > 1) {
		asterisk(i / 2);
		asterisk(i / 2);
	}
	printf("*");
}

void unknown() {
	int ch;
	if ((ch = getchar()) != '\n') unknown();
	putchar(ch);
}