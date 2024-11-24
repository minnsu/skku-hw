/*
#include <stdio.h>
int pact(int num) { // ���丮��
	if (num == 1) {
		return 1;
	}
	return num * pact(num - 1);
}
int temp[5040][7]; // 7! ������ ��� ������ ������ �������迭
int count = 0; // temp�� ���� ������Ű�� ����
void swap(int* index, int i, int j) { // index �迭 ���� swap�ϴ� function
	int temp;
	temp = index[i];
	index[i] = index[j];
	index[j] = temp;
}

int permu(int* index, int Total, int size) { // index �迭 ������ �ٲپ� temp�� �����ϴ� �Լ�
	int i;
	if (size == 1) {
		for (i = 0; i < Total; i++) {
			temp[count][i] = index[i]; // temp[count][i]�� index[i]�� ����
		}
		count++; // temp�� ���� ������ �ѱ�
		return 0;
	}
	for (i = 0; i < size; i++) {
		swap(index, i, size - 1); // i��°�� size-1��° ����
		permu(index, Total, size - 1); // �ٲ��� ���·� ����Լ�
		swap(index, i, size - 1); // �ٲ� �� �����·� ����
	}
}

int main() { // Data Structures_SWE2015_41 ��μ<student_id>52
	int size;
	scanf("%d", &size);
	int graph1[size][size];
	int graph2[size][size];
	int indexarr[size]; // 0 1 2 3...size-1 �����ϴ� �迭

	for (int i = 0; i < size; i++) {
		indexarr[i] = i;
		for (int j = 0; j < size; j++) {
			scanf("%d", &graph1[i][j]);
		}
	} // graph1 �Է�, indexarr ����
	printf("\n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			scanf("%d", &graph2[i][j]);
		}
	} // graph2 �Է�

	permu(indexarr, size, size); // temp�� ��� ������ �ε������� ����

	int key = 0; // Ż�� ���� �� ����
	for (int i = 0; i < pact(size); i++) { // �ִ� ���� pact(size)
		for (int j = 0; j < size; j++) {
			// �� �񱳵� �ٲ� ����, �� �� ��ҵ� �ٲ� ���� ������ ��
			for (int k = 0; k < size; k++) {
				if (graph1[temp[i][j]][temp[i][k]] == graph2[j][k]) {
					key = 1; // �ֽ� ���°� ���� ���¸� 1
				}
				else {
					key = -1; // �ֽ� ���°� �ٸ� ���¸� -1
					break;
				}
			}
			if (key == -1) { // �ٸ� ���¶�� ���� �ٲ� ������ �Ѿ�� ����
				key = 0;
				break; // key�� 0���� �ʱ�ȭ�ϰ� break�Ͽ� ���� �ٲ� ������ �Ѿ(i++)
			}
		}
		if (key == 1) { // ������ ���� ���¿��ٸ�
			printf("True\n"); // True ��� �� ����
			return 0;
		}
	}

	// ���� ���°� �ƴ� ���·� �ݺ��� Ż�� �� False ��� �� ����
	printf("False\n");
	return 0;
}
*/