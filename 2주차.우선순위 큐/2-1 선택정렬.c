#pragma warning(disable:4996)
#include <stdio.h>

/* 선택 정렬 구현 */

void selection_sort(int* arr, int n) {
	int max = 0;
	int max_idx = 0;

	for (int i = 0; i < n; i++) {
		max = arr[0];
		max_idx = 0;

		//제일 큰 값 찾기
		for (int j = 0; j < n - i; j++) {
			if (arr[j] > max) {
				max = arr[j];
				max_idx = j;
			}
		}

		//찾은 큰 값 맨뒤로 보내기
		int temp = arr[max_idx];
		arr[max_idx] = arr[n - 1 - i];
		arr[n - 1 - i] = temp;
	}

}


int main() {
	int n;
	scanf("%d", &n);
	int* arr = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	selection_sort(arr, n);
	//after sorting

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

}