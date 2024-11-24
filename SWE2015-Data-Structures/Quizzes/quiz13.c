#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
#define MAX_STACK_SIZE 100
typedef struct{
	int key;
} element;
element stack[MAX_STACK_SIZE];
element newstack[MAX_STACK_SIZE];
int top1 = 1;
int top2 = 1;
void push1(element item);
void push2(element item);
element pop1();
element pop2();
int main13() { // Data Structures_SWE2015_41 ��μ<student_id>52
	srand(time(NULL));
	element a;
	for (int i = 0; i < 10; i++) {
		a.key = rand() % 100 + 1;
		printf("%d��° �� ���� : %d\n", i+1, a.key);
		push1(a);
	}
	for (int i = 0; i < 10; i++) {
		push2(pop1());
	}
	for (int i = 0; i < 10; i++) {
		printf("newstack %d��° ��� : %d\n", i+1,pop2().key);
	}
	return 0;
}

void push1(element item)
{
	if (top1 >= MAX_STACK_SIZE - 1) {
		//stackFull();
		return;
	}
	stack[++top1] = item;
}

void push2(element item)
{
	if (top2 >= MAX_STACK_SIZE - 1) {
		//stackFull();
		return;
	}
	newstack[++top2] = item;
}

element pop1(){
	if (top1 == 1) {
		return;
	}
	return stack[top1--];
}

element pop2() {
	if (top2 == 1) {
		return;
	}
	return newstack[top2--];
}

void stackFull(){
	fprintf(stderr , "Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}*/