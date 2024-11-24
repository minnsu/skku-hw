#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

void stringremove(char* s, int i, int j) { // Data Structures_SWE2015_41 ��μ<student_id>52
	char string[MAX_SIZE];
	char *temp = string;
	char string2[MAX_SIZE];
	char* temp2 = string2;

	memset(string, 0, sizeof(string));
	strncpy(temp, s, i); // s�� i������ ���ڸ� ����
	memset(temp2, 0, sizeof(temp2));
	strncpy(temp2, s + i + j, strlen(s)-i-j); // �����Ϸ��� �κ��� �� �κ��� ����

	strcat(temp, temp2); // �̾���̱�
	strcpy(s, temp); // s�� �ٽ� �����ؼ� �����
}

int main9() {
	char* s = "ABCDEFGHIJ";
	stringremove(s, 3, 4);
	printf("%s\n", s);
	return 0;
}