#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	struct node* lChild;
	struct node* parent;
	int key;
	struct node* rChild;
}NODE;
NODE* root;

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

void reduceExternal(NODE* z) {

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

int removeElement(NODE* root, int k) {
	//삭제할 노드를 탐색
	NODE* w = treeSearch(root, k);

	NODE* z, * y;
	int e;

	//삭제할 노드가 없다면 -1 반환
	//means 'NoSuchKey'
	if (isExternal(w)) return -1;

	//case1 : w의 자식 중 적어도 하나가 외부노드 z라면
	//case2 : w의 자식이 둘다 내부노드라면

	e = w->key;
	z = w->lChild; //먼저 왼쪽 자식노드로 설정하고
	//왼쪽 자식노드가 내부노드면, 오른쪽 자식노드를 외부노드 z로 설정
	if (!isExternal(z)) z = w->rChild; // in case1


	if (isExternal(z)) {
		reduceExternal(z);
	}// 왼쪽자식노드 내부노드 + 오른쪽자식노드 외부노드거나
	 // 왼쪽자식노드가 외부노드일때 걸리는 조건문

	else {// 둘다 내부노드일때 in case 2
		//case2에서는 중위순회훈계자 y를 설정하고
		//y의 왼쪽 자식을 z노드로 설정
		y = inOrderSucc(w);
		z = y->lChild;

		//w의 자리에 중위순회후계자를 복사
		// 단순히 key값만 복사하면 됨
		w->key = y->key;

		reduceExternal(z);

	}

	return e;

}

void insertItem(NODE* root, int k) {

	NODE* new_lChild = (NODE*)malloc(sizeof(NODE));

	NODE* new_rChild = (NODE*)malloc(sizeof(NODE));

	NODE* p = treeSearch(root, k);
	if (isInternal(p)) return;
	else {
		//set node w to k,e
		p->key = k;
		p->lChild = new_lChild;
		p->rChild = new_rChild;
		//expandExternal
		new_lChild->parent = p;
		new_rChild->parent = p;
		//leaf의 자식노드 초기화
		new_lChild->lChild = NULL;
		new_lChild->rChild = NULL;

		new_rChild->lChild = NULL;
		new_rChild->rChild = NULL;
	}
}

//전위순회 인쇄
// root -> left -> right 순 
void printTree(struct node* w) {

	if (isExternal(w)) {
		return;
	}

	else {
		printf(" %d", w->key);
		printTree(w->lChild);
		printTree(w->rChild);
	}

}

void freeTree(NODE* w) {

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

	char com = '0';
	//초기화
	root = malloc(sizeof(NODE));
	root->parent = NULL;
	root->lChild = NULL;
	root->rChild = NULL;

	char temp;
	int key;

	while (1) {
		scanf("%c", &com);

		if (com == 'i') {//insert
			scanf("%d", &key);
			insertItem(root, key);
		}
		else if (com == 'd') {//delete
			scanf("%d", &key);
			int res = removeElement(root, key);
			if (res == -1) printf("X\n");
			else printf("%d\n", res);
		}
		else if (com == 's') {//search
			scanf("%d", &key);
			if (treeSearch(root, key)->key != key) printf("X\n");
			else {
				printf("%d\n", treeSearch(root, key)->key);
			}
		}
		else if (com == 'p') {//print
			printTree(root);
			printf("\n");
		}
		else if (com == 'q') break;
		getchar();
	}
	freeTree(root);
}
