#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct node {

	int key;
	int height;

	struct node* lChild;
	struct node* rChild;
	struct node* parent;
}NODE;

struct node* root;

int isExternal(NODE* w) {
	if (w->lChild == NULL && w->rChild == NULL) return 1;//true
	else return 0; //false
}
int isInternal(NODE* w) {
	if (w->lChild != NULL || w->rChild != NULL) return 1;//true
	else return 0; //false
}

NODE* sibling(NODE* w) {

	if (w->parent == NULL) {
		return;
	}// sibling이 존재하지않음


	if (w->parent->lChild == w) {
		return w->parent->rChild;
	}
	else {
		return w->parent->lChild;
	}
}

//중위순회후계자 y 를 찾는 함수
NODE* inOrderSucc(NODE* w) {
	/*
	중위순회후계자 y찾기
	1. w의 오른쪽 자식으로 먼저 이동한다.
	2. 거기서부터 왼쪽 자식들만을 끝까지 따라내려간다
	3. 그때의 마지막 내부노드가 y이고 z는 y의 왼쪽자식인 외부노드
	*/

	w = w->rChild; // 1번과정

	if (isExternal(w)) {
		return;
	}//invalidNodeException

	//2번과정
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}

	//3번과정
	return w; // ==> return y
}

NODE* reduceExternal(NODE* z) {

	NODE* w, * zs, * g;

	w = z->parent;
	zs = sibling(z);

	if (w->parent == NULL) {//isRoot?
		root = zs;
		zs->parent = NULL;

	}

	else {
		//w의 부모노드를 g라 하자.
		g = w->parent;
		zs->parent = g;

		//g의 자식노드를 삭제된 w 대신
		//zs 노드로 설정
		if (w == g->lChild) {
			g->lChild = zs;
		}
		else if (w == g->rChild) {
			g->rChild = zs;
		}
	}

	free(z);
	free(w);
	return zs;
}


void expandExternal(NODE* w) {

	NODE* new_lChild = (NODE*)malloc(sizeof(NODE));
	NODE* new_rChild = (NODE*)malloc(sizeof(NODE));

	//expandExternal
	//leaf의 자식노드 초기화
	new_lChild->lChild = NULL;
	new_lChild->rChild = NULL;
	new_lChild->height = 0;
	new_lChild->parent = w;

	new_rChild->lChild = NULL;
	new_rChild->rChild = NULL;
	new_rChild->height = 0;
	new_rChild->parent = w;

	w->lChild = new_lChild;
	w->rChild = new_rChild;
	w->height = 1;

	return;

}

NODE* treeSearch(NODE* w, int k) {

	//base case
	//leaf 에 도달 했다면, 키 k가 발견되지 않은 것이므로
	//삽입될 자리에 해당되는 그 외부노드 w를 반환
	if (isExternal(w)) {
		return w;
	}

	//탐색 성공 case
	if (w->key == k) {
		return w;
	}

	//중위순회는 a<b<c
	//찾고자하는 키 k가 더 작다면, 왼쪽으로 가서 탐색
	else if (w->key > k) {
		return treeSearch(w->lChild, k);
	}

	//찾고자하는 키 k가 더 크다면, 오른쪽으로 가서 탐색
	else {//means w->key < k
		return treeSearch(w->rChild, k);
	}
}



int updateHeight(NODE* w) {

	//부모노드의 높이는 자식노드의 높이중 더 큰 높이 + 1
	int height;
	if (w->lChild->height > w->rChild->height) {
		height = w->lChild->height + 1;
	}
	else {
		height = w->rChild->height + 1;
	}

	//변경여부 반환
	if (height != w->height) {
		w->height = height;
		return 1;

	}
	else {
		return 0;
	}
}



int isBalanced(NODE* w) {

	if ((-1 <= (w->lChild->height - w->rChild->height)) && ((w->lChild->height - w->rChild->height) <= 1)) {

		return 1;

	}

	else {

		return 0;

	}

}

