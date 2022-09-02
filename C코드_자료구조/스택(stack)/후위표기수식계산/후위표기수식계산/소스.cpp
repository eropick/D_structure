#define _CRT_SECURE_NO_WARNINGS
#include "myStack.h"
#include <string.h>
#include <ctype.h>
int eval(char exp[]);

int main(int argc, char* argv[]) {
	//atoi����ؼ� ���ڿ��� ���ڷ� ��ȯ �� ���ÿ� ����.
	char p[100];
	char* pf;
	printf("����ǥ�����?: ");
	scanf("%[^\n]s", p);
	printf("�������? %d\n",eval(p));
	return 0;
}

int eval(char exp[]) {
	int op1, op2,rlen,value=0;
	char ch;
	StackType s;
	init_stack(&s);
	rlen = strlen(exp);
	for (int i = 0; i < rlen;) {
		ch=exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ',' && ch != ' ') { //�����ڳ� �����̳� ,�� �ƴ϶�� ���ÿ� �ִ´�.
			if (!isdigit(ch)) { //���� ���ڰ� �ƴѰ�� ����.
				fprintf(stderr, "����: ���ڰ� �ƴ� ���� ����.\n");
				return 0;
			}
			value = atoi(exp+i); //���ڿ� ���� ���� ������ ���ڷ� ��ȯ
			push(&s, value);
			while (exp[i] != '\0') { //�ι��ڰ� ������ �ݺ� ����
				++i;
				if (!isdigit(exp[i])) break; //���� ���ڰ� ������ �ʴ´ٸ� ���� ���
			}
		}
		else if (ch == ' ' || ch == ',') ++i; //�����̳� ,�� ���� ��� i���� 1������Ŵ.
		else { //�����ڰ� ������ ���
			op1 = pop(&s);
			op2 = pop(&s);
			switch (ch) {
				case '+':
					push(&s, op2 + op1);
					break;
				case '-':
					push(&s, op2 - op1);
					break;
				case '*':
					push(&s, op2 * op1);
					break;
				case '/':
					push(&s, op2 / op1);
					break;
			}
			++i;
		}
	}
	return pop(&s);
}