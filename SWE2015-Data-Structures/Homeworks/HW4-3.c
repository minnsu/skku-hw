//DO NOT USE ADDITIONAL HEADER
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct curri {
	char score;
	struct curri* presub; // 선수강의 포인터
}curri;
curri*** loadmap;
int semester; // 학기 수
int targetnum; // 맞출 학기 수
char* targetscore; // 맞출 score 배열
int* a; // 각 학기별 과목 수 배열

int answercount = 0;
void find() { // 거꾸로 찾을 것
	curri* temp; // 임시 포인터
	int temptargetnum;
	for (int i = semester - 1; i >= targetnum - 1; i--) {
		for (int j = 0; j < a[i]; j++) {
			temp = loadmap[i][j]; // 선택
			temptargetnum = targetnum - 1;
			while (temptargetnum >= 0 && temp->score == targetscore[temptargetnum]) {
				// 같은 동안 반복, i 범위가 targetnum-1이상이므로 temptargetnum이 0이상이면 temp는 NULL 안됨
				temptargetnum--;
				temp = temp->presub;
			}
			if (temptargetnum == -1) { // -1이면 정답
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
		a[i] = subject; // 학기당 과목수 저장
		loadmap[i] = (curri**)malloc(sizeof(curri*) * subject);
		for (int j = 0; j < subject; j++) {
			scanf("%c ", &score);
			loadmap[i][j] = (curri*)malloc(sizeof(curri));
			loadmap[i][j]->score = score; // 각 과목별 score 저장
		}
	}
	int presubnum;
	char pre[20];
	char* tok;
	int semnum1, subnum1, semnum2, subnum2;
	scanf("%d", &presubnum);
	gets(pre); // 버퍼 비우기
	for (int i = 0; i < presubnum; i++) {
		gets(pre);
		tok = strtok(pre, ":");
		semnum1 = atoi(tok); // 선수과목 학기
		tok = strtok(NULL, " ");
		subnum1 = atoi(tok); // 선수과목 순서(위치)
		tok = strtok(NULL, ":");
		semnum2 = atoi(tok); // 다음 학기
		tok = strtok(NULL, " ");
		subnum2 = atoi(tok); // 연계 과목 순서(위치)
		loadmap[semnum2 - 1][subnum2 - 1]->presub = loadmap[semnum1 - 1][subnum1 - 1]; // 선수과목 포인터 연결
	}
	scanf("%d", &targetnum);
	targetscore = malloc(sizeof(char) * targetnum);
	for (int i = 0; i < targetnum; i++) {
		scanf(" %c", &targetscore[i]);
	} // 맞출 학기 수와 각 과목의 score 배열 입력

	find();
	printf("%d", answercount);
	return 0;
}
*/