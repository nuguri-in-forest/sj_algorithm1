#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct index {
	int a;
	int b;
}IDX;

int findPivot(int* arr, int l, int r) {
	int k;
	srand(time(NULL));
	//무작위 피벗 선택
	k = rand() % (r - l + 1) + l; // l에서 r까지
	return k;
}

IDX inPlacePartition(int* arr, int l, int r, int k) {
	IDX res;

	int p = arr[k]; //피벗설정
	// hide pivot
	int temp = arr[k];
	arr[k] = arr[r];
	arr[r] = temp;

	int i = l;
	int j = r - 1;

	//엇갈릴때까지 분할
	while (i <= j) {

		// left에서 큰 원소가 있는지 검사 
		while (i <= j && arr[i] <= p) {
			i++;
		}
		// right에서 작은 원소가 있는지 검사
		while (i <= j && arr[j] >= p) {
			j--;
		}

		// 위에서 발견된 것이 있다면 swap
		if (i < j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//while문을 나왔다는건 엇갈렸다는 뜻
	//피벗의 역할이 끝났으므로, arr[i]에 피벗을 넣고
	// LT, EQ, GT로 분할
	temp = arr[i];
	arr[i] = arr[r];
	arr[r] = temp;

	//피벗은 현재 인덱스 i에 위치함
	//피벗과 같은 원소가 얼마나 있는지 알아내야한다

	//LT는 l부터 a-1
	res.a = i;


	j = r - 1; //다시 리스트의 끝을 지정, 여기 r은 안되나?

	//피벗과 같은 원소가 있다면
	while ((i+1) <= j && arr[i+1] == p) {
		i++;
	}
	res.b = i;

	return res;
}

void inPlaceQuickSort(int* arr, int l, int r) {

	if (l >= r) return;
	IDX res;
	int k = findPivot(arr, l, r);
	res = inPlacePartition(arr, l, r, k);
	inPlaceQuickSort(arr, l, (res.a) - 1);
	inPlaceQuickSort(arr, (res.b) + 1, r);

}


int main() {
	int n, * arr;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	//QuickSort 수행
	inPlaceQuickSort(arr, 0, n - 1);

	//정렬후 print
	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	//메모리반납
	free(arr);
}


