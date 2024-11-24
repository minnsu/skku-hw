#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int** make2dArray(int row) {
	int** x;
	int cols;
	x = (int**)malloc(sizeof(int*)*row);
	for (int i = 0; i < row; i++) {
		printf("x[%d]�� ������ ĭ ��? : ", i);
		scanf("%d", &cols); // ���� ���� �Է�
		x[i] = (int*)malloc(sizeof(int)*cols);
		for (int j = 0; j < cols; j++) {
			x[i][j] = i * 10 + j; // ���� ���� Ȯ���ϱ� ���� "��*10 + ��"�� ��������.
			printf("%d ", x[i][j]);
		}
		printf("\n");
	}
	return x;
}
int main4() { // Data Structures_SWE2015_41 ��μ� <student_id>
	int** array;
	int row;
	printf("������ �迭�� �� �� : ");
	scanf("%d", &row); // �� ���� �Է� �ް� �Ͽ���.
	array = make2dArray(row);
	return 0;
}
