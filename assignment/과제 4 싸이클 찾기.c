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

	NODE* node = G.vertices[a].adj_list; //��������Ʈ�� ������ ��������� ���
	NODE* new = get_node(id);

	int z, z2;
	int e;
	int u = -1;

	if (node->next == NULL) {//����� ������ ��������� ù ����
		G.vertices[a].adj_list->next = new;
	}
	else {//ù���฻��
		while (node->next != NULL) {
			//���⼭ node->next�� ���� ��ȯ���� ������ �ǹ�
			z = opposite(node->next, a);//������ ������ z������

			if (z > b) {
				//���� ��ȯ���� ���� �� �Ӹ��� �ٷ� �������� ������
				//��� �������� �����Ѵ�
				new->next = node->next;
				G.vertices[a].adj_list->next = new;
				return;
			}
			else {
				if (node->next->next != NULL) {//�ڿ��� �� �����Ѵٸ�
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
	//������ ������ ���� �Է¹޴´�
	scanf("%d %d", &n, &m);
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * n + 1);

	G.edges = (EDGE*)malloc(sizeof(EDGE) * m);
	//������ ��ȣ���� �� ��������Ʈ �ʱ�ȭ
	for (int i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].visited = 0;
		G.vertices[i].adj_list = get_node(-1);
	}

	//���� ����
	int a, b, w;

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edgeMethod(i, a, b);
	}
}

void initVisit() {
	//�湮����ʱ�ȭ
	for (int i = 1; i <= n; i++) {
		G.vertices[i].visited = 0;
	}
}
int isCycle(int u, int parent, int start) {
	//u�� ���� ����, parent�� ���� ����

	//1. �湮ǥ��
	G.vertices[u].visited = 1;
	NODE* node = G.vertices[u].adj_list;

	//2. ��������Ʈ�� ���� ������ ��ȸ
	int z;
	int res = 0;
	while (node->next != NULL) {
		z = opposite(node->next, u);
		if (G.vertices[z].visited == 0) {
			res = isCycle(z, u, start);//���ȣ��
			if (res == 1) return 1;
		}
		//��带 ���µ� �̹� �湮�� ��尡 �����Ѵٸ� ��ȯ
		//�̶� ���� ���۳��� ���ƿ;��ϰ�, �ٷ� ������尡 �ƴϾ����
		else if (G.vertices[z].id == start && G.vertices[z].id != parent) {
			return 1;
		}
		node = node->next;
	}
	return 0;
}

int main() {

	buildGraph();
	//�� ���� ������ ���Ͽ� ����Ŭ Ž��
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
