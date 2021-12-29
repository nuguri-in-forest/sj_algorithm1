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
	scanf("%d %d", &n, &m);
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

void initVisit() {
	//방문기록초기화
	for (int i = 1; i <= n; i++) {
		G.vertices[i].visited = 0;
	}
}
int isCycle(int u, int parent, int start) {
	//u는 현재 정점, parent는 이전 정점

	//1. 방문표시
	G.vertices[u].visited = 1;
	NODE* node = G.vertices[u].adj_list;

	//2. 인접리스트를 통해 간선들 순회
	int z;
	int res = 0;
	while (node->next != NULL) {
		z = opposite(node->next, u);
		if (G.vertices[z].visited == 0) {
			res = isCycle(z, u, start);//재귀호출
			if (res == 1) return 1;
		}
		//노드를 도는데 이미 방문한 노드가 존재한다면 순환
		//이때 노드는 시작노드로 돌아와야하고, 바로 이전노드가 아니어야함
		else if (G.vertices[z].id == start && G.vertices[z].id != parent) {
			return 1;
		}
		node = node->next;
	}
	return 0;
}

int main() {

	buildGraph();
	//각 시작 정점에 대하여 싸이클 탐색
	int res = 0;
	for (int i = 1; i <= n; i++) {
		res = isCycle(i, 1, i);
		if (res == 1) break;
		else {
			initVisit();
		}

	}

	printf("%d", res);
	return 0;
}
