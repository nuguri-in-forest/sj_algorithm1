#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void selection_sort(int* q, int n) {
	int max = 0;
	int max_idx = 0;
	for (int i = 0; i < n; i++) {

		//max °ª select
		max = q[0];
		max_idx = 0;
		for (int j = 0; j < n - i; j++) {
			if (max < q[j]) {
				max = q[j];
				max_idx = j;
			}
		}
		//±³È¯
		int temp = q[n - 1 - i];
		q[n - 1 - i] = q[max_idx];
		q[max_idx] = temp;
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
	
	selection_sort(q,n);
	free(q);
	return 0;
}