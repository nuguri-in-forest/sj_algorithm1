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
	}// sibling�� ������������


	if (w->parent->lChild == w) {
		return w->parent->rChild;
	}
	else {
		return w->parent->lChild;
	}
}

//������ȸ�İ��� y �� ã�� �Լ�
NODE* inOrderSucc(NODE* w) {
	/*
	������ȸ�İ��� yã��
	1. w�� ������ �ڽ����� ���� �̵��Ѵ�.
	2. �ű⼭���� ���� �ڽĵ鸸�� ������ ���󳻷�����
	3. �׶��� ������ ���γ�尡 y�̰� z�� y�� �����ڽ��� �ܺγ��
	*/

	w = w->rChild; // 1������

	if (isExternal(w)) {
		return;
	}//invalidNodeException

	//2������
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}

	//3������
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
		//w�� �θ��带 g�� ����.
		g = w->parent;
		zs->parent = g;

		//g�� �ڽĳ�带 ������ w ���
		//zs ���� ����
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
	//leaf �� ���� �ߴٸ�, Ű k�� �߰ߵ��� ���� ���̹Ƿ�
	//���Ե� �ڸ��� �ش�Ǵ� �� �ܺγ�� w�� ��ȯ
	if (isExternal(w)) {
		return w;
	}

	//Ž�� ���� case
	if (w->key == k) {
		return w;
	}

	//������ȸ�� a<b<c
	//ã�����ϴ� Ű k�� �� �۴ٸ�, �������� ���� Ž��
	else if (w->key > k) {
		return treeSearch(w->lChild, k);
	}

	//ã�����ϴ� Ű k�� �� ũ�ٸ�, ���������� ���� Ž��
	else {//means w->key < k
		return treeSearch(w->rChild, k);
	}
}

int removeElement(NODE* root, int k) {
	//������ ��带 Ž��
	NODE* w = treeSearch(root, k);

	NODE* z, * y;
	int e;

	//������ ��尡 ���ٸ� -1 ��ȯ
	//means 'NoSuchKey'
	if (isExternal(w)) return -1;

	//case1 : w�� �ڽ� �� ��� �ϳ��� �ܺγ�� z���
	//case2 : w�� �ڽ��� �Ѵ� ���γ����

	e = w->key;
	z = w->lChild; //���� ���� �ڽĳ��� �����ϰ�
	//���� �ڽĳ�尡 ���γ���, ������ �ڽĳ�带 �ܺγ�� z�� ����
	if (!isExternal(z)) z = w->rChild; // in case1


	if (isExternal(z)) {
		reduceExternal(z);
	}// �����ڽĳ�� ���γ�� + �������ڽĳ�� �ܺγ��ų�
	 // �����ڽĳ�尡 �ܺγ���϶� �ɸ��� ���ǹ�

	else {// �Ѵ� ���γ���϶� in case 2
		//case2������ ������ȸ�ư��� y�� �����ϰ�
		//y�� ���� �ڽ��� z���� ����
		y = inOrderSucc(w);
		z = y->lChild;

		//w�� �ڸ��� ������ȸ�İ��ڸ� ����
		// �ܼ��� key���� �����ϸ� ��
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
		//leaf�� �ڽĳ�� �ʱ�ȭ
		new_lChild->lChild = NULL;
		new_lChild->rChild = NULL;

		new_rChild->lChild = NULL;
		new_rChild->rChild = NULL;
	}
}

//������ȸ �μ�
// root -> left -> right �� 
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
	//�ʱ�ȭ
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
