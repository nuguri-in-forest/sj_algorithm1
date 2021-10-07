#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	struct node* next;
	int data;
}NODE;

typedef struct part {
	NODE* L1;
	NODE* L2;
}PART;

NODE* makenode(int data) {
	//make a new_node
	NODE* new = malloc(sizeof(NODE));
	new->data = data;
	new->next = NULL;

	return new;
}

//L�� ũ�� size�� |L|-size �ΰ��� ����
PART partition(NODE* L, int size) {
	PART part;
	NODE* L1, * L2;
	NODE* cur = L;
	L1 = L;
	//cur�� �̹� ù��°���Ҹ� ����Ű�� ����
	//���� size�� ũ�⸦ ���ؼ� size - 1 ��ŭ ����Ʈ ��ȸ
	for (int i = 0; i < size - 1; i++) {
		cur = cur->next;
	}

	//L2�� ����Ʈ�� ũ�⿡�� size�� ����
	L2 = cur->next;
	cur->next = NULL;// cur->next�� NULL�̹Ƿ�, L1�� ũ��� size�� ��

	//��ȯ�� ���� ����ü�� ��Ƽ� ��ȯ
	part.L1 = L1;
	part.L2 = L2;

	return part;
}

NODE* merge(NODE* L1, NODE* L2) {
	NODE* res = NULL;
	//2���� ������ ������ 1�������� �������� ����

	//base case
	if (L1 == NULL) return L2;
	else if (L2 == NULL) return L1;

	//recursive case
	if (L1->data < L2->data) {
		res = L1;
		res->next = merge(L1->next, L2);
	}
	else {
		res = L2;
		res->next = merge(L2->next, L1);
	}
	return res;
}

void mergeSort(NODE** L, int size) {
	NODE* L1 = NULL, * L2 = NULL;
	PART res;

	//base case, size >1
	if (size > 1 && *L != NULL) {
		//1�� ������Ʈ
		res = partition(*L, size / 2);
		L1 = res.L1;
		L2 = res.L2;

		//2�� �����Ʈ
		mergeSort(&L1, size / 2);
		mergeSort(&L2, size - (size / 2));

		//3�� ������Ʈ
		*L = merge(L1, L2);
	}
}

void print(NODE* L) {

	while (L != NULL) {
		printf(" %d", L->data);
		L = L->next;
	}

}

int main() {
	int n, data;
	//head ��忡�� �����͸� ���� �ʴ´�
	NODE* head = (NODE*)malloc(sizeof(NODE));
	head->next = NULL;
	scanf("%d", &n);
	//make list L
	NODE* cur = head;
	for (int i = 0; i < n; i++) {
		scanf("%d", &data);
		cur->next = makenode(data);
		cur = cur->next;
	}


	//recursive merge sort 
	mergeSort(&head->next, n);
	print(head->next);
	// merge L1, L2

}