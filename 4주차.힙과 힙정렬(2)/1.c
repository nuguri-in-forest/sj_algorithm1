#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

//���� �� Ű ������ ��Ÿ���� n
int Heap[100];
int n;

void upHeap(int i) {
	//base case�� ��Ʈ��忡 ����������
	if (i == 1) return;
	
	//�θ��� ����
	int parent = i / 2;

	if (Heap[i] > Heap[parent]) {
		//�����尡 �θ��庸�� ũ�ٸ� ���� �÷����� (�ִ���)
		//swap
		int temp = Heap[i];
		Heap[i] = Heap[parent];
		Heap[parent] = temp;
	}

	upHeap(parent);//recursive case
}
void insertItem(int key) {
	//last node�� ��Ÿ���� n�� 1 ����
	n = n + 1;
	Heap[n] = key; //������ ��忡 key ����

	//upheap�� ���� heapify ����
	upHeap(n);

}

void downHeap(int i,int last) {
	int left = 2 * i;
	int right = 2 * i + 1;

	//base case
	//�ܺγ�忡 �����ߴٸ� ��� stop
	if (left > last) return;

	//�ڽĳ���� �� ū ��� ã��
	int larger = left;

	if (right <= last) {//last node�� n�� �ƴ� �������� last�ΰͿ� ��������.
		if (Heap[right] > Heap[larger]) {
			larger = right;
		}
	}
	

	//�ڽĳ��� ������ swap
	if (Heap[i] < Heap[larger]) {
		int temp = Heap[i];
		Heap[i] = Heap[larger];
		Heap[larger] = temp;
	}
	downHeap(larger, last);
}
void inPlaceHeapSort() {
	for (int i = n; i >= 2; i--) {
		//�ִ����� �����Ǿ������Ƿ�
		//Heap[1] �� �ִ밪�� ����Ǿ�����
		//������ ������ ==> �Ķ��� ����
		//����Ʈ ==> ����� ����
		// ��谡 �����ʿ��� �������� ��ĭ�� �̵��ϴ� ��
		int temp = Heap[1];
		Heap[1] = Heap[i];
		Heap[i] = temp;

		//��Ʈ��忡 �ּҰ��� ��������Ƿ�, downHeap�� ���� heapify
		// i��° ���� ���ĵǾ������Ƿ� , last ��带 i-1�� ����
		downHeap(1, i - 1);
	}

}
void printArray() {
	for(int i = 1; i <= n; i++) {
		printf(" %d", Heap[i]);
	}
}
int main() {

	//phase1 ���Խ� �� ����
	int key = 0;
	int cnt = 0;
	scanf("%d", &cnt);

	for (int i = 0; i < cnt; i++) {
		scanf("%d", &key);//key�� �Է¹ް�
		insertItem(key); //����
	}
	
	//phase2 ���ڸ� �� ����
	inPlaceHeapSort();

	//���
	printArray();
}

