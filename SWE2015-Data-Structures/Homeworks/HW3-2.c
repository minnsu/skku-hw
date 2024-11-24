/*
// DO NOT INCLUDE ANY OTHER HEADER FILE
#include <stdio.h>
#include <stdlib.h>

char ar[100][100];
int visit[100][100];
int alpha[26] = {}; // cycle ������ 1�� ����
int key = 0; // �Ÿ��� �缭 cycle���� �߰��� ���� ��� �ǵ��� ���� ������ Ȯ��

void find(int i, int j, int size1, int size2, int starti, int startj) {
	visit[i][j] = 1; // visit ǥ��
	if (j + 1 < size2 && ar[i][j + 1] == ar[i][j] && visit[i][j + 1] == 0) { // ���� col
		key++; // �Ÿ� + 1
		find(i, j + 1, size1, size2, starti, startj); // ���
	}
	if (j - 1 >= 0 && ar[i][j - 1] == ar[i][j] && visit[i][j - 1] == 0) { // ���� col
		key++; // �Ÿ� + 1
		find(i, j - 1, size1, size2, starti, startj); // ���
	}
	if (i + 1 < size1 && ar[i + 1][j] == ar[i][j] && visit[i + 1][j] == 0) { // ���� row
		key++; // �Ÿ� + 1
		find(i + 1, j, size1, size2, starti, startj); // ���
	}
	if (i - 1 >= 0 && ar[i - 1][j] == ar[i][j] && visit[i - 1][j] == 0) { // ���� col
		key++; // �Ÿ� + 1
		find(i - 1, j, size1, size2, starti, startj); // ���
	}
	if (key >= 3 && ((i == starti && j + 1 == startj && ar[i][j + 1] == ar[i][j]) || (i == starti && j - 1 == startj && ar[i][j - 1] == ar[i][j]) || (i + 1 == starti && j == startj && ar[i + 1][j] == ar[i][j]) || (i - 1 == starti && j == startj && ar[i - 1][j] == ar[i][j]))) {
		// �Ÿ��� 3 �̻��̸鼭 �ֺ��� cycle�� ������ġ�� �ִٸ� cycle�� �ִٴ� ��
		alpha[ar[i][j] - 'a'] = 1; // alpha �迭�� 1�� ����
		return;
	}
	key = 0; // �߰��� ���� ��� ƨ�ܳ����� �Ÿ� �ʱ�ȭ
}
int main() { // Data Structures_SWE2015_41 ��μ<student_id>52
	int size1, size2;
	scanf("%d %d", &size1, &size2);
	for (int i = 0; i < size1; i++) {
		scanf("%s", ar[i]); // �ٴ� �Է�
	}

	int startrow, startcol; // cycle�� ���� ��ġ ����
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			key = 0; // key �ʱ�ȭ
			if (alpha[ar[i][j] - 'a'] == 1) { // �̹� cycle�� �ִ� ���ĺ����� ����Ϸ��� �� ��
				continue; // �������� �Ѿ
			}
			startrow = i; startcol = j; // ���� ��ġ ����
			find(i, j, size1, size2, startrow, startcol); // ����Լ� ����
			for (int i = 0; i < size1; i++) {
				for (int j = 0; j < size2; j++) {
					visit[i][j] = 0; // visit �ʱ�ȭ
				}
			}
		}
	}

	// ���
	int answer = 0;
	for (int i = 0; i < 26; i++) {
		if (alpha[i] == 1) {
			// alpha�迭���� cycle�� �ִ� ���ĺ� ���� ����
			answer++;
		}
	}
	printf("%d", answer);
	return 0;
}
*/