/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include <string.h> // 직접 include
#define INF 999999
int diri[2][4] = { { -1,0,1,0 }, { -1,0,1,0 } }, dirj[2][4] = { {0,-1,0,1}, {0,1,0,-1} };
char dirarr[2][4] = { {'u', 'l', 'd', 'r'}, { 'u', 'r', 'd', 'l' } };
int sizei, sizej;

typedef struct pq {
	int i, j;
	int weight; // 기본 가중
	int accum; // 누적 가중
	char fromdir; // 누적 가중 갱신한 방향
}pq;
pq map[2][INF];
pq mapweight[2][20][20];
int last;

void push(pq new, int i) {
	map[i][++last] = new; // 가장 뒤에 추가
	for (int child = last, parent = child / 2; map[i][child].accum < map[i][parent].accum; child = parent, parent = child / 2) { // 부모보다 작으면 계속해서 올라감
		pq tmp = map[i][child]; map[i][child] = map[i][parent]; map[i][parent] = tmp; // swap
	}
}
pq pop(int i) {
	pq ret = map[i][1]; // 맨 앞 리턴할 것
	pq tmp;
	map[i][1] = map[i][last--]; // 가장 뒤의 것을 1로 옮김
	int child;
	for (int p = 1, lc = p * 2, rc = lc + 1; lc <= last; p = child, lc = p * 2, rc = lc + 1) { // 자식 중 작은 것을 택해서 바꾸기 반복
		if (rc > last) { // 오른쪽 자식 없다면
			child = lc;
		}
		else { // 자식 둘 다 있을 때
			child = (map[i][lc].accum < map[i][rc].accum ? map[i][lc].accum : map[i][rc].accum); // 둘 중 작은 것(min heap)
		}
		if (map[i][p].accum < map[i][child].accum) { // min heap 완료
			break;
		}
		tmp = map[i][p]; map[i][p] = map[i][child]; map[i][child] = tmp; // swap
	}
	return ret;
}
void search(int sel) {
	last = 1;
	pq tmp;
	pq pushpq; // push용 위치
	while (last >= 1) {
		tmp = pop(sel); // 가장 누적 가중치 작은 위치 가져옴
		for (int dir = 0; dir < 4; dir++) {
			int nexti = tmp.i + diri[sel][dir], nextj = tmp.j + dirj[sel][dir];
			if (nexti < 0 || nexti >= sizei || nextj < 0 || nextj >= sizej) {
				continue;
			}
			if (mapweight[sel][nexti][nextj].accum <= tmp.accum + mapweight[sel][nexti][nextj].weight) {
				/*if (mapweight[nexti][nextj].accum == tmp.accum + mapweight[nexti][nextj].weight && dirarr[sel][dir] > mapweight[nexti][nextj].fromdir) {
					mapweight[nexti][nextj].fromdir = dirarr[sel][dir] ;
				}*/
				continue;
			}
			mapweight[sel][nexti][nextj].accum = tmp.accum + mapweight[sel][nexti][nextj].weight;
			mapweight[sel][nexti][nextj].fromdir = dirarr[sel][dir];
			pushpq.i = nexti, pushpq.j = nextj, pushpq.weight = mapweight[sel][nexti][nextj].weight, pushpq.accum = tmp.accum + mapweight[sel][nexti][nextj].weight;
			push(pushpq, sel);
		}
	}
}

