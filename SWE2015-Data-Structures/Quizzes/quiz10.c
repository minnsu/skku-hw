#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS_

int strnchar(char* s, char p) { // Data Structures_SWE2015_41 ��μ<student_id>52
	int count = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == p) { // p�� ������ �� �빮�ڿ� �ҹ��ڸ� ���� �ٸ� ������ ���
			count++; // ���� �� count ����
		}
	}
	return count; // count ��ȯ
}

int main10() {
	char* s = "My Name is Kim Min su!";
	printf("%d\n", strnchar(s, '!'));
	return 0;
}