// DO NOT INCLUDE ANY OTHER HEADER FILE
/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char map[10][10];
char* answer[10];

typedef struct MapQ {
	char map[10][10];
	int mi, mj; // I ��ġ
	int fi, fj; // F ��ġ
	int fromindex; // ��� front index���� �� ������ ����
	char* dir; // ���� ���ڿ� : LEFT DOWN RIGHT UP
	int length; // �̵� �Ÿ�, 10���� ũ�� break
}MapQ;

MapQ Map[999999];
int front = -1, rear = -1;

void BFS(int startmi, int startmj, int startfi, int startfj, int desti, int destj, int sizei, int sizej) {
	int diri[4] = { 0,1,0,-1 };
	int dirj[4] = { -1,0,1,0 };
	// ������� ����, �Ʒ���, ������, ����
	rear++;
	Map[rear].mi = startmi, Map[rear].mj = startmj;
	Map[rear].fi = startfi, Map[rear].fj = startfj;
	Map[rear].length = 1;
	for (int i = 0; i < sizei; i++) {
		for (int j = 0; j < sizej; j++) {
			Map[rear].map[i][j] = map[i][j];
		}
	}
	// ���� �ʰ� I, F ��ġ Map[0]�� ����
	while (front < rear && Map[rear].length <= 10) {
		front++;
		int mi, mj;
		int fi, fj;
		char tempmap[10][10];
		// �ӽ� ���� ������ ��
		for (int dir = 0; dir < 4; dir++) {
			mi = Map[front].mi, mj = Map[front].mj;
			fi = Map[front].fi, fj = Map[front].fj;
			for (int i = 0; i < sizei; i++) {
				for (int j = 0; j < sizej; j++) {
					tempmap[i][j] = Map[front].map[i][j];
				}
			}
			while ((diri[dir] != 0 || dirj[dir] != 0) && (tempmap[mi + diri[dir]][mj + dirj[dir]] == '.' || tempmap[fi + diri[dir]][fj + dirj[dir]] == '.')) {
				if (tempmap[mi + diri[dir]][mj + dirj[dir]] == '.' && tempmap[fi + diri[dir]][fj + dirj[dir]] == '.') {
					// �Ѵ� ������ �� �ӽ� �ʰ� �ӽ� I, F ��ġ ����
					tempmap[mi][mj] = '.'; tempmap[fi][fj] = '.';
					mi = mi + diri[dir]; mj = mj + dirj[dir];
					fi = fi + diri[dir]; fj = fj + dirj[dir];
					tempmap[mi][mj] = 'I'; tempmap[fi][fj] = 'F';
				}
				else if (tempmap[mi + diri[dir]][mj + dirj[dir]] == '.' && tempmap[fi + diri[dir]][fj + dirj[dir]] != '.') {
					// I�� ������ �� �ӽ� �ʰ� I ��ġ ����
					tempmap[mi][mj] = '.';
					mi = mi + diri[dir]; mj = mj + dirj[dir];
					tempmap[mi][mj] = 'I';
				}
				else if (tempmap[mi + diri[dir]][mj + dirj[dir]] != '.' && tempmap[fi + diri[dir]][fj + dirj[dir]] == '.') {
					// F�� ������ �� �ӽ� �ʰ� F ��ġ ����
					tempmap[fi][fj] = '.';
					fi = fi + diri[dir]; fj = fj + dirj[dir];
					tempmap[fi][fj] = 'F';
				}
			} // dir �� �ϳ��� �� ���� �ְ�, I �Ǵ� F�� �� �� �� �� �ִ� ���� �ִ� ���� ����

			rear++;
			Map[rear].mi = mi; Map[rear].mj = mj;
			Map[rear].fi = fi; Map[rear].fj = fj;
			Map[rear].length = Map[front].length + 1;
			Map[rear].fromindex = front;
			if (dir == 0) { Map[rear].dir = "LEFT"; }
			else if (dir == 1) { Map[rear].dir = "DOWN"; }
			else if (dir == 2) { Map[rear].dir = "RIGHT"; }
			else if (dir == 3) { Map[rear].dir = "UP"; }
			for (int i = 0; i < sizei; i++) {
				for (int j = 0; j < sizej; j++) {
					Map[rear].map[i][j] = tempmap[i][j];
				}
			}
			// ���ο� rear�� I, F, length, fromindex, dir, map ����

			if (fi + diri[dir] == desti && fj + dirj[dir] == destj) {
				break;
			} // F�� ��ġ�� ���� �Ǵ� ���� T�� �����ߴٸ� ���� -> break
			if (mi + diri[dir] == desti && mj + dirj[dir] == destj) { // F�� �����ϱ��� I�� ����
				int count = 0;
				while (rear >= 0) { // answer ���ڿ� �迭�� �����ϴ� ����
					answer[count++] = Map[rear].dir;
					rear = Map[rear].fromindex;
					if (rear == 0) {
						break;
					}
				}
				for (int i = count - 1; i >= 0; i--) { // answer ���ڿ� �迭 ���� ��� -> ���ۺ��� ��� ����
					printf("%s\n", answer[i]);
				}
				return;
			}
		}
	}
	printf("IMPOSSIBLE"); // ���� �� IMPOSSIBLE
}

int main() { // Data Structures_SWE2015_41 ��μ<student_id>52
	int sizei, sizej;
	int mi, mj, fi, fj, di, dj;
	scanf("%d %d", &sizei, &sizej);
	for (int i = 0; i < sizei; i++) {
		scanf("%s", map[i]);
		for (int j = 0; j < sizej; j++) {
			if (map[i][j] == 'I') {
				mi = i; mj = j;
			}
			else if (map[i][j] == 'F') {
				fi = i; fj = j;
			}
			else if (map[i][j] == 'T') {
				di = i; dj = j;
			}
		}
	}

	BFS(mi, mj, fi, fj, di, dj, sizei, sizej);
	return 0;
}*/