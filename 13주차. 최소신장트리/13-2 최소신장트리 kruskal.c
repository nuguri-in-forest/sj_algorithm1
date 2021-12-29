#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int index;
	struct node* next;
}NODE;

typedef struct vertex {
	int id;
	int d;
	int p;
	NODE* adj_list;
}VERTEX;

typedef struct edge {
	int id;
	int a;
	int b;
	int weight;
}EDGE;

typedef struct graph {
	VERTEX* vertices;
	EDGE* edges;
}GraphType;

typedef struct queue {
	int max;
	int size;
	int* key;
	int* value;

}QUEUE;

typedef struct set {
	int size;
	int k;
	int* data;
}SET;

QUEUE Q;
GraphType G;
int n, m;

NODE* get_node(int i) {

	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->index = i;
	new->next = NULL;

	return new;
}

int opposite(NODE* e, int a) {

	EDGE edge = G.edges[e->index];
	if (edge.a == a) {
		return edge.b;
	}
	else {
		return edge.a;
	}

}


void insertAdj(int id, int a, int b) {

	NODE* head = G.vertices[a].adj_list;
	NODE* new;

	while (head->next) {
		head = head->next;
	}
	new = get_node(id);
	head->next = new;
}

void edgeMethod(int id, int a, int b, int w) {

	G.edges[id].a = a;
	G.edges[id].b = b;
	G.edges[id].weight = w;
	insertAdj(id, a, b);
	if (a != b)
		insertAdj(id, b, a);
}

void buildGraph() {

	scanf("%d %d", &n, &m);
	G.edges = (EDGE*)malloc(sizeof(EDGE) * m);
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * n + 1);

	for (int i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].adj_list = get_node(-1);
	}

	int a, b, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		edgeMethod(i, a, b, w);
	}
}

SET* getSet(int range, int k) {
	SET* new = malloc(sizeof(SET));
	//초기화
	new->size = range + 1;
	new->k = k;
	new->data = malloc(sizeof(int) * (range + 1));
	for (int i = 0; i < new->size; i++) {
		new->data[i] = -1;
	}
	return new;
}

int whereSet(SET* S, int e) {
	return S->data[e];
}

void Union(SET* S, int a, int b) {
	S->k--;
	for (int i = 0; i < S->size; i++) {
		//a로 통합
		if (S->data[i] == b) {
			S->data[i] = a;
		}
	}
}

void makequeue(int size) {
	Q.max = size;
	Q.size = 0;
	Q.key = malloc(sizeof(int) * size);
	Q.value = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		Q.key[i] = -1;
		Q.value[i] = -1;
	}
}
void enqueue(int key, int val) {
	int size = Q.size;
	Q.key[size] = key;
	Q.value[size] = val;
	Q.size++;
}
int dequeue() {

	int minkey, minval;
	int minidx = 0;
	//초기화
	minkey = Q.key[0];
	minval = Q.value[0];
	minidx = 0;

	for (int i = 1; i < Q.max; i++) {
		if (Q.key[i] < minkey) {
			minkey = Q.key[i];
			minval = Q.value[i];
			minidx = i;
		}
	}
	Q.key[minidx] = 100000;
	Q.value[minidx] = -1;
	Q.size--;
	return minval;
}


void KruskalMST() {

	//큐 생성 및 초기화
	makequeue(m);
	for (int i = 0; i < m; i++) {
		enqueue(G.edges[i].weight, i);
	}

	//집합 생성 및 data 초기화
	SET* S;
	S = getSet(n, n);
	for (int i = 1; i <= n; i++) {
		S->data[i] = i;
	}

	int idx;
	int a, b;
	int res = 0;
	while (Q.size != 0) {
		idx = dequeue();
		a = G.edges[idx].a;
		b = G.edges[idx].b;
		if (whereSet(S, a) != whereSet(S, b)) {
			// MST에 간선추가
			// 가중치 합 더하기
			res = res + G.edges[idx].weight;
			printf(" %d", G.edges[idx].weight);
			Union(S, whereSet(S, a), whereSet(S, b));
		}
	}
	printf("\n%d", res);
}

int main() {

	buildGraph();
	KruskalMST();
	return 0;
}