#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Heap[99];
int n; //힙의 크기, 현재 키의 개수



void upHeap(int v) {

	if (v == 1) { // isRoot ? 
		return;
	}
	int parent = v / 2;

	if (Heap[v] <= Heap[parent]) {
		return;
	}

	//swap
	int temp = Heap[v];
	Heap[v] = Heap[parent];
	Heap[parent] = temp;
	upHeap(parent);

}

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


void insertItem(key) {

	//힙의 n+1 위치에 key 삽입
	n = n + 1;
	Heap[n] = key;
	
	// 상향식 heapify
	upHeap(n);
	
}

int removeMax() {

	int key = Heap[1];
	Heap[1] = Heap[n];
	n--;
	downHeap(1);
	return key;
}




void printHeap() {
	for (int i = 1; i < n+1; i++) {
		printf(" %d", Heap[i]);
	}
	printf("\n");
}
int main() {
	/*
	<command>
	i : insert , p : print
	d : delete , q : quit
	*/
	char command; 
	int key;
	int root = 0;

	
	while (1) {
		scanf("%c", &command);

		if (command == 'i') {
			scanf("%d", &key);
			//n위치에 key 삽입
			insertItem(key);
			printf("0\n");
		}

		else if (command == 'd') {
			root = removeMax();
			printf("%d\n", root);
		}

		else if (command == 'p') {
			printHeap();
		}
		else if (command == 'q') {
			break;
		}
	}


}