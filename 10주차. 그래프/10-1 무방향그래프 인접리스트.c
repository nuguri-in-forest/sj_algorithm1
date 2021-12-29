#pragma warning(disable:4996)
#include <stdio.h>
#include<stdlib.h>

//�ڷᱸ������
typedef struct node {
	int index;
	struct node* next;
}NODE;

typedef struct vertex {
	NODE* adj_list;
	int id;
}VERTEX;

typedef struct edge {
	int weight;
	int a;
	int b;
	int id;
}EDGE;

typedef struct graph {
	VERTEX* vertices;
	EDGE* edges;
}Graphtype;

Graphtype G;
int m;//������ ����

//����ȯ
NODE* get_node(int i) {
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->index = i;
	new->next = NULL;
	return new;
}

//������ �ݴ����� ��ȯ
int opposite(NODE* node, int a) {
	EDGE edge = G.edges[node->index];
	if (edge.a == a) {
		return edge.b;
	}
	else {
		return edge.a;
	}
}

void insertAdj(int id, int a, int b) {
	NODE* node = G.vertices[a].adj_list;//������ ���������� ���
	NODE* new = get_node(id);//�ε��� id�� ����

	int z1, z2;
	if (node->next == NULL) {
		G.vertices[a].adj_list->next = new;
	}
	else {
		while (node->next != NULL) {
			//2��° ������ ���� z1����
			z1 = opposite(node->next, a);
			if (z1 > b) {
				new->next = node->next;
				G.vertices[a].adj_list->next = new;
				return;
			}
			//3��°���� ������ ������ ����z2���� 
			else if (node->next->next != NULL) {
				z2 = opposite(node->next->next, a);
				if (z2 > b) {
					new->next = node->next->next;
					node->next->next = new;
					return;
				}
			}

			node = node->next;
		}

	}
	node->next = new;
}
void edgeMethod(int id, int a, int b, int w) {
	G.edges[id].id = id;
	G.edges[id].a = a;
	G.edges[id].b = b;
	G.edges[id].weight = w;

	insertAdj(id, a, b);
	if (a != b) {
		insertAdj(id, b, a);
	}
}
void removeEdge(int a, int b, int target) {
	//prev�� ���⶧���� ���ΰ��� ���� ������
	NODE* node1 = G.vertices[a].adj_list->next;
	NODE* node2 = G.vertices[a].adj_list->next->next;

	while (node1 != NULL) {
		//������ ���������
		//�״������ �״ϱ� ù���Ұ� �����ɶ���
		//������� �������(ù����)�� ���� �������־����
		if (G.vertices[a].adj_list->next->index == target) {
			free(G.vertices[a].adj_list->next);
			G.vertices[a].adj_list->next = node2;
			return;
		}
		//�� node2�� ������ ����Ʈ�� ��ȸ�ϴ� ����
		else if (node2->index == target) {
			node1->next = node2->next;
			free(node2);
			return;
		}
		node1 = node1->next;
		node2 = node2->next;
	}
}
void removeMethod(int a, int b, int target) {
	//���� �������� ����
	//���⼭ target�� ������ id�� ����
	G.edges[target].id = -1;
	removeEdge(a, b, target);
	if (a != b) {
		removeEdge(b, a, target);
	}
}
void modifyMethod(int a, int b, int w) {
	//1.���� a,b�� ���縦 Ȯ���Ѵ�
	if (a <= 0 || a > 6) {
		printf("-1\n");
		return;
	}
	if (b <= 0 || b > 6) {
		printf("-1\n");
		return;
	}
	//2. ������ ��ȸ�ϸ鼭 Ÿ�ٰ��� (a,b)�� �ε����� ã�´�
	//�̶� a<b�̹Ƿ� a,b�� �������� target_a, ū ���� target_b
	int target_index = -1, target_a, target_b;
	if (a < b) {
		target_a = a;
		target_b = b;
	}
	else {
		target_a = b;
		target_b = a;
	}
	//������ȸ �� Ÿ�� ���� �ε��� ã��
	for (int i = 0; i < m; i++) {
		if (G.edges[i].a == target_a && G.edges[i].b == target_b && G.edges[i].id != -1) {
			target_index = i;
			break;
		}
	}

	//3.w�� ���� ���� ����,����,���� ����� �����Ѵ�
	//4.������ �����ϴ� ���
	if (target_index != -1) {
		if (w == 0) {
			removeMethod(a, b, target_index);
			return;
		}//������ �����ϴµ� w�� 0�̸� ����
		else {//������ �����ϴµ� w�� 0�� �ƴϸ� ����
			G.edges[target_index].weight = w;
		}
	}
	//5.������ �������� �ʴ� ���
	else if (target_index == -1) {
		if (w == 0) {//�ƹ��͵� ��������
			return;
		}
		else {//����
			edgeMethod(m++, a, b, w);
			return;
		}
	}

}

void printAdj(int a) {
	if (a <= 0 || a > 6) {
		printf("-1\n");
		return;
	}
	NODE* head = G.vertices[a].adj_list;
	int z;
	int e;
	while (head->next != NULL) {
		z = opposite(head->next, a);//�������� a �ݴ��� ����z
		e = head->next->index;
		printf(" %d %d", G.vertices[z].id, G.edges[e].weight);
		head = head->next;
	}
	printf("\n");
}

void buildGraph() {
	//������ 7�������ؼ� 1������ 6���������
	//������ �ִ� 21���̹Ƿ� 21�� ����
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * 7);
	G.edges = (EDGE*)malloc(sizeof(EDGE) * 21);

	//�������� �� ��������Ʈ ����� �ʱ�ȭ
	for (int i = 1; i <= 6; i++) {
		G.vertices[i].id = i;
		G.vertices[i].adj_list = get_node(-1);
	}
	//�׷��� �׸��� ���� ���� ����
	m = 0;//m�� ������ ���簳��
	edgeMethod(m++, 1, 2, 1);

	//1������
	edgeMethod(m++, 1, 3, 1);

	//2������
	edgeMethod(m++, 1, 4, 1);

	//3������
	edgeMethod(m++, 1, 6, 2);

	//4������
	edgeMethod(m++, 2, 3, 1);

	//5������
	edgeMethod(m++, 3, 5, 4);
	//6������
	edgeMethod(m++, 5, 5, 4);
	//7������
	edgeMethod(m++, 5, 6, 3);
}
int main() {
	//�׷��� ���带 �����ϰ�
	buildGraph();

	//��ȭ�� ���α׷� ����
	char com;

	while (1) {
		scanf("%c", &com);
		if (com == 'a') {
			int number;
			scanf("%d", &number);
			printAdj(number);
		}
		else if (com == 'm') {
			int a, b, w;
			scanf("%d %d %d", &a, &b, &w);
			modifyMethod(a, b, w);
		}
		else if (com == 'q') {
			break;
		}
		getchar();
	}
	return 0;
}