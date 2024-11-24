#define _CRT_SECURE_NO_WARNINGS
#define MAX_DEGREE 101
#include <stdio.h>

/* ���׽��� ����( ó�� �������� ���� �� ����� �����Լ����� ���� ���̶�� ����
Ȥ�� �����̵忡 �־��� d ���׽�ó�� ��� �ʱ�ȭ�� ���·� �߰��ϴ� ����̶�� ����*/
typedef struct { // Data Structures_SWE2015_41 ��μ<student_id>52
	int degree;
	float coef[MAX_DEGREE];
} polynomial;
polynomial Remove(polynomial x, int exp) {
	int max = 0; // degree�� �����ϱ� ���� ����
	for (int i = 100; i >= 0; i--) { // �ְ������� ã�� ���� �Ųٷ� ����
		if (x.coef[i] != 0 && max == 0) { // ����� �����鼭 ó�� �����ٸ�(�ְ�����) max = 1�� ����
			max = 1;
		}
		else if (x.coef[i] != 0 && max == 1) { // ����� �����鼭 �ι�°�� ������ ���̶�� ���� degree�� ��.
			max = i; //max�� i�� ������� degree�� �����ų �� �̿�
			break; // �ٸ� ���� ������ �ʵ��� Ż��
		}
	}
	if (x.degree == exp) {
		x.degree = max; // �Ѱܹ��� ����, �� ������ ���� �ְ������̶�� �ְ����� ����
	}
	x.coef[exp] = 0; // �Ѱܹ��� ������ �ش��ϴ� ���� ����� 0���� ����
	return x; // ����� ���׽� ����
}
polynomial Attach(polynomial x, int coef, int exp) {
	x.coef[exp] = x.coef[exp] + coef; /* �Ѱܹ��� ������ �ش��ϴ� �׿� �Ѱܹ��� ����� ����,
	 �־��� d ���׽��� 0���� �ʱ�ȭ �Ǿ����Ƿ� ���� ����� 0, 0 + �Ѱܹ��� ����� ��*/
	if (x.degree < exp) { // ���׽��� �������� �Ѱܹ��� ������ ũ�ٸ� degree�� �ٽ� ����
		x.degree = exp;
	}
	return x; // ����� ���׽� ����
}

int main6() {
	polynomial a, b;
	for (int i = 0; i < 101; i++) {
		a.coef[i] = 0;
		b.coef[i] = 0;
	}
	a.coef[2] = 1;
	a.coef[1] = 2;
	a.coef[0] = 1;
	a.degree = 2;
	b.coef[1] = 2;
	b.coef[0] = 1;
	b.degree = 1;
	for (int i = 100; i >= 0; i--) {
		if (a.coef[i] == 0) {
			continue;
		}
		printf("%fx^%d ", a.coef[i], i);
		if (i == 0) {
			break;
		}
		printf("+ ");
	}
	printf("\n");
	for (int i = 100; i >= 0; i--) {
		if (b.coef[i] == 0) {
			continue;
		}
		printf("%fx^%d ", b.coef[i], i);
		if (i == 0) {
			break;
		}
		printf("+ ");
	}
	a = Attach(a, 3, 7);
	b = Attach(b, 2, 6);
	a = Remove(a, 2);
	b = Remove(b, 1);
	printf("\n");
	for (int i = 100; i >= 0; i--) {
		if (a.coef[i] == 0) {
			continue;
		}
		printf("%fx^%d ", a.coef[i], i);
		if (i == 0) {
			break;
		}
		printf("+ ");
	}
	printf("\n");
	for (int i = 100; i >= 0; i--) {
		if (b.coef[i] == 0) {
			continue;
		}
		printf("%fx^%d ", b.coef[i], i);
		if (i == 0) {
			break;
		}
		printf("+ ");
	}
	return 0;
}