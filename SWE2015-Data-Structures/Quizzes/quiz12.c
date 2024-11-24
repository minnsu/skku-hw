#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS_
int failure[6] = { -1, -1, 0, 1, 2, 0 };
int pmatch(char* string, char* pat) { // Data Structures_SWE2015_41 ��μ<student_id>52
	int i = 0; // i, j ���� �� �ʱ�ȭ
	int j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	for (; i < lens && j < lenp;) { // ���ǽİ� ������ �����Ͽ� while�� ���� ����� �ϵ��� ��.
		if (string[i] == pat[j]) {
			i++;
			j++;
		}
		else if (j == 0) {
			i++;
		}
		else {
			j = failure[j - 1] + 1;
		}
	} // for �ӿ� ���� ���ǹ��� ��ġ�鼭 i, j ���� ��ȭ�ϰ� �ݺ����� Ż���� �� �ִ� ������ ��.
	return (j == lenp ? i - lenp : -1);
}

int main12() {
	char* string = "aabbababaababaaab";
	char* pat = "ababaa";

	printf("%d\n", pmatch(string, pat));
	return 0;
}