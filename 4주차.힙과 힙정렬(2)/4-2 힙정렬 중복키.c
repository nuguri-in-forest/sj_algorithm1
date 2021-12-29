#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Heap[100];
int n;

void downHeap(int v, int last)
{
	int l_child = 2 * v;
	int r_child = 2 * v + 1;

	//base case
	//�ڽĳ�尡 n���� Ŭ��
	if (l_child > last) return;

	int larger = l_child;

	if (r_child <= last) {
		if (Heap[larger] < Heap[r_child]) {
			larger = r_child;
		}
	}
	//��
	if (Heap[v] < Heap[larger]) {
		//swap
		int temp = Heap[v];
		Heap[v] = Heap[larger];
		Heap[larger] = temp;
	}
	//recursive case
	downHeap(larger, last);
}

void buildHeap() {
	//���γ�忡 ���ؼ��� downHeap ����
	for (int i = n / 2; i >= 1; i--) {
		downHeap(i, n);
	}
}
void inPlaceHeapSort() {
	//�ڿ������� �ִ��� ä���
	// �� ����� ���δ�.
	for (int i = n; i >= 2; i--) {
		int temp = Heap[1];
		Heap[1] = Heap[i]; // i means last node
		Heap[i] = temp;


		downHeap(1, i - 1);
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
	inPlaceHeapSort();
	printHeap();
}