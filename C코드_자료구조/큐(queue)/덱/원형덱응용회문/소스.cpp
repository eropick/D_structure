#include "myDeque.h"

boolean palindrome(const element* str); //�Է¹��� ���ڿ��� ȸ������ ����

int main() {
	element str[100]; //���ڿ��� �Է��� ����
	printf("���ڿ��� �Է��Ͻÿ�: ");
	scanf("%[^\n]s", str);
	if (palindrome(str)) printf("'%s'�� ȸ���Դϴ�.\n",str);
	else printf("'%s'�� ȸ���� �ƴմϴ�.\n", str);
	return 0;
}

boolean palindrome(const element* str) {
	element ch1, ch2;
	boolean check = true;
	int len = strlen(str);
	DequeType dq;
	init_Deque(&dq);
	for (int i = 0; i < len; ++i) {
		if(isalpha(str[i])==1) add_front(&dq, str[i]); //�ҹ��ڶ�� �״�� ���ڿ��� �߰���
		else if(isalpha(str[i]) == 2) add_front(&dq, str[i]-32); //�빮�ڶ�� �ҹ��ڷ� �ٲ㼭 �־���.
	}
	while (1) {
		//ȸ���� �ƴ� ��� 
		ch1 = ch2 = '!';  //�ʱ�ȭ
		if (!is_empty(&dq)) ch1 = delete_front(&dq); //������� �ʴٸ� �տ��� �ϳ���.
		if (!is_empty(&dq)) ch2 = delete_rear(&dq); //������� �ʴٸ� �ڿ��� �ϳ���.
		if (ch1 != ch2 && ch1 != '!' && ch2 != '!') {
			//ch1�� ch2���� �ٸ��� ch1�� ch2�� �ʱ�ȭ ���� �ƴ� ���
			check = false; //ȸ���� �ƴ��� ǥ��
			break; // ��������.
		}
		if (is_empty(&dq)) break; //����ִٸ� ��������.
	}
	return check;
}