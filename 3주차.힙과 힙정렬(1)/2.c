#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Heap[99];
int n; //���� ũ��, ���� Ű�� ����


void downHeap(int v) {
	int left_child = 2 * v;
	int right_child = 2 * v + 1;

	// isleaf ?
	// �������� �ڽĳ�尡 ���ٸ� return
	if (left_child > n) {
		return;
	}


	int larger = left_child;

	//�� ū �ڽ��� ã��
	if (Heap[right_child] > Heap[larger]) {
		larger = right_child;
	}

	//�ڽİ� �θ��带 ���ؼ�, �ڽ��� ũ�ٸ� ��ȯ
	if (Heap[v] < Heap[larger]) {
		int temp = Heap[v];
		Heap[v] = Heap[larger];
		Heap[larger] = temp;
	}
	//����� ����
	downHeap(larger);

}

void buildHeap() {

	for (int i = n / 2; i >= 1; i--) {
		downHeap(i);
	}

}



void printHeap() {
	for (int i = 1; i < n + 1; i++) {
		printf(" %d", Heap[i]);
	}
	printf("\n");
}
int main() {

	scanf("%d", &n);
	//Heap�� �ε��� 0�� ����д�

	for (int i = 1; i <= n; i++) {
		scanf("%d", &Heap[i]);
	}
	buildHeap();
	printHeap();
}