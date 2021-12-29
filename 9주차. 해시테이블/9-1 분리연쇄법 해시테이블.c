#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int elem;
	struct node* next;
}NODE;

NODE* Table;
int M;
//�и�������� hash 
//h(x) = x % M
int h(int x) {
	return (x % M);
}

void insertItem(int x) {

	int v = h(x); // v�� �ؽ̰�
	NODE* p = Table + v;


	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->elem = x;
	new->next = (Table + v)->next;
	(Table + v)->next = new;
	//����Ʈ ����(���� �տ�)

}



int searchItem(int x) {

	int v = h(x);
	//Ž���� ���������� ������ ���
	//empty status ==> rank 0
	int rank = 0;

	NODE* p = Table + v;

	//empty��� return 0
	if (p->next == NULL) {
		return 0;
	}
	else {
		while (1) {
			p = p->next;
			rank++;
			//Ž���� �����ߴٸ� ���� ��ȯ
			if (p->elem == x) {
				return rank;
			}

			//empty��� return 0
			if (p->next == NULL) {
				return 0;
			}
		}
	}
}



int deleteItem(int x) {

	int v = h(x), rank = 0;

	NODE* p1 = Table + v;
	NODE* p2 = Table + v;

	if (p1->next == NULL) {
		return 0;
	}//empty ���� check

	else {

		while (1) {
			//search
			p1 = p1->next;
			rank++;
			//Ž���� �����Ѵٸ�
			if (p1->elem == x) {
				//p2�� p1 ���� ���� ����
				while (p2->next != p1) {
					p2 = p2->next;
				}
				//����
				p2->next = p1->next;
				//p1 �޸�����
				free(p1);
				//���� ��ȯ
				return rank;

			}
			if (p1->next == NULL) {
				return 0;
			}

		}

	}

}

void printTable() {

	NODE* p;
	//�� �׸��� ��ȸ�ϸ鼭
	//�׸� ���� ����Ʈ�� ���ʴ�� �����
	for (int i = 0; i < M; i++) {
		p = Table + i;

		//�� �׸� ���� ����Ʈ ���
		if (p->next != NULL) {
			p = p->next;
			printf(" %d", p->elem);
			while (p->next != NULL) {
				p = p->next;
				printf(" %d", p->elem);
			}
		}

	}

	printf("\n");

}


//���̺� �޸� ����
void freeTable() {

	NODE* p1, * p2;

	for (int i = 0; i < M; i++) {

		if ((Table + i)->next != NULL) {

			p1 = (Table + i)->next;
			p2 = p1;

			while (p2->next != NULL) {
				p1 = p1->next;
				free(p2);
				p2 = p1;
			}
		}
	}
	free(Table);
}

int main() {
	int key;
	char com;
	scanf("%d", &M);

	//ũ�Ⱑ M�� �迭�� �����Ҵ�
	Table = (NODE*)malloc(sizeof(NODE) * M);

	//���̺� �ʱ�ȭ
	for (int i = 0; i < M; i++) {
		(Table + i)->elem = NULL;
		(Table + i)->next = NULL;
	}

	//��ȭ�� ���α׷� ����
	while (1) {
		scanf("%c", &com);

		if (com == 'i') { // ����
			scanf("%d", &key);
			insertItem(key);
			getchar();
		}

		else if (com == 's') {//Ž��
			scanf("%d", &key);
			printf("%d\n", searchItem(key));
			getchar();
		}

		else if (com == 'd') {//����
			scanf("%d", &key);
			printf("%d\n", deleteItem(key));
			getchar();
		}
		else if (com == 'p') {//���
			printTable();
			getchar();
		}
		else if (com == 'e') { // exit
			break;
		}

	}
	//���̺� �޸� ����
	freeTable();

}