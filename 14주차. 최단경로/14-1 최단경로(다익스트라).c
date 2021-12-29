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

int isEmpty() {
	if (Q.size == 0) {
		return 1;
	}
	else return 0;
}

void makequeue() {
	Q.max = n;
	Q.size = 0;
	Q.key = (int*)malloc(sizeof(int) * n);
	Q.value = (int*)malloc(sizeof(int) * n);
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
	//�ʱ�ȭ
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
void replaceKey(int target, int key) {

	for (int i = 0; i < Q.max; i++) {
		if (Q.value[i] == target) {
			Q.key[i] = key;
		}
	}
}
int find(int target) {

	for (int i = 0; i < Q.max; i++) {
		if (Q.value[i] == target) {
			return 1;
		}
	}

	return 0;
}


void dijkstra(int start) {

	//�׷��� �ʱ�ȭ
	//��� ������ d[v] -> inf, ó�� �������� d[v] -> 0
	for (int i = 1; i <= n; i++) {
		G.vertices[i].d = 100000; // means => d[v] = inf
		G.vertices[i].p = -1;
	}
	G.vertices[start].d = 0;

	//��� ������ ť�� ����
	makequeue();
	for (int i = 1; i <= n; i++) {
		enqueue(G.vertices[i].d, i);
	}

	//�� ������ ������������Ʈ�� ���ؼ� ������ ����

	int u = -1;
	int z;
	int e;

	NODE* edge;
	//Q�� ������������� �ݺ��� ����
	while (!isEmpty()) {
		u = dequeue();// -> extract min from queue
		if (u == -1) break;
		//for each vertex v of adj list
		edge = G.vertices[u].adj_list;

		while (edge->next) {
			z = opposite(edge->next, u);//��� u������ ���� �ݴ��� ���

			e = (edge->next->index);

			//z�� �켱���� ť �ȿ� �����ϰ�
			//z������ �Ÿ����� u���� z�� ���°� �� ª����
			if (find(z) && (G.edges[e].weight + G.vertices[u].d) < G.vertices[z].d) {

				G.vertices[z].p = u;
				G.vertices[z].d = G.edges[e].weight + G.vertices[u].d;
				replaceKey(z, G.vertices[z].d);
			}
			edge = edge->next;
		}
	}
}

void print() {
	for (int i = 1; i <= n; i++) {
		if (G.vertices[i].p != -1) {
			printf("%d %d\n", G.vertices[i].id, G.vertices[i].d);
		}
	}
}
int main() {
	int s;
	scanf("%d %d %d", &n, &m, &s);

	buildGraph();


	dijkstra(s);


	print();
	return 0;
}