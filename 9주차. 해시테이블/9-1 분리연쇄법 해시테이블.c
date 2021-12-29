#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int elem;
	struct node* next;
}NODE;

NODE* Table;
int M;
//분리연쇄법의 hash 
//h(x) = x % M
int h(int x) {
	return (x % M);
}

void insertItem(int x) {

	int v = h(x); // v는 해싱값
	NODE* p = Table + v;


	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->elem = x;
	new->next = (Table + v)->next;
	(Table + v)->next = new;
	//리스트 삽입(제일 앞에)

}



int searchItem(int x) {

	int v = h(x);
	//탐색과 삭제에서는 순위를 출력
	//empty status ==> rank 0
	int rank = 0;

	NODE* p = Table + v;

	//empty라면 return 0
	if (p->next == NULL) {
		return 0;
	}
	else {
		while (1) {
			p = p->next;
			rank++;
			//탐색에 성공했다면 순위 반환
			if (p->elem == x) {
				return rank;
			}

			//empty라면 return 0
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
	}//empty 인지 check

	else {

		while (1) {
			//search
			p1 = p1->next;
			rank++;
			//탐색에 성공한다면
			if (p1->elem == x) {
				//p2를 p1 이전 노드로 설정
				while (p2->next != p1) {
					p2 = p2->next;
				}
				//삭제
				p2->next = p1->next;
				//p1 메모리해제
				free(p1);
				//순위 반환
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
	//각 항목을 순회하면서
	//항목에 대한 리스트를 차례대로 출력함
	for (int i = 0; i < M; i++) {
		p = Table + i;

		//각 항목에 대한 리스트 출력
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


//테이블 메모리 해제
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

	//크기가 M인 배열로 동적할당
	Table = (NODE*)malloc(sizeof(NODE) * M);

	//테이블 초기화
	for (int i = 0; i < M; i++) {
		(Table + i)->elem = NULL;
		(Table + i)->next = NULL;
	}

	//대화형 프로그램 설정
	while (1) {
		scanf("%c", &com);

		if (com == 'i') { // 삽입
			scanf("%d", &key);
			insertItem(key);
			getchar();
		}

		else if (com == 's') {//탐색
			scanf("%d", &key);
			printf("%d\n", searchItem(key));
			getchar();
		}

		else if (com == 'd') {//삭제
			scanf("%d", &key);
			printf("%d\n", deleteItem(key));
			getchar();
		}
		else if (com == 'p') {//출력
			printTable();
			getchar();
		}
		else if (com == 'e') { // exit
			break;
		}

	}
	//테이블 메모리 해제
	freeTable();

}