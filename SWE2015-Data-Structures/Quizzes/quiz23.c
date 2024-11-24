/*#include <stdio.h>
typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
};
listPointer invert(listPointer lead) {
	listPointer middle, trail;
	middle = NULL;
	while (lead) {
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	return middle;
}

void add(listPointer c, int data) {
	c->data = data;
	listPointer new;
	new->link = NULL;
	c->link = new;
}
listPointer invertedCopyList(listPointer ptr) { // Data Structures_SWE2015_41 ��μ<student_id>52
	listPointer new = ptr; // ���� ���� ����Ű�� �ٸ� �̸����� �Ѿ�� ����, ptr�� �ջ��� ���ϱ� ����
	listPointer realnew1; // �����ϰ� invert��ų listPointer
	for (new->link != NULL) {
		add(realnew1, new->data); // ���� realnew1�� new->data ���� �� ���� ���� ����
		realnew1 = realnew1->link; // ���� ����� �ѱ��(add���� ���� ����� link)
		new = new->link; // ���� ����� �ѱ��(ptr���� �����ϴ� list, ptr�� �ջ� ���� �Ѿ)
	} // copy

	listPointer realnew2 = invert(realnew1); // invert
	return realnew2;
}

int main() {


	return 0;
}*/