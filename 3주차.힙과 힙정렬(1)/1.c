#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Heap[99];
int n; //���� ũ��, ���� Ű�� ����



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


void insertItem(key) {

	//���� n+1 ��ġ�� key ����
	n = n + 1;
	Heap[n] = key;
	
	// ����� heapify
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
			//n��ġ�� key ����
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