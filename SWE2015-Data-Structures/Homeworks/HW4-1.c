//DO NOT USE ADDITIONAL HEADER
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size, sumroot, sumOftree = 0; // ũ��, �ִ��� ����, �������� �ӽ� ����
int maxOfsum = 0; // �ִ�
int* tree; // tree �迭
void search(int rootindex) {
	sumOftree = sumOftree + tree[rootindex]; // ���� tree �� ����
	int childindex = (rootindex + 1) * 2; // �ڽ� tree index(����)
	if (childindex - 1 > size || childindex > size) { // �ڽ� �� �� �ϳ��� ������ �Ѿ�� �Լ� ����
		return;
	}
	if ((tree[childindex - 1] != 0 && tree[childindex - 1] >= tree[rootindex]) || (tree[childindex] != 0 && tree[childindex] <= tree[rootindex])) { // BST�� ������ �������� ������(ũ�� ������ �ȵǾ�������)
		sumOftree = 0; // 0���� �ʱ�ȭ �� �� ����
		return;
	}
	search(childindex - 1); // ���� �ڽ�
	search(childindex); // ������ �ڽ�
}

int main() {
	scanf("%d", &size);
	tree = malloc(sizeof(int) * size);
	char input[500000];
	char* tok;
	gets(input); // ���� ����
	gets(input); // ���ڿ� �Է�
	int i = 0; tok = strtok(input, " "); // ù��° ���� �ڸ��� ���ڿ� ���·� ����
	while (tok != NULL) {
		tree[i++] = atoi(tok); // tree�� int���·� �����ϰ� i++, x���ٸ� 0���� ����
		tok = strtok(NULL, " "); // ���� ���� �ڸ���
	} // �Է� �� tree�� ����

	for (int i = 0; i < size; i++) {
		sumOftree = 0; // �Ź� �ʱ�ȭ
		search(i);
		if (maxOfsum < sumOftree) { // �ִ� ����
			maxOfsum = sumOftree;
			sumroot = tree[i];
		}
	}

	// ���
	if (maxOfsum <= 0) {
		printf("%d %c", 0, 'x');
	}
	else {
		printf("%d %d", maxOfsum, sumroot);
	}
	return 0;
}
*/