#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	struct node* next;
	int data;
}NODE;

typedef struct part {
	struct NODE* L1;
	struct NODE* L2;
}PART;

NODE* makenode(int data) {
	NODE* new = malloc(sizeof(NODE));
	new->next = NULL;
	new->data = data;
	return new;
}

PART partition(NODE* L, int size) {
	PART res;
	NODE* L1 = L, * L2;

	//L1 , L2 �и�
	NODE* cur = L;

	//�̹� ũ��� 1�̹Ƿ�, size-1��ŭ �̵��ؾ���
	for (int i = 0; i < size - 1; i++) {
		cur = cur->next;
	}

	//���⼭ cur�� size �� ũ��
	L2 = cur->next; //L2�� cur->next, �� |L2| = |L|-size
	cur->next = NULL;// L1�� ũ��� size

	//��ȯ
	res.L1 = L1;
	res.L2 = L2;
	return res;
}
NODE* merge(NODE* L1, NODE* L2) {
	NODE* res = NULL;

	//base case
	//L1�̳� L2�� null�϶�
	if (L1 == NULL) return L2;
	else if (L2 == NULL) return L1;
	//recursive case

	if (L1->data < L2->data) {
		res = L1;
		res->next = merge(L1->next, L2);
	}
	else {
		res = L2;
		res->next = merge(L1, L2->next);
	}
	return res;
}
void mergeSort(NODE** L, int size) {
	PART res; //���ҵ� �� ����Ʈ�� ���޹ޱ�����
	NODE* L1 = NULL, * L2 = NULL;

	//base case ����
	if (size > 1 && *L != NULL) {
		//����
		res = partition(*L, size / 2);
		L1 = res.L1;
		L2 = res.L2;

		//��� 
		mergeSort(&L1, size / 2);
		mergeSort(&L2, size - (size / 2));

		//�պ�
		*L = merge(L1, L2);
	}
}

void print(NODE* L) {
	NODE* cur = L;
	while (cur != NULL) {
		printf(" %d", cur->data);
		cur = cur->next;
	}

}
int main() {
	int n;
	//head���� �����͸� ���� �ʴ´�
	NODE* head = malloc(sizeof(NODE));
	head->next = NULL;

	scanf("%d", &n);

	//���Ḯ��Ʈ ����
	int data;
	NODE* cur = head;
	for (int i = 0; i < n; i++) {
		scanf("%d", &data);
		cur->next = makenode(data);
		cur = cur->next;
	}

	mergeSort(&head->next, n);
	print(head->next);
	free(head);
}