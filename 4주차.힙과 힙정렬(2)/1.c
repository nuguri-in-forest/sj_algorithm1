#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

//힙과 총 키 개수를 나타내는 n
int Heap[100];
int n;

void upHeap(int i) {
	//base case는 루트노드에 도달했을떄
	if (i == 1) return;
	
	//부모노드 설정
	int parent = i / 2;

	if (Heap[i] > Heap[parent]) {
		//현재노드가 부모노드보다 크다면 위로 올려야함 (최대힙)
		//swap
		int temp = Heap[i];
		Heap[i] = Heap[parent];
		Heap[parent] = temp;
	}

	upHeap(parent);//recursive case
}
void insertItem(int key) {
	//last node를 나타내는 n을 1 증가
	n = n + 1;
	Heap[n] = key; //마지막 노드에 key 삽입

	//upheap을 통해 heapify 수행
	upHeap(n);

}

void downHeap(int i,int last) {
	int left = 2 * i;
	int right = 2 * i + 1;

	//base case
	//외부노드에 도달했다면 재귀 stop
	if (left > last) return;

	//자식노드중 더 큰 노드 찾기
	int larger = left;

	if (right <= last) {//last node는 n이 아닌 힙에서의 last인것에 주의하자.
		if (Heap[right] > Heap[larger]) {
			larger = right;
		}
	}
	

	//자식노드와 현재노드 swap
	if (Heap[i] < Heap[larger]) {
		int temp = Heap[i];
		Heap[i] = Heap[larger];
		Heap[larger] = temp;
	}
	downHeap(larger, last);
}
void inPlaceHeapSort() {
	for (int i = n; i >= 2; i--) {
		//최대힙이 구성되어있으므로
		//Heap[1] 에 최대값이 저장되어있음
		//가상의 힙공간 ==> 파란색 공간
		//리스트 ==> 노란색 공간
		// 경계가 오른쪽에서 왼쪽으로 한칸씩 이동하는 것
		int temp = Heap[1];
		Heap[1] = Heap[i];
		Heap[i] = temp;

		//루트노드에 최소값이 들어있으므로, downHeap을 통해 heapify
		// i번째 노드는 정렬되어있으므로 , last 노드를 i-1로 설정
		downHeap(1, i - 1);
	}

}
void printArray() {
	for(int i = 1; i <= n; i++) {
		printf(" %d", Heap[i]);
	}
}
int main() {

	//phase1 삽입식 힙 생성
	int key = 0;
	int cnt = 0;
	scanf("%d", &cnt);

	for (int i = 0; i < cnt; i++) {
		scanf("%d", &key);//key를 입력받고
		insertItem(key); //삽입
	}
	
	//phase2 제자리 힙 정렬
	inPlaceHeapSort();

	//출력
	printArray();
}

