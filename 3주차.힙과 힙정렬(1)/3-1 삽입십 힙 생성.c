#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Heap[100];
int n;

void upHeap(int v) {
	int parent = v / 2;

	//base case
	//상향식 heapify니까 루트에 도달하면 종료
	if (v == 1) return;

	if (Heap[v] > Heap[parent]) {
		//swap
		int temp = Heap[v];
		Heap[v] = Heap[parent];
		Heap[parent] = temp;
	}
	//재귀호출
	upHeap(parent);
}

void insertItem(int key) {
	n = n + 1;
	Heap[n] = key;
	upHeap(n);
}


void downHeap(int v)
{
	int r_child = 2 * v + 1;
	int l_child = 2 * v;

	//base case
	//현재 노드의 자식노드(l_child)가 n보다 크다면 return
	if (l_child > n) return;

	int larger = l_child;

	if (Heap[larger] < Heap[r_child]) {
		larger = r_child;
	}

	if (Heap[v] < Heap[larger]) {
		int temp = Heap[v];
		Heap[v] = Heap[larger];
		Heap[larger] = temp;
	}
	downHeap(larger);
}

int removeMax() {

	//key는 루트노드
	int key = Heap[1];
	//루트노드 자리에 마지막 노드 넣어주고
	Heap[1] = Heap[n];
	//크기를 1줄이면 삭제완료
	n--;
	//하향식 heapify수행
	downHeap(1);
	//키반환
	return key;
}

void printHeap() {
	for (int i = 1; i < n + 1; i++) {
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