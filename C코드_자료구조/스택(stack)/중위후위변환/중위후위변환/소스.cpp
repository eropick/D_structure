#define _CRT_SECURE_NO_WARNINGS
#include "postfixop.h" //�������� ��� �Լ�
#include "my_stack.h" //����

void in_post(char* in,char* post); //���� ������ ������������ ��ȯ
int op_priority(char op); //�켱������ ���Ѵ�.

int main(int argc, char** argv) {
	char infix[100];
	char* postfix;
	printf("���� ���� �Է�: ");
	scanf("%[^\n]s", infix);
	postfix = (char*)calloc(strlen(infix) * 2 , sizeof(char));
	in_post(infix, postfix);
	printf("��������: %s\n", postfix);
	printf("�����: %d\n", eval(postfix));
	free(postfix);
	return 0;
}

void in_post(char* in, char* post) {
	int rlen = strlen(in);
	int p = -1; //post ������
	char ch;
	StackType op;
	init_stack(&op); //���� �ʱ�ȭ.'
	//(40+5)/9
	for (int i = 0; i < rlen;) {
		ch = in[i];
		switch (ch) {
			// ex)3*4+1 => 34*1+
			// ex)3-4+1 => 34-1+
			case '+':case '-':case '*':case '/': //�������� ��� 
				while (!is_empty(&op) && (op_priority(peek(&op)) >= op_priority(ch))) { 
					//�⺻������ ���� �������� ��ĵ�� ���� ���� ��µǾ�� �Ѵ�. �׷��� ���ؼ� �켱������ Ŀ���Ѵ�.
					//���ÿ� �ִ� �켱������ �� ũ�ų� ���ٸ� ���� ����ؾ� �ϱ� ������ �� pop���ش�. 
					//�켱������ �������� �տ� �� �� ���� ���Ǵ� �켱������ ���� ������
					//������ ����ְų� ch �켱������ �� Ŭ ��� ���ÿ� ��� �װ� �ȴ�. 
					post[++p]=pop(&op); //pop�� �������Ĺ迭�� ����.
				}
				push(&op, ch); //push
				++i;
				break;
			case '(': //���� ��ȣ�� ��� �ϴ� �״´�.
				//������ �켱������ ���� ���Ƽ� ���� ���Ŀ����� ch�� �� Ŀ���� ������ ��ȣ ���� ���̰� �ȴ�.
				push(&op, ch); //���ÿ� ����.
				++i;
				break;
			case ')': //������ ��ȣ�� ���
				while (peek(&op) != '(') {
					//peek�� (�� �� ������ 
					post[++p] = pop(&op); //pop�� �������Ĺ迭�� ����.
				}
				//peek�� (�� �Ǹ� 
				pop(&op);
				++i;
				break;;
			default: //�ǿ������� ��� �������Ŀ� ��� ����.
				if (p >= 0 && isdigit(post[p])) { //�������� �ǿ����ڶ�� ,�� �Ҵ�
					post[++p] = ',';
				}//���� ���� ���� ���ڿ��ٸ� ,�� �ٿ���.
				while (in[i] != '\0') {
					post[++p] = in[i];
					++i;
					if (!isdigit(in[i])) break; //���ڰ� �ƴϸ� ��������
				}
				break;
		}
	}
	//���������� ���ÿ� �����ִ� ��� �����ڸ� ��Ƴ�.
	while (!is_empty(&op)) post[++p] = pop(&op);
	post[++p] = '\0'; //���������� �ι��ڷ� ������ ��.
}


int op_priority(char op) { //�켱���� ��ȯ
	switch (op) {
		case '(': case ')':
			return 0;
		case '+': case '-':
			return 1;
		case '*': case '/':
			return 2;
	}
	return -1;
}