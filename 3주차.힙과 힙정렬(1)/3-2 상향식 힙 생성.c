#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Heap[100];
int n;

void downHeap(int v)
{
	int l_child = 2 * v;
	int r_child = 2 * v + 1;

	//base case
	//�ڽĳ�尡 n���� Ŭ��
	if (l_child > n) return;

	int larger = l_child;
	if (Heap[larger] < Heap[r_child]) {
		larger = r_child;
	}

	//��
	if (Heap[v] < Heap[larger]) {
		//swap
		int temp = Heap[v];
		Heap[v] = Heap[larger];
		Heap[larger] = temp;
	}
	//recursive case
	downHeap(larger);
}

void buildHeap() {
	//���γ�忡 ���ؼ��� downHeap ����
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

	for (int i = 1; i < n + 1; i++) {
		scanf("%d", &Heap[i]);
	}
	buildHeap();
	printHeap();
}