NODE* restructure(NODE* x, NODE* y, NODE* z) {

	NODE* a, * b, * c;
	NODE* T0, * T1, * T2, * T3;

	if ((z->key < y->key) && (y->key < x->key)) {

		a = z;

		b = y;

		c = x;

		T0 = a->lChild;

		T1 = b->lChild;

		T2 = c->lChild;

		T3 = c->rChild;

	}

	else if ((x->key < y->key) && (y->key < z->key)) {

		a = x;

		b = y;

		c = z;

		T0 = a->lChild;

		T1 = a->rChild;

		T2 = b->rChild;

		T3 = c->rChild;

	}

	else if ((z->key < x->key) && (x->key < y->key)) {

		a = z;

		b = x;

		c = y;

		T0 = a->lChild;

		T1 = b->lChild;

		T2 = b->rChild;

		T3 = c->rChild;

	}

	else {

		a = y;

		b = x;

		c = z;

		T0 = a->lChild;

		T1 = b->lChild;

		T2 = b->rChild;

		T3 = c->rChild;

	}



	if (z->parent == NULL) {

		root = b;

		b->parent = NULL;

	}

	else if (z->parent->lChild == z) {

		z->parent->lChild = b;

		b->parent = z->parent;

	}

	else if (z->parent->rChild == z) {

		z->parent->rChild = b;

		b->parent = z->parent;

	}

	a->lChild = T0;
	T0->parent = a;
	a->rChild = T1;
	T1->parent = a;
	updateHeight(a);

	c->lChild = T2;
	T2->parent = c;
	c->rChild = T3;
	T3->parent = c;
	updateHeight(c);

	b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;
	updateHeight(b);

	return b;
}


void searchAndFixAfterInsertion(NODE* w) {

	NODE* x, * y, * z;

	w->lChild->height = 0;

	w->rChild->height = 0;

	w->height = 1;

	if (w->parent == NULL) {

		return NULL;

	}

	z = w->parent;

	while (updateHeight(z) && isBalanced(z)) {

		if (z->parent == NULL) {

			return;

		}

		z = z->parent;

	}

	if (isBalanced(z)) {

		return;

	}

	if (z->lChild->height > z->rChild->height) {

		y = z->lChild;

	}

	else {

		y = z->rChild;

	}

	if (y->lChild->height > y->rChild->height) {

		x = y->lChild;

	}

	else {

		x = y->rChild;

	}

	restructure(x, y, z);

	return;

}



void insertItem(NODE* w, int k) {

	NODE* p = treeSearch(w, k);

	if (isInternal(p)) {
		return;
	}

	else {
		p->key = k;
		expandExternal(p);
		searchAndFixAfterInsertion(p);
	}

}



void searchAndFixAfterRemoval(NODE* w) {

	NODE* x = NULL, * y, * z, * b;

	if (w == NULL) {
		return;
	}

	z = w;
	while (updateHeight(z) && isBalanced(z)) {

		if (z->parent == NULL) {
			return;
		}

		z = z->parent;

	}

	if (isBalanced(z)) {

		return;

	}

	if (z->lChild->height > z->rChild->height) {

		y = z->lChild;

	}

	else {

		y = z->rChild;

	}

	if (y->lChild->height > y->rChild->height) {

		x = y->lChild;

	}

	else if (y->lChild->height < y->rChild->height) {

		x = y->rChild;

	}

	else {

		if (z->lChild == y) {

			x = y->lChild;

		}

		else if (z->rChild == y) {

			x = y->rChild;

		}

	}

	b = restructure(x, y, z);

	searchAndFixAfterRemoval(b->parent);

}



int removeElement(NODE* w, int k) {

	NODE* p = treeSearch(w, k);

	NODE* z, * zs, * y;

	int e;

	if (isExternal(p)) {

		return -1;

	}

	e = p->key;

	z = p->lChild;

	if (!isExternal(z)) {

		z = p->rChild;

	}

	if (isExternal(z)) {

		zs = reduceExternal(z);

	}

	else {

		y = inOrderSucc(p);

		z = y->lChild;

		p->key = y->key;

		zs = reduceExternal(z);

	}

	searchAndFixAfterRemoval(zs->parent);

	return e;

}



void printTree(NODE* w) {

	if (isExternal(w)) {

		return;

	}

	else {

		printf(" %d", w->key);

		printTree(w->lChild);

		printTree(w->rChild);

	}

}



void freeTree(struct node* w) {

	if (isExternal(w)) {

		return;

	}

	else {

		freeTree(w->lChild);

		freeTree(w->rChild);

		free(w);

	}

}

int main() {

	char com;
	int key, res;
	//root 초기화
	root = (NODE*)malloc(sizeof(NODE));
	root->parent = NULL;
	root->lChild = NULL;
	root->rChild = NULL;

	while (1) {

		scanf("%c", &com);

		if (com == 'i') {
			scanf("%d", &key);
			insertItem(root, key);
			getchar();
		}

		else if (com == 'd') {

			scanf("%d", &key);

			res = removeElement(root, key);

			if (res == key) {
				printf("%d\n", res);
			}
			else {
				printf("X\n");
			}
			getchar();
		}

		else if (com == 's') {

			scanf("%d", &key);

			if (treeSearch(root, key)->key != key) {
				printf("X\n");
			}

			else {

				printf("%d\n", treeSearch(root, key)->key);
			}
			getchar();
		}

		else if (com == 'p') {

			printTree(root);

			printf("\n");

		}

		else if (com == 'q') {

			break;

		}
	}

	freeTree(root);

}

