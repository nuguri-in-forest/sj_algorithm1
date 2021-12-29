#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
//�ִ����
int findMaxElement(int* L, int n) {
	int l, r, mid;
	l = 0;
	r = n - 1;
	//����->������ ���Ϲ迭�̹Ƿ�
	//�������������� left�� mid + 1�� �����ϰ�
	//���ұ��������� right�� mid -1�� �����ؼ�
	// ������������ �ݺ��Ѵ�.
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
	//����->������ ���Ϲ迭�̹Ƿ�
	//���ұ��������� left�� mid + 1�� �����ϰ�
	//�������������� right�� mid -1�� �����ؼ�
	// ������������ �ݺ��Ѵ�.
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
	//���� -> ��������, ����-> �������� �ʱⰪ Ȯ��
	int i = 0;
	if (L[0] < L[1]) {//ó���� ���������̶��
		//������ ���ߴ� ���� search
		while (L[i] < L[i + 1]) i++;
		//���� -> �������� Ȯ��
		while (L[i] > L[i + 1] && i < n - 1) i++;
		if (i == n - 1) return 1;
		else return 0;
	}

	else if (L[0] > L[1]) {//ó���� ���ұ����̶��
		while (L[i] > L[i + 1]) i++;
		//����->�������� Ȯ��
		while (L[i] < L[i + 1] && i < n - 1) i++;
		if (i == n - 1) return -1;
		else return 0;
	}
	else {//ó�� �� ���ڰ����ٸ� ���ϸ�尡 �ƴϹǷ�
		return 0;
	}
}

int main() {
	int n, k;
	int* L;
	//�迭ũ�� n�� ������ Ű x�� ��ġ�� ��Ÿ���� k1,k2 �Է�
	//ũ�Ⱑ n�� �迭 �������� �Ҵ�
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
