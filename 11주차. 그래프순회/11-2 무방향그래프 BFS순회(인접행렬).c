#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct Graph {
	int** matrix; //그래프 인접행렬
	int n; //정점 개수
}GraphType;

GraphType g;
int n, m, s;

void edgeMethod(int a, int b) {
	//그래프에 2차원배열에 간선추가 
	g.matrix[a][b] = 1;
	g.matrix[b][a] = 1;
}


void BFS(int s) {
	int size = g.n;
	int* queue, * visit;
	int rear = 0, front = 0;
	queue = (int*)malloc(sizeof(int) * size);
	visit = (int*)malloc(sizeof(int) * (size + 1));
	//visit 초기화
	memset(visit, 0, sizeof(int) * (size + 1));
	visit[s] = 1; //시작 정점을 방문한 것 체크

	printf("%d\n", s);
	queue[rear++] = s;

	while (front < rear) {
		s = queue[front++];
		for (int i = 1; i <= g.n; i++) {
			if (g.matrix[s][i] == 1 && !visit[i]) {//방문하지 않은경우
				visit[i] = 1; //방문
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

	//2차원배열 메모리할당
	for (int i = 0; i <= n; i++) {
		g.matrix[i] = (int*)malloc(sizeof(int) * (n + 1));//i행 메모리 할당
		memset(g.matrix[i], 0, sizeof(int) * (n + 1)); //메모리 0으로 초기화
	}
	//간선추가
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