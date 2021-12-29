#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct Graph {
	int** matrix; //�׷��� �������
	int n; //���� ����
}GraphType;

GraphType g;
int n, m, s;

void edgeMethod(int a, int b) {
	//�׷����� 2�����迭�� �����߰� 
	g.matrix[a][b] = 1;
	g.matrix[b][a] = 1;
}


void BFS(int s) {
	int size = g.n;
	int* queue, * visit;
	int rear = 0, front = 0;
	queue = (int*)malloc(sizeof(int) * size);
	visit = (int*)malloc(sizeof(int) * (size + 1));
	//visit �ʱ�ȭ
	memset(visit, 0, sizeof(int) * (size + 1));
	visit[s] = 1; //���� ������ �湮�� �� üũ

	printf("%d\n", s);
	queue[rear++] = s;

	while (front < rear) {
		s = queue[front++];
		for (int i = 1; i <= g.n; i++) {
			if (g.matrix[s][i] == 1 && !visit[i]) {//�湮���� �������
				visit[i] = 1; //�湮
				printf("%d\n", i);
				queue[rear++] = i;
			}
		}
	}
}

void buildGraph() {
	scanf("%d %d %d", &n, &m, &s);
	g.n = n;
	g.matrix = (int**)malloc(sizeof(int*) * (n + 1));

	//2�����迭 �޸��Ҵ�
	for (int i = 0; i <= n; i++) {
		g.matrix[i] = (int*)malloc(sizeof(int) * (n + 1));//i�� �޸� �Ҵ�
		memset(g.matrix[i], 0, sizeof(int) * (n + 1)); //�޸� 0���� �ʱ�ȭ
	}
	//�����߰�
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edgeMethod(a, b);
	}
}

int main() {
	buildGraph();
	BFS(s);
	return 0;
}