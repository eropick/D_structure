#include "myDeque.h"

boolean palindrome(const element* str); //입력받은 문자열이 회문인지 정함

int main() {
	element str[100]; //문자열을 입력할 변수
	printf("문자열을 입력하시오: ");
	scanf("%[^\n]s", str);
	if (palindrome(str)) printf("'%s'는 회문입니다.\n",str);
	else printf("'%s'는 회문이 아닙니다.\n", str);
	return 0;
}

boolean palindrome(const element* str) {
	element ch1, ch2;
	boolean check = true;
	int len = strlen(str);
	DequeType dq;
	init_Deque(&dq);
	for (int i = 0; i < len; ++i) {
		if(isalpha(str[i])==1) add_front(&dq, str[i]); //소문자라면 그대로 문자열을 추가함
		else if(isalpha(str[i]) == 2) add_front(&dq, str[i]-32); //대문자라면 소문자로 바꿔서 넣어줌.
	}
	while (1) {
		//회문이 아닌 경우 
		ch1 = ch2 = '!';  //초기화
		if (!is_empty(&dq)) ch1 = delete_front(&dq); //비어있지 않다면 앞에서 하나뺌.
		if (!is_empty(&dq)) ch2 = delete_rear(&dq); //비어있지 않다면 뒤에서 하나뺌.
		if (ch1 != ch2 && ch1 != '!' && ch2 != '!') {
			//ch1과 ch2값이 다르고 ch1과 ch2가 초기화 값이 아닌 경우
			check = false; //회문이 아님을 표시
			break; // 빠져나옴.
		}
		if (is_empty(&dq)) break; //비어있다면 빠져나옴.
	}
	return check;
}