/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include <string.h> // ���� include
#define INF 999999
int diri[4] = { -1,0,1,0 }, dirj[4] = { 0,-1,0,1 };
int ddiri[4] = { 0, 1, 0, -1}, ddirj[4] = { 1, 0, -1, 0};
int sizei, sizej;

typedef struct pq {
	int i, j;
	int weight; // �⺻ ����
	int accum; // ���� ����
	char fromdir; // ���� ���� ������ ����
}pq;
pq map[INF];
pq** mapweight;
int last = 1;

void push(pq new) {
	map[++last] = new; // ���� �ڿ� �߰�
	for (int child = last, parent = child / 2; map[child].accum < map[parent].accum; child = parent, parent = child / 2) { // �θ𺸴� ������ ����ؼ� �ö�
		pq tmp = map[child];
		map[child] = map[parent];
		map[parent] = tmp; // swap
	}
}
pq pop() {
	pq ret = map[1]; // �� �� ������ ��
	pq tmp;
	map[1] = map[last--]; // ���� ���� ���� 1�� �ű�
	int child;
	for (int p = 1, lc = p * 2, rc = lc + 1; lc <= last; p = child, lc = p * 2, rc = lc + 1) { // �ڽ� �� ���� ���� ���ؼ� �ٲٱ� �ݺ�
		if (rc > last) { // ������ �ڽ� ���ٸ�
			child = lc;
		}
		else { // �ڽ� �� �� ���� ��
			child = (map[lc].accum < map[rc].accum ? map[lc].accum : map[rc].accum); // �� �� ���� ��(min heap)
		}
		if (map[p].accum < map[child].accum) { // min heap �Ϸ�
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
	pq pushpq; // push�� ��ġ
	while (last >= 1) {
		tmp = pop(); // ���� ���� ����ġ ���� ��ġ ������
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
	pq pushpq; // push�� ��ġ
	while (last >= 1) {
		tmp = pop(); // ���� ���� ����ġ ���� ��ġ ������
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

char answerstack[100]; // ���� ���� ����
char answerstack2[100];
int main() {
	char input[5000];
	char* tok;
	scanf("%d %d ", &sizei, &sizej); // �ڿ� ���� -> ���� ���ۿ�
	mapweight = malloc(sizeof(pq*) * sizei);
	for (int i = 0; i < sizei; i++) {
		mapweight[i] = malloc(sizeof(pq) * sizej);
	}
	for (int i = 0; i < sizei; i++) {
		gets(input);
		int j = 0; tok = strtok(input, " ");
		while (tok != NULL) {
			mapweight[i][j].weight = atoi(tok);
			mapweight[i][j].accum = INF; // ���Ѵ�� �ʱ�ȭ
			tok = strtok(NULL, " ");
			j++;
		} // �Է� �� tree�� ����
	}
	map[1].i = 0, map[1].j = 0, map[1].weight = 0, map[1].accum = 0; // ������ġ : 0,0
	search();
	int answercount = 0;
	int tempi = sizei - 1, tempj = sizej - 1;
	while (tempi != 0 || tempj != 0) { // �������� ���� ���� answerstack�� ����
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
	while (tempi != 0 || tempj != 0) { // �������� ���� ���� answerstack�� ����
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
		for (int i = answercount - 1; i >= 0; i--) { // �������� ���
			printf("%c ", answerstack[i]);
		}
	}
	else {
		for (int i = answercount2 - 1; i >= 0; i--) { // �������� ���
			printf("%c ", answerstack2[i]);
		}
	}
	return 0;
}

/*#include <stdio.h>
#include <stdlib.h>

#include <string.h> // ���� include
#define INF 999999
int diri[4] = {-1,0,1,0}, dirj[4] = {0,-1,0,1};
int sizei, sizej;

typedef struct pq {
	int i, j;
	int weight; // �⺻ ����
	int accum; // ���� ����
	char fromdir; // ���� ���� ������ ����
}pq;
pq map[INF];
pq** mapweight;
int last = 1;

void push(pq new) {
	map[++last] = new; // ���� �ڿ� �߰�
	for (int child = last, parent = child / 2; map[child].accum < map[parent].accum; child = parent, parent = child / 2) { // �θ𺸴� ������ ����ؼ� �ö�
		pq tmp = map[child];
		map[child] = map[parent];
		map[parent] = tmp; // swap
	}
}
pq pop() {
	pq ret = map[1]; // �� �� ������ ��
	pq tmp;
	map[1] = map[last--]; // ���� ���� ���� 1�� �ű�
	int child;
	for (int p = 1, lc = p * 2, rc = lc + 1; lc <= last; p = child, lc = p * 2, rc = lc + 1) { // �ڽ� �� ���� ���� ���ؼ� �ٲٱ� �ݺ�
		if (rc > last) { // ������ �ڽ� ���ٸ�
			child = lc;
		}
		else { // �ڽ� �� �� ���� ��
			child = (map[lc].accum < map[rc].accum ? map[lc].accum : map[rc].accum); // �� �� ���� ��(min heap)
		}
		if (map[p].accum < map[child].accum) { // min heap �Ϸ�
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
	pq pushpq; // push�� ��ġ
	while (last >= 1) {
		tmp = pop(); // ���� ���� ����ġ ���� ��ġ ������
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

char answerstack[100]; // ���� ���� ����
int main() {
	char input[5000];
	char* tok;
	scanf("%d %d ", &sizei, &sizej); // �ڿ� ���� -> ���� ���ۿ�
	mapweight = malloc(sizeof(pq*) * sizei);
	for (int i = 0; i < sizei; i++) {
		mapweight[i] = malloc(sizeof(pq) * sizej);
	}
	for (int i = 0; i < sizei; i++) {
		gets(input);
		int j = 0; tok = strtok(input, " ");
		while (tok != NULL) {
			mapweight[i][j].weight = atoi(tok);
			mapweight[i][j].accum = INF; // ���Ѵ�� �ʱ�ȭ
			tok = strtok(NULL, " ");
			j++;
		} // �Է� �� tree�� ����
	}
	map[1].i = 0, map[1].j = 0, map[1].weight = 0, map[1].accum = 0; // ������ġ : 0,0
	search();

	int answercount = 0;
	int tempi = sizei - 1, tempj = sizej - 1;
	while (tempi != 0 || tempj != 0) { // �������� ���� ���� answerstack�� ����
		answerstack[answercount] = mapweight[tempi][tempj].fromdir;
		if (answerstack[answercount] == 'u') { tempi = tempi + 1; }
		else if (answerstack[answercount] == 'l') { tempj = tempj + 1; }
		else if (answerstack[answercount] == 'd') { tempi = tempi - 1; }
		else if (answerstack[answercount] == 'r') { tempj = tempj - 1; }
		answercount++;
	}
	for (int i = answercount - 1; i >= 0; i--) { // �������� ���
		printf("%c ", answerstack[i]);
	}
	return 0;
}*/