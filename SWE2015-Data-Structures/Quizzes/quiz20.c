/*
#include <stdio.h>
#define MAX_QUEUES 100

typedef struct element {
	int data;
}element;
typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
};
queuePointer front[MAX_QUEUES], rear[MAX_QUEUES];

void addq(int i, element item) { // Data Structures_SWE2015_41 ��μ<student_id>52
	queuePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = NULL; // temp�� ����� �� ����
	queuePointer* tempfirst = front[i]; // ���� ����Ű�� �� �ٸ� ������ ����
	if (front[i]) { // ���� �����Ѵٸ�(������� �ʴٸ�)
		while ((*tempfirst)->link != NULL) {  // ���� ���� ���� link�� NULL�� �ƴҶ� ����
			(*tempfirst) = (*tempfirst)->link; // �� �ܰ辿 �ѱ�
		}
		(*tempfirst)->link = temp; // ������ NULL�̾��� *tempfirst->link�� ���ο� �������� �ǵ��� ����.
	}
	else { // ���� ���ٸ�
		front[i] = temp; // ù��°�� ����
	}
}*/