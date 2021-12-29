#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define MAX 6

typedef struct Graph {
	int** matrix; //그래프 인접행렬
	int n; //정점 개수
}GraphType;

GraphType g;

void edgeMethod(int a, int b, int w) {
	//그래프에 2차원배열에 간선을 넣어주면됨
	g.matrix[a][b] = w;
	g.matrix[b][a] = w;
}

void removeMethod(int a, int b) { //간선 삭제
	g.matrix[a][b] = 0; //간선 0 설정
	g.matrix[b][a] = 0; //간선 0 설정
}

int find(int a, int b) {//간선 존재 유무 확인
	if (g.matrix[a][b]!=0) {//간선 존재
		return 1;
	}
	else { //간선 존재 x
		return 0;
	}
}

void modifyMethod(int a, int b, int weight) { //간선 변경사항 함수
	if (a > g.n || b > g.n || a < 1 || b < 1) { //정점이 존재하지 않을 때
		printf("-1\n");
		return;
	}

	if (weight == 0) { //간선 삭제
		removeMethod(a, b);
	}
	else {//간선 존재하는지 체크
		//대칭형으로 가중치변경
		if (find(a, b)) { //간선존재->가중치 변경
			g.matrix[a][b] = weight;
			g.matrix[b][a] = weight;
		}
		else {
			edgeMethod(a, b, weight);
		}
	}
}

void printAdj(int num) //출력
{
	if (g.n < num || num < 1) {
		printf("-1\n");
		return;
	}

	for (int i = 1; i <= g.n; i++)
	{
		if (g.matrix[num][i])
		{
			printf(" %d %d", i, g.matrix[num][i]);
		}
	}
	printf("\n");
}

void buildGraph() {
	g.n = MAX;
	g.matrix = (int**)malloc(sizeof(int*) * (MAX + 1));

	//2차원배열 메모리할당
	for (int i = 0; i <= 6; i++) {
		g.matrix[i] = (int*)malloc(sizeof(int) * (MAX + 1));//i행 메모리 할당
		memset(g.matrix[i], 0, sizeof(int) * (MAX + 1)); //메모리 0으로 초기화
	}
	//간선추가
	edgeMethod(1, 2, 1);
	edgeMethod(1, 3, 1);
	edgeMethod(1, 4, 1);
	edgeMethod(1, 6, 2);
	edgeMethod(2, 3, 1);
	edgeMethod(3, 5, 4);
	edgeMethod(5, 5, 4);
	edgeMethod(5, 6, 3);

}

int main() {
	buildGraph();

	int num;
	char com;
	int a, b, w;

	while (1) {
		scanf("%c", &com);

		if (com == 'a') { //노드번호 오름차순으로 (인접노드, 가중치) 순서대로 출력
			scanf("%d", &num);
			printAdj(num);
		}
		else if (com == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			modifyMethod(a, b, w);
		}
		else if (com == 'q') {
			return 0;
		}
		getchar();
	}

	return 0;
}