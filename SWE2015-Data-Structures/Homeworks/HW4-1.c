//DO NOT USE ADDITIONAL HEADER
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size, sumroot, sumOftree = 0; // 크기, 최댓값의 시작, 더해지는 임시 변수
int maxOfsum = 0; // 최댓값
int* tree; // tree 배열
void search(int rootindex) {
	sumOftree = sumOftree + tree[rootindex]; // 현재 tree 값 더함
	int childindex = (rootindex + 1) * 2; // 자식 tree index(우측)
	if (childindex - 1 > size || childindex > size) { // 자식 둘 중 하나라도 범위를 넘어가면 함수 종료
		return;
	}
	if ((tree[childindex - 1] != 0 && tree[childindex - 1] >= tree[rootindex]) || (tree[childindex] != 0 && tree[childindex] <= tree[rootindex])) { // BST의 조건을 만족하지 않으면(크기 정렬이 안되어있으면)
		sumOftree = 0; // 0으로 초기화 한 후 종료
		return;
	}
	search(childindex - 1); // 왼쪽 자식
	search(childindex); // 오른쪽 자식
}

int main() {
	scanf("%d", &size);
	tree = malloc(sizeof(int) * size);
	char input[500000];
	char* tok;
	gets(input); // 버퍼 비우기
	gets(input); // 문자열 입력
	int i = 0; tok = strtok(input, " "); // 첫번째 숫자 자르고 문자열 형태로 저장
	while (tok != NULL) {
		tree[i++] = atoi(tok); // tree에 int형태로 저장하고 i++, x였다면 0으로 저장
		tok = strtok(NULL, " "); // 다음 띄어쓰기 자르기
	} // 입력 후 tree에 저장

	for (int i = 0; i < size; i++) {
		sumOftree = 0; // 매번 초기화
		search(i);
		if (maxOfsum < sumOftree) { // 최댓값 갱신
			maxOfsum = sumOftree;
			sumroot = tree[i];
		}
	}

	// 출력
	if (maxOfsum <= 0) {
		printf("%d %c", 0, 'x');
	}
	else {
		printf("%d %d", maxOfsum, sumroot);
	}
	return 0;
}
*/