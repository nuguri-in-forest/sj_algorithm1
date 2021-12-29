#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Heap[100];
int n;

void upHeap(int v) {
	int parent = v / 2;

	//base case
	//����� heapify�ϱ� ��Ʈ�� �����ϸ� ����
	if (v == 1) return;

	if (Heap[v] > Heap[parent]) {
		//swap
		int temp = Heap[v];
		Heap[v] = Heap[parent];
		Heap[parent] = temp;
	}
	//���ȣ��
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
	//���� ����� �ڽĳ��(l_child)�� n���� ũ�ٸ� return
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

	//key�� ��Ʈ���
	int key = Heap[1];
	//��Ʈ��� �ڸ��� ������ ��� �־��ְ�
	Heap[1] = Heap[n];
	//ũ�⸦ 1���̸� �����Ϸ�
	n--;
	//����� heapify����
	downHeap(1);
	//Ű��ȯ
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