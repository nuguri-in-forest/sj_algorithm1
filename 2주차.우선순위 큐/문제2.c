#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void insertion_sort(int* q, int n) {
	
	for (int i = 0; i < n-1; i++) {

		int j = i;//배열의 앞을 정렬상태로 유지
		while (q[j] > q[j + 1]) {
			//swap
			int temp = q[j];
			q[j] = q[j+1];
			q[j+1] = temp;
			if (j == 0) break;
			j--;
		}
	}
	for (int i = 0; i < n; i++) printf(" %d", q[i]);
	
}

int main()
{
	int n;
	scanf("%d", &n);
	int* q = 0;
	q = malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &q[i]);
	}
	
	insertion_sort(q,n);

	return 0;
}