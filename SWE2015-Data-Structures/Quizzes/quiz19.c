#include <stdio.h>
#define _CRT_SECURE_NO_WANRINGS

typedef struct listNode* listPointer;
typedef struct listNode{
	char data[4];
	listPointer link;
};

void delete(listPointer* first, listPointer x) { // Data Structures_SWE2015_41 ��μ<student_id>52
	listPointer* tempfirst = first; // ù��° Node�� ����Ű�� �� �ٸ� �����͸� ����
	if ((*first) == x) { // ó���� x��
		(*first) = (*first)->link; 
		// ó���� ���� ù��°�� ����Ű�� ������ �����Ͽ� ������ �ι�°�� ù��°�� �ǵ����Ѵ�.
	}
	else {
		while ((*tempfirst)->link != x) { // ���� ���� ���� ����Ű�� �� x�� �ƴҵ���
			(*tempfirst) = (*tempfirst)->link; // ��ũ�� �� �ܰ辿 �ѱ��.
		}
		// ���� ���� ���� ��ũ�� x�� �Ǿ��� ��
		(*tempfirst)->link = x->link; // �� ��ũ�� x�� ����Ű�� ������ �����Ͽ� x�� ���ش�.
	}
	free(x); // free x
}