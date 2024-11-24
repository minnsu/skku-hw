//************ ���� ���� ����
/*#include <stdio.h>
#include <stdlib.h>

typedef struct Node {  // Data Structures_SWE2015_41 ��μ<student_id>52
	int coef;
	int exp;
	struct Node* before;
	struct Node* next; // ���� ���, ���� ��� ����Ű�� ������
}Node;

void init(Node* p) { // �ʱ�ȭ �Լ�
	p->before = NULL;
	p->next = NULL;
	p->coef = 0;
	p->exp = -1;
}

struct Node* a, * b, * q; // a(���߿� �������� �� ��), b(������ ���׽�), q(��, �����鼭 �߰��ϴ� ��)
struct Node* ah, * at, * bh, * bt, * qh, * qt; // a�� head, tail, b�� head, tail, q�� head, tail

void add(Node* bef, int coef, int exp) {
	Node* new = (Node*)malloc(sizeof(Node)); init(new); // ���ο� ���
	new->coef = coef;
	new->exp = exp;
	if (bef->next == NULL) { // �̾ ��尡 ������ �����
		new->before = bef;
		bef->next = new;
		new->next = NULL; // next�� NULL
	}
	else { // �߰��� �����ִ� ���̶��
		new->before = bef;
		new->next = bef->next;

		bef->next->before = new; // bef�� ���� ����� ���� ��带 ���ο� ���� ����
		bef->next = new; // bef�� ���� ��带 ���ο� ���� ����
	}
} // add�� �̾ �ѹ� �Ѱܾ���

Node* find(Node* head, int exp) { // exp�� �ش��ϴ� ��� ��ȯ
	if (head->next == NULL) { // ���ۿ� ���ٸ�
		Node* temph = head;
		add(temph, 0, exp);
		temph = temph->next;
		return temph; // ���� ���� ��ȯ, ���� ��� + ���ο� ����
	}

	Node* temph = head->next; // temph�� ����� ���� ���(������ ���� ù ���)
	while (temph->next != NULL && temph->exp > exp) { // ���� ���� NULL�� �ƴϸ鼭 �־��� exp���� ū ���� �Ѿ��
		temph = temph->next;
	}

	if (temph->exp == exp) { // ������ ����
		return temph;
	}
	else {
		if (temph->next == NULL && temph->exp > exp) { // ���� ���� NULL�̸鼭 ������ ��尡 exp���� ũ��
			add(temph, 0, exp);
			temph = temph->next;
			return temph; // ���� ���� ����
		}
		else if (temph->exp < exp) { // �߰��� ���� ���̶�� temph->exp < exp
			temph = temph->before; // �ϳ� �������� ���ư���
			add(temph, 0, exp); // ���� ��忡 ���̰�
			temph = temph->next; // ���� ���� �ű��
			return temph; // ����
		}
	}
}

void minus(Node* ah, Node* bh, Node* qt, int coef, int exp) {
	Node* tempa;
	Node* tempb = bh->next; // ������ ���� ù ���� ����
	while (tempb != NULL) {
		tempa = find(ah, tempb->exp + exp); // target exp ��带 �޾ƿ���
		tempa->coef = tempa->coef - coef * tempb->coef; // �޾ƿ� ����� coef ���� ����
		if (tempa->coef == 0) { // ����� coef�� 0�̸� �����ؾ���.
			if (tempa->next == NULL) { // 0���� ����� ��尡 �������̶��
				tempa->before->next = NULL; // ���� ����� ������ NULL�� ����
				free(tempa); // free
			}
			else { // �߰� node�� �����Ǿ�� �Ѵٸ�
				tempa->before->next = tempa->next; // ���� ����� ���� �����͸� temph�� ���� ���� ����
				tempa->next->before = tempa->before; // ���� ����� ���� �����͸� temph�� ���� ���� ����
				free(tempa); // free
			}
		}
		tempb = tempb->next; // ������ ���� ���� ������ �Ѿ��
	}
}

int main() {
	a = (Node*)malloc(sizeof(struct Node)); init(a); ah = at = a;
	b = (Node*)malloc(sizeof(struct Node)); init(b); bh = bt = b;
	q = (Node*)malloc(sizeof(struct Node)); init(q); qh = qt = q;
	// a, b, q �ʱ�ȭ �� head, tail ����
	int sizea, sizeb;
	int num_coef, num_exp;

	scanf("%d", &sizea);
	for (int i = 0; i < sizea; i++) {    // acoef, aexp�� ah->next->coef, ah->next->exp�� �ذ�
		scanf("%d", &num_coef);
		scanf("%d", &num_exp);
		add(at, num_coef, num_exp);
		at = at->next;
	}

	scanf("%d", &sizeb);
	for (int i = 0; i < sizeb; i++) {    // bcoef, bexp�� bh->next->coef, bh->next->exp�� �ذ�
		scanf("%d", &num_coef);
		scanf("%d", &num_exp);
		add(bt, num_coef, num_exp);
		bt = bt->next;
	}
	// a, b ��� �ӽ� ������ �ӷ¹ް� add, �� ��� tail�� ���̴� ���

	while (ah->next != NULL && bh->next->exp <= ah->next->exp) {
		// ����� ���� ���(������ ���� ù ���)�� NULL�� �ƴϸ鼭 ������ ���� �������� a ���� ������ ũ�ų� ���� ���� �ݺ�
		add(qt, ah->next->coef / bh->next->coef, ah->next->exp - bh->next->exp);
		qt = qt->next; // �� Node�� �߰�
		minus(ah, bh, qt, ah->next->coef / bh->next->coef, ah->next->exp - bh->next->exp);
		// coef = ah�� ù ����� ��� / ������ ���� ù ����� ���, exp = ah�� ù ����� ���� / ������ ���� ù ����� ����
	} // ahead�� �ű�鼭 �ְ����� ã�¹��?

	// ���

	// ��
	if (qh->next == NULL) {
		printf("%d %d\n", 0, 0); // NULL�̸� 0 0 ���
	}
	else { // ������ ���� ��尡 �����Ѵٸ�
		qh = qh->next; // ������ ���� ù ���� �̵�
		while (qh != NULL) {
			printf("%d %d\n", qh->coef, qh->exp);
			qh = qh->next; // ��� �� �̵�
		}
	}
	// ������
	if (ah->next == NULL) {
		printf("%d %d\n", 0, 0); // NULL�̸� 0 0 ���
	}
	else { // ������ ���� ��尡 �����Ѵٸ�
		ah = ah->next; // ������ ���� ù ���� �̵�
		while (ah != NULL) {
			printf("%d %d\n", ah->coef, ah->exp);
			ah = ah->next; // ��� �� �̵�
		}
	}
	return 0;
}*/