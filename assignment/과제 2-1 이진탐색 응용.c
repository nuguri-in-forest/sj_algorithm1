#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
//이진탐색
int rFE1(int* L, int k, int l, int r) {
	//base case
	// x>=k1 이므로, l을 반환
	if (l > r) return l;
	int mid = (l + r) / 2;

	if (k == L[mid]) return mid;//인덱스반환

	//recursive case
	else if (k < L[mid]) {
		rFE1(L, k, l, mid - 1);
	}
	else {
		rFE1(L, k, mid + 1, r);
	}
}

int rFE2(int* L, int k, int l, int r) {
	//base case
	// x<=k2 이므로 r을 반환
	if (l > r) return r;
	int mid = (l + r) / 2;

	if (k == L[mid]) return mid;//인덱스반환
	//recursive case
	else if (k < L[mid]) {
		rFE2(L, k, l, mid - 1);
	}
	else {
		rFE2(L, k, mid + 1, r);
	}
}

int main() {
	int n, k1, k2;
	int* L;
	//배열크기 n과 사전의 키 x의 위치를 나타내는 k1,k2 입력
	//크기가 n인 배열 동적으로 할당
	scanf("%d %d %d", &n, &k1, &k2);
	L = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &L[i]);
	}

	// k1<= x <=k2
	int res_k1 = rFE1(L, k1, 0, n - 1);
	int res_k2 = rFE2(L, k2, 0, n - 1);

	//엇갈린다면 조건을 만족하는 키가 없는 것 이므로 -1 출력
	if (res_k1 > res_k2) printf(" -1");
	else {
		for (int i = res_k1; i <= res_k2; i++) {
			printf(" %d", i);
		}
	}

	free(L);
}