char answerstack[2][100]; // 정답 역순 저장
int main() {
	char input[5000];
	char* tok;
	scanf("%d %d ", &sizei, &sizej); // 뒤에 띄어쓰기 -> 엔터 버퍼용
	for (int i = 0; i < sizei; i++) {
		gets(input);
		int j = 0; tok = strtok(input, " ");
		while (tok != NULL) {
			mapweight[0][i][j].weight = atoi(tok); mapweight[1][i][j].weight = atoi(tok);
			mapweight[0][i][j].accum = INF; mapweight[1][i][j].accum = INF; // 무한대로 초기화
			tok = strtok(NULL, " ");
			j++;
		} // 입력 후 tree에 저장
	}
	map[0][1].i = 0, map[0][1].j = 0, map[0][1].weight = 0, map[0][1].accum = 0; // 시작위치 : 0,0
	search(0);
	int answercount = 0;
	int tempi = sizei - 1, tempj = sizej - 1;
	while (tempi != 0 || tempj != 0) { // 역순으로 정답 순서 answerstack에 저장
		answerstack[0][answercount] = mapweight[0][tempi][tempj].fromdir;
		if (answerstack[0][answercount] == 'u') { tempi = tempi + 1; }
		else if (answerstack[0][answercount] == 'l') { tempj = tempj + 1; }
		else if (answerstack[0][answercount] == 'd') { tempi = tempi - 1; }
		else if (answerstack[0][answercount] == 'r') { tempj = tempj - 1; }
		answercount++;
	}
	
	map[1][1].i = 0, map[1][1].j = 0, map[1][1].weight = 0, map[1][1].accum = 0;
	search(1);
	int answercount2 = 0;
	tempi = sizei - 1, tempj = sizej - 1;
	while (tempi != 0 || tempj != 0) { // 역순으로 정답 순서 answerstack에 저장
		answerstack[1][answercount2] = mapweight[1][tempi][tempj].fromdir;
		if (answerstack[1][answercount2] == 'u') { tempi = tempi + 1; }
		else if (answerstack[1][answercount2] == 'l') { tempj = tempj + 1; }
		else if (answerstack[1][answercount2] == 'd') { tempi = tempi - 1; }
		else if (answerstack[1][answercount2] == 'r') { tempj = tempj - 1; }
		answercount2++;
	}

	int answerkey = 0;
	for (int i = answercount - 1, j = answercount2 - 1; i >= 0 && j >= 0; i--, j--) {
		if (answerstack[0][i] < answerstack[1][j]) {
			answerkey = 1;
			break;
		}
		if (answerstack[0][i] > answerstack[1][j]) {
			answerkey = 2;
			break;
		}
	}
	if (answerkey <= 1) {
		for (int i = answercount - 1; i >= 0; i--) { // 역순으로 출력
			printf("%c ", answerstack[0][i]);
		}
	}
	else {
		for (int i = answercount2 - 1; i >= 0; i--) { // 역순으로 출력
			printf("%c ", answerstack[1][i]);
		}
	}
	return 0;
}
*/
/*
#include <string.h> // 직접 include
#define INF 999999
int diri[4] = {-1,0,1,0}, dirj[4] = {0,-1,0,1};
char dirarr[4] = { 'u', 'l', 'd', 'r' };
int sizei, sizej;

typedef struct pq {
	int i, j;
	int weight; // 기본 가중
	int accum; // 누적 가중
	char fromdir; // 누적 가중 갱신한 방향
}pq;
pq map[INF];
pq** mapweight;
int last = 1;

void push(pq new) {
	map[++last] = new; // 가장 뒤에 추가
	for (int child = last, parent = child / 2; map[child].accum < map[parent].accum; child = parent, parent = child / 2) { // 부모보다 작으면 계속해서 올라감
		pq tmp = map[child]; map[child] = map[parent]; map[parent] = tmp; // swap
	}
}
pq pop() {
	pq ret = map[1]; // 맨 앞 리턴할 것
	pq tmp;
	map[1] = map[last--]; // 가장 뒤의 것을 1로 옮김
	int child;
	for (int p = 1, lc = p * 2, rc = lc + 1; lc <= last; p = child, lc = p * 2, rc = lc + 1) { // 자식 중 작은 것을 택해서 바꾸기 반복
		if (rc > last) { // 오른쪽 자식 없다면
			child = lc;
		}
		else { // 자식 둘 다 있을 때
			child = (map[lc].accum < map[rc].accum ? map[lc].accum : map[rc].accum); // 둘 중 작은 것(min heap)
		}
		if (map[p].accum < map[child].accum) { // min heap 완료
			break;
		}
		tmp = map[p]; map[p] = map[child]; map[child] = tmp; // swap
	}
	return ret;
}
void search() {
	pq tmp;
	pq pushpq; // push용 위치
	while (last >= 1) {
		tmp = pop(); // 가장 누적 가중치 작은 위치 가져옴
		for (int dir = 0; dir < 4; dir++) {
			int nexti = tmp.i + diri[dir], nextj = tmp.j + dirj[dir];
			if (nexti < 0 || nexti >= sizei || nextj < 0 || nextj >= sizej) {
				continue;
			}
			if (mapweight[nexti][nextj].accum <= tmp.accum + mapweight[nexti][nextj].weight) {
				continue;
			}
			mapweight[nexti][nextj].accum = tmp.accum + mapweight[nexti][nextj].weight;
			mapweight[nexti][nextj].fromdir = dirarr[dir];

			pushpq.i = nexti, pushpq.j = nextj, pushpq.weight = mapweight[nexti][nextj].weight, pushpq.accum = tmp.accum + mapweight[nexti][nextj].weight;
			push(pushpq);
		}
	}
}

char answerstack[100]; // 정답 역순 저장
int main() {
	char input[5000];
	char* tok;
	scanf("%d %d ", &sizei, &sizej); // 뒤에 띄어쓰기 -> 엔터 버퍼용
	mapweight = malloc(sizeof(pq*) * sizei);
	for (int i = 0; i < sizei; i++) {
		mapweight[i] = malloc(sizeof(pq) * sizej);
	}
	for (int i = 0; i < sizei; i++) {
		gets(input);
		int j = 0; tok = strtok(input, " ");
		while (tok != NULL) {
			mapweight[i][j].weight = atoi(tok);
			mapweight[i][j].accum = INF; // 무한대로 초기화
			tok = strtok(NULL, " ");
			j++;
		} // 입력 후 tree에 저장
	}
	map[1].i = 0, map[1].j = 0, map[1].weight = 0, map[1].accum = 0; // 시작위치 : 0,0
	search();

	int answercount = 0;
	int tempi = sizei - 1, tempj = sizej - 1;
	while (tempi != 0 || tempj != 0) { // 역순으로 정답 순서 answerstack에 저장
		answerstack[answercount] = mapweight[tempi][tempj].fromdir;
		if (answerstack[answercount] == 'u') { tempi = tempi + 1; }
		else if (answerstack[answercount] == 'l') { tempj = tempj + 1; }
		else if (answerstack[answercount] == 'd') { tempi = tempi - 1; }
		else if (answerstack[answercount] == 'r') { tempj = tempj - 1; }
		answercount++;
	}
	for (int i = answercount - 1; i >= 0; i--) { // 역순으로 출력
		printf("%c ", answerstack[i]);
	}
	return 0;
}
*/