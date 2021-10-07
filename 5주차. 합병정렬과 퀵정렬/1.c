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

//L을 크기 size와 |L|-size 두개로 분할
PART partition(NODE* L, int size) {
	PART part;
	NODE* L1, * L2;
	NODE* cur = L;
	L1 = L;
	//cur은 이미 첫번째원소를 가리키는 상태
	//따라서 size의 크기를 위해서 size - 1 만큼 리스트 순회
	for (int i = 0; i < size - 1; i++) {
		cur = cur->next;
	}

	//L2는 리스트의 크기에서 size를 뺀것
	L2 = cur->next;
	cur->next = NULL;// cur->next가 NULL이므로, L1의 크기는 size가 됨

	//반환을 위해 구조체에 담아서 반환
	part.L1 = L1;
	part.L2 = L2;

	return part;
}

NODE* merge(NODE* L1, NODE* L2) {
	NODE* res = NULL;
	//2차선 도로의 차들이 1차선으로 합쳐지는 원리

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
		//1번 분할파트
		res = partition(*L, size / 2);
		L1 = res.L1;
		L2 = res.L2;

		//2번 재귀파트
		mergeSort(&L1, size / 2);
		mergeSort(&L2, size - (size / 2));

		//3번 병합파트
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
	//head 노드에는 데이터를 담지 않는다
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