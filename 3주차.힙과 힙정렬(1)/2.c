#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Heap[99];
int n; //힙의 크기, 현재 키의 개수


void downHeap(int v) {
	int left_child = 2 * v;
	int right_child = 2 * v + 1;

	// isleaf ?
	// 현재노드의 자식노드가 없다면 return
	if (left_child > n) {
		return;
	}


	int larger = left_child;

	//더 큰 자식을 찾고
	if (Heap[right_child] > Heap[larger]) {
		larger = right_child;
	}

	//자식과 부모노드를 비교해서, 자식이 크다면 교환
	if (Heap[v] < Heap[larger]) {
		int temp = Heap[v];
		Heap[v] = Heap[larger];
		Heap[larger] = temp;
	}
	//하향식 구조
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
	//Heap의 인덱스 0은 비워둔다

	for (int i = 1; i <= n; i++) {
		scanf("%d", &Heap[i]);
	}
	buildHeap();
	printHeap();
}