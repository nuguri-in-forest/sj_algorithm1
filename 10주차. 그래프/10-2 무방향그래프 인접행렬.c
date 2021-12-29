#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define MAX 6

typedef struct Graph {
	int** matrix; //�׷��� �������
	int n; //���� ����
}GraphType;

GraphType g;

void edgeMethod(int a, int b, int w) {
	//�׷����� 2�����迭�� ������ �־��ָ��
	g.matrix[a][b] = w;
	g.matrix[b][a] = w;
}

void removeMethod(int a, int b) { //���� ����
	g.matrix[a][b] = 0; //���� 0 ����
	g.matrix[b][a] = 0; //���� 0 ����
}

int find(int a, int b) {//���� ���� ���� Ȯ��
	if (g.matrix[a][b]!=0) {//���� ����
		return 1;
	}
	else { //���� ���� x
		return 0;
	}
}

void modifyMethod(int a, int b, int weight) { //���� ������� �Լ�
	if (a > g.n || b > g.n || a < 1 || b < 1) { //������ �������� ���� ��
		printf("-1\n");
		return;
	}

	if (weight == 0) { //���� ����
		removeMethod(a, b);
	}
	else {//���� �����ϴ��� üũ
		//��Ī������ ����ġ����
		if (find(a, b)) { //��������->����ġ ����
			g.matrix[a][b] = weight;
			g.matrix[b][a] = weight;
		}
		else {
			edgeMethod(a, b, weight);
		}
	}
}

void printAdj(int num) //���
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

	//2�����迭 �޸��Ҵ�
	for (int i = 0; i <= 6; i++) {
		g.matrix[i] = (int*)malloc(sizeof(int) * (MAX + 1));//i�� �޸� �Ҵ�
		memset(g.matrix[i], 0, sizeof(int) * (MAX + 1)); //�޸� 0���� �ʱ�ȭ
	}
	//�����߰�
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

		if (com == 'a') { //����ȣ ������������ (�������, ����ġ) ������� ���
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