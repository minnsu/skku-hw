//DO NOT USE ADDITIONAL HEADER
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct curri {
	char score;
	struct curri* presub; // �������� ������
}curri;
curri*** loadmap;
int semester; // �б� ��
int targetnum; // ���� �б� ��
char* targetscore; // ���� score �迭
int* a; // �� �б⺰ ���� �� �迭

int answercount = 0;
void find() { // �Ųٷ� ã�� ��
	curri* temp; // �ӽ� ������
	int temptargetnum;
	for (int i = semester - 1; i >= targetnum - 1; i--) {
		for (int j = 0; j < a[i]; j++) {
			temp = loadmap[i][j]; // ����
			temptargetnum = targetnum - 1;
			while (temptargetnum >= 0 && temp->score == targetscore[temptargetnum]) {
				// ���� ���� �ݺ�, i ������ targetnum-1�̻��̹Ƿ� temptargetnum�� 0�̻��̸� temp�� NULL �ȵ�
				temptargetnum--;
				temp = temp->presub;
			}
			if (temptargetnum == -1) { // -1�̸� ����
				answercount++;
			}
		}
	}
}

int main() {
	scanf("%d", &semester);
	loadmap = (curri***)malloc(sizeof(curri**) * semester);
	int subject;
	char score;
	a = (int*)malloc(sizeof(int) * semester);
	for (int i = 0; i < semester; i++) {
		scanf("%d ", &subject);
		a[i] = subject; // �б�� ����� ����
		loadmap[i] = (curri**)malloc(sizeof(curri*) * subject);
		for (int j = 0; j < subject; j++) {
			scanf("%c ", &score);
			loadmap[i][j] = (curri*)malloc(sizeof(curri));
			loadmap[i][j]->score = score; // �� ���� score ����
		}
	}
	int presubnum;
	char pre[20];
	char* tok;
	int semnum1, subnum1, semnum2, subnum2;
	scanf("%d", &presubnum);
	gets(pre); // ���� ����
	for (int i = 0; i < presubnum; i++) {
		gets(pre);
		tok = strtok(pre, ":");
		semnum1 = atoi(tok); // �������� �б�
		tok = strtok(NULL, " ");
		subnum1 = atoi(tok); // �������� ����(��ġ)
		tok = strtok(NULL, ":");
		semnum2 = atoi(tok); // ���� �б�
		tok = strtok(NULL, " ");
		subnum2 = atoi(tok); // ���� ���� ����(��ġ)
		loadmap[semnum2 - 1][subnum2 - 1]->presub = loadmap[semnum1 - 1][subnum1 - 1]; // �������� ������ ����
	}
	scanf("%d", &targetnum);
	targetscore = malloc(sizeof(char) * targetnum);
	for (int i = 0; i < targetnum; i++) {
		scanf(" %c", &targetscore[i]);
	} // ���� �б� ���� �� ������ score �迭 �Է�

	find();
	printf("%d", answercount);
	return 0;
}
*/