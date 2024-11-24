#include <stdio.h>

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
};

void erase(polyPointer* ptr) { // Data Structures_SWE2015_41 ��μ<student_id>52
	polyPointer temp;
	for (; *ptr;) {   // �����, ������ ���� ���ǽĸ� ���ܵθ� while�� ���� ���
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}