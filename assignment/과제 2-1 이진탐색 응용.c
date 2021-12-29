#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
//����Ž��
int rFE1(int* L, int k, int l, int r) {
	//base case
	// x>=k1 �̹Ƿ�, l�� ��ȯ
	if (l > r) return l;
	int mid = (l + r) / 2;

	if (k == L[mid]) return mid;//�ε�����ȯ

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
	// x<=k2 �̹Ƿ� r�� ��ȯ
	if (l > r) return r;
	int mid = (l + r) / 2;

	if (k == L[mid]) return mid;//�ε�����ȯ
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
	//�迭ũ�� n�� ������ Ű x�� ��ġ�� ��Ÿ���� k1,k2 �Է�
	//ũ�Ⱑ n�� �迭 �������� �Ҵ�
	scanf("%d %d %d", &n, &k1, &k2);
	L = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &L[i]);
	}

	// k1<= x <=k2
	int res_k1 = rFE1(L, k1, 0, n - 1);
	int res_k2 = rFE2(L, k2, 0, n - 1);

	//�������ٸ� ������ �����ϴ� Ű�� ���� �� �̹Ƿ� -1 ���
	if (res_k1 > res_k2) printf(" -1");
	else {
		for (int i = res_k1; i <= res_k2; i++) {
			printf(" %d", i);
		}
	}

	free(L);
}
