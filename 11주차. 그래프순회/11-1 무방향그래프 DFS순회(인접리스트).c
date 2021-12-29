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
	scanf("%d %d %d", &n, &m, &s);
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

void DFS(int start) {
	//1. �湮ǥ�� �� ���� ���̵� ���
	G.vertices[start].visited = 1;
	printf("%d\n", G.vertices[start].id);

	NODE* node = G.vertices[start].adj_list;

	//2. ��������Ʈ�� ���� ������ ��ȸ
	int z;
	while (node->next != NULL) {
		z = opposite(node->next, start);
		if (G.vertices[z].visited == 0) {
			DFS(z); //���ȣ��
		}
		node = node->next;
	}
}

int main() {

	buildGraph();
	DFS(s);
	return 0;
}
