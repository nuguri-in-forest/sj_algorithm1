#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int index;
	struct node* next;
}NODE;

typedef struct vertex {
	int id;
	int visited;
	NODE* adj_list;
}VERTEX;

typedef struct edge {
	int id;
	int a;
	int b;
}EDGE;

typedef struct graph {
	VERTEX* vertices;
	EDGE* edges;
}GraphType;

GraphType G;
int n, m, s;

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

	NODE* node = G.vertices[a].adj_list; //인접리스트의 헤드노드는 쓰레기노드로 사용
	NODE* new = get_node(id);

	int z, z2;
	int e;
	int u = -1;

	if (node->next == NULL) {//헤드노드 다음이 비어있으면 첫 수행
		G.vertices[a].adj_list->next = new;
	}
	else {//첫수행말고
		while (node->next != NULL) {
			//여기서 node->next는 현재 순환중인 간선을 의미
			z = opposite(node->next, a);//간선의 종점을 z라하자

			if (z > b) {
				//현재 순환중인 간선 즉 머리의 바로 다음보다 작으면
				//헤드 다음노드로 삽입한다
				new->next = node->next;
				G.vertices[a].adj_list->next = new;
				return;
			}
			else {
				if (node->next->next != NULL) {//뒤에가 더 존재한다면
					z2 = opposite(node->next->next, a);

					if (z2 > b) {

						new->next = node->next->next;
						node->next->next = new;
						return;
					}
				}
			}

			node = node->next;
		}
	}
	node->next = new;
}

void edgeMethod(int id, int a, int b) {

	G.edges[id].a = a;
	G.edges[id].b = b;
	G.edges[id].id = id;
	insertAdj(id, a, b);
	if (a != b) {
		insertAdj(id, b, a);
	}
}

void buildGraph() {
	//정점과 간선의 수를 입력받는다
	scanf("%d %d %d", &n, &m, &s);
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * n + 1);

	G.edges = (EDGE*)malloc(sizeof(EDGE) * m);
	//정점에 번호삽입 및 인접리스트 초기화
	for (int i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].visited = 0;
		G.vertices[i].adj_list = get_node(-1);
	}

	//간선 삽입
	int a, b, w;

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edgeMethod(i, a, b);
	}
}

void DFS(int start) {
	//1. 방문표시 후 정점 아이디 출력
	G.vertices[start].visited = 1;
	printf("%d\n", G.vertices[start].id);

	NODE* node = G.vertices[start].adj_list;

	//2. 인접리스트를 통해 간선들 순회
	int z;
	while (node->next != NULL) {
		z = opposite(node->next, start);
		if (G.vertices[z].visited == 0) {
			DFS(z); //재귀호출
		}
		node = node->next;
	}
}

int main() {

	buildGraph();
	DFS(s);
	return 0;
}
