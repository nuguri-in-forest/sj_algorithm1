#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int rFE(int* L, int k, int l, int r) {
	//base case
	if (l > r) return r;
	int mid = (l + r) / 2;

	if (k == L[mid]) return mid;//¿Œµ¶Ω∫π›»Ø
	else if (k < L[mid]) {
		rFE(L, k, l, mid - 1);
	}
	else {
		rFE(L, k, mid + 1, r);
	}
}
int findElement(int* L, int k, int n) {
	return rFE(L, k, 0, n - 1);
}
int main() {
	int n, k;
	int* L;
	scanf("%d %d", &n, &k);
	L = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &L[i]);
	}

	int res = findElement(L, k, n);
	printf(" %d", res);
	free(L);
}