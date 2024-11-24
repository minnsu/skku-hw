/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include <string.h> // 직접 include
#define INF 999999
int diri[4] = { -1,0,1,0 }, dirj[4] = { 0,-1,0,1 };
int ddiri[4] = { 0, 1, 0, -1}, ddirj[4] = { 1, 0, -1, 0};
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
		pq tmp = map[child];
		map[child] = map[parent];
		map[parent] = tmp; // swap
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
		tmp = map[p];
		map[p] = map[child];
		map[child] = tmp; // swap
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
			if (dir == 0) mapweight[nexti][nextj].fromdir = 'u';
			else if (dir == 1) mapweight[nexti][nextj].fromdir = 'l';
			else if (dir == 2) mapweight[nexti][nextj].fromdir = 'd';
			else if (dir == 3) mapweight[nexti][nextj].fromdir = 'r';
			pushpq.i = nexti, pushpq.j = nextj, pushpq.weight = mapweight[nexti][nextj].weight, pushpq.accum = tmp.accum + mapweight[nexti][nextj].weight;
			push(pushpq);
		}
	}
}

void search2() {
	pq tmp;
	pq pushpq; // push용 위치
	while (last >= 1) {
		tmp = pop(); // 가장 누적 가중치 작은 위치 가져옴
		for (int dir = 0; dir < 4; dir++) {
			int nexti = tmp.i + ddiri[dir], nextj = tmp.j + ddirj[dir];
			if (nexti < 0 || nexti >= sizei || nextj < 0 || nextj >= sizej) {
				continue;
			}
			if (mapweight[nexti][nextj].accum <= tmp.accum + mapweight[nexti][nextj].weight) {
				continue;
			}
			mapweight[nexti][nextj].accum = tmp.accum + mapweight[nexti][nextj].weight;
			if (dir == 0) mapweight[nexti][nextj].fromdir = 'r';
			else if (dir == 1) mapweight[nexti][nextj].fromdir = 'd';
			else if (dir == 2) mapweight[nexti][nextj].fromdir = 'l';
			else if (dir == 3) mapweight[nexti][nextj].fromdir = 'u';
			pushpq.i = nexti, pushpq.j = nextj, pushpq.weight = mapweight[nexti][nextj].weight, pushpq.accum = tmp.accum + mapweight[nexti][nextj].weight;
			push(pushpq);
		}
	}
}

char answerstack[100]; // 정답 역순 저장
char answerstack2[100];
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



	for (int i = 0; i < sizei; i++) {
		for (int j = 0; j < sizej; j++) {
			mapweight[i][j].accum = INF;
		}
	}
	last = 1;
	map[1].i = 0, map[1].j = 0, map[1].weight = 0, map[1].accum = 0;
	search2();

	int answercount2 = 0;
	tempi = sizei - 1; tempj = sizej - 1;
	while (tempi != 0 || tempj != 0) { // 역순으로 정답 순서 answerstack에 저장
		answerstack2[answercount] = mapweight[tempi][tempj].fromdir;
		if (answerstack2[answercount] == 'u') { tempi = tempi + 1; }
		else if (answerstack2[answercount] == 'l') { tempj = tempj + 1; }
		else if (answerstack2[answercount] == 'd') { tempi = tempi - 1; }
		else if (answerstack2[answercount] == 'r') { tempj = tempj - 1; }
		answercount++;
	}

	int answerkey = 0;
	if (answercount == answercount2) {
		for (int i = answercount - 1; i >= 0; i--) {
			if (answerstack[i] > answerstack2[i]) {
				answerkey = 2;
			}
		}
	}
	else {
		if (answercount > answercount2) {
			answerkey = 2;
		}
	}
	if (answerkey != 2) {
		for (int i = answercount - 1; i >= 0; i--) { // 역순으로 출력
			printf("%c ", answerstack[i]);
		}
	}
	else {
		for (int i = answercount2 - 1; i >= 0; i--) { // 역순으로 출력
			printf("%c ", answerstack2[i]);
		}
	}
	return 0;
}

/*#include <stdio.h>
#include <stdlib.h>

#include <string.h> // 직접 include
#define INF 999999
int diri[4] = {-1,0,1,0}, dirj[4] = {0,-1,0,1};
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
		pq tmp = map[child];
		map[child] = map[parent];
		map[parent] = tmp; // swap
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
		tmp = map[p];
		map[p] = map[child];
		map[child] = tmp; // swap
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
			if (dir == 0) mapweight[nexti][nextj].fromdir = 'u';
			else if (dir == 1) mapweight[nexti][nextj].fromdir = 'l';
			else if (dir == 2) mapweight[nexti][nextj].fromdir = 'd';
			else if (dir == 3) mapweight[nexti][nextj].fromdir = 'r';
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
}*/