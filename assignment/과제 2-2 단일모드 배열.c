#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
//최대원소
int findMaxElement(int* L, int n) {
	int l, r, mid;
	l = 0;
	r = n - 1;
	//증가->감소의 단일배열이므로
	//증가구간에서는 left를 mid + 1로 설정하고
	//감소구간에서는 right를 mid -1로 설정해서
	// 엇갈릴때까지 반복한다.
	do {
		int mid = (l + r) / 2;

		if (L[mid] < L[mid + 1]) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	} while (l <= r);

	return l;
}

int findMinElement(int* L, int n) {
	int l, r, mid;
	l = 0;
	r = n - 1;
	//증가->감소의 단일배열이므로
	//감소구간에서는 left를 mid + 1로 설정하고
	//증가구간에서는 right를 mid -1로 설정해서
	// 엇갈릴때까지 반복한다.
	do {
		int mid = (l + r) / 2;

		if (L[mid] > L[mid + 1]) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	} while (l <= r);

	return l;
}

int isSingle(int* L, int n) {
	//증가 -> 감소인지, 감소-> 증가인지 초기값 확인
	int i = 0;
	if (L[0] < L[1]) {//처음이 증가구간이라면
		//증가가 멈추는 구간 search
		while (L[i] < L[i + 1]) i++;
		//증가 -> 감소인지 확인
		while (L[i] > L[i + 1] && i < n - 1) i++;
		if (i == n - 1) return 1;
		else return 0;
	}

	else if (L[0] > L[1]) {//처음이 감소구간이라면
		while (L[i] > L[i + 1]) i++;
		//감소->증가인지 확인
		while (L[i] < L[i + 1] && i < n - 1) i++;
		if (i == n - 1) return -1;
		else return 0;
	}
	else {//처음 두 숫자가같다면 단일모드가 아니므로
		return 0;
	}
}

int main() {
	int n, k;
	int* L;
	//배열크기 n과 사전의 키 x의 위치를 나타내는 k1,k2 입력
	//크기가 n인 배열 동적으로 할당
	scanf("%d", &n);
	L = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &L[i]);
	}

	//is single mode array?
	int res = isSingle(L, n);


	if (res == 1) { //find max
		printf(" %d %d", res, L[findMaxElement(L, n)]);
	} //find min
	else if (res == -1) {
		printf(" %d %d", res, L[findMinElement(L, n)]);
	} // not single mode array
	else printf(" %d", res);

	free(L);
}
