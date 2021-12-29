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
	//자식노드가 n보다 클때
	if (l_child > n) return;

	int larger = l_child;
	if (Heap[larger] < Heap[r_child]) {
		larger = r_child;
	}

	//비교
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
	//내부노드에 한해서만 downHeap 수행
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