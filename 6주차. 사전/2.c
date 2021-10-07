#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int findElement(int* L, int k, int n) {
	int l,r,mid;
	l = 0;
	r = n - 1;
	mid = (l + r)/2;
	
	while (l <= r) {
		
		if (k == L[mid]) {
			return mid;
		}

		else if (k < L[mid]) {// mid���� key������ ũ��
			r = mid - 1;
		}

		else {// mid���� key������ ������
			l = mid + 1;
		}
		mid = (l + r) / 2;

	}
	//��ã�� ���
	return l;
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
}