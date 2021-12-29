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
	NODE* out_list;
	NODE* in_list;
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


void insertAdj(NODE* head, int id) {
	NODE* new = get_node(id);

	while (head->next) {
		head = head->next;
	}
	head->next = new;
}

void edgeMethod(int id, int a, int b, int w) {

	G.edges[id].a = a;
	G.edges[id].b = b;
	G.edges[id].weight = w;
	//간선방향 a->b 에 대해 진입,진출 인접리스트 설정
	insertAdj(G.vertices[a].out_list, id);
	insertAdj(G.vertices[b].in_list, id);
}

void buildGraph() {

	G.edges = (EDGE*)malloc(sizeof(EDGE) * m);
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * n + 1);

	for (int i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].out_list = get_node(-1);
		G.vertices[i].in_list = get_node(-1);
	}

	int a, b, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		edgeMethod(i, a, b, w);
	}
}

void BellmanFord(int start) {

	//그래프 초기화
	//모든 정점의 d[v] -> inf, 처음 시작정점 d[v] -> 0
	for (int i = 1; i <= n; i++) {
		G.vertices[i].d = 100000; // means => d[v] = inf
		G.vertices[i].p = -1;
	}
	G.vertices[start].d = 0;


	int u = -1;
	int z; //opposite
	int e; // 현재 간선의 인덱스번호
	int weight = 0;
	NODE* edge;
	//밸만포드 알고리즘은 모든 간선에 대해서 relax 수행


	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			u = G.edges[j].a; //src
			z = G.edges[j].b; //dest;
			weight = G.edges[j].weight;// w(u,z)

			//if d[u] + w(u,z) < d[z], d[z] = d[u]+ w(u,z)
			if (G.vertices[u].d != 100000 && (G.vertices[u].d + weight) < G.vertices[z].d) {
				G.vertices[z].p = u;
				G.vertices[z].d = G.vertices[u].d + weight;
			}

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


	BellmanFord(s);


	print();
	return 0;
}