#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/*
#define MAX_QUEUE_SIZE 4
typedef struct {
	int key;
}element;

element queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;
void addq(element item);
element deleteq(element item);
int main() { // Data Structures_SWE2015_41 ��μ<student_id>52
	element jj;
	int j;
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		printf("%d\n", queue[i].key);
	}
	for(int i =0; i< 10; i++) {
		printf("���� 1 : add, 2 : delete\n : ");
		scanf("%d", &j);
		if (j == 1) {
			scanf("%d", &jj.key);
			addq(jj);
		}
		else if (j == 2) {
			printf("%d", deleteq());
		}
		printf("front : %d, rear : %d\n", queue[front].key, queue[rear].key);
	}
	return 0;
}


element queue[MAX_QUEUE_SIZE];
int num = 0; // rear�� Ŀ�� ��  full -> 1�� ����, front�� Ŀ�� �� empty -> -1�� ����
int front = 0; rear = 0;
void addq(element item) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear && num == 1) 
		queueFull(rear);
	}
	queue[rear] = item;
}
element deleteq() {
	if (front == rear && num == -1) {
		return queueEmpty();
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}*/