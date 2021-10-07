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
	//������ �ǹ� ����
	k = rand() % (r - l + 1) + l; // l���� r����
	return k;
}

IDX inPlacePartition(int* arr, int l, int r, int k) {
	IDX res;

	int p = arr[k]; //�ǹ�����
	// hide pivot
	int temp = arr[k];
	arr[k] = arr[r];
	arr[r] = temp;

	int i = l;
	int j = r - 1;

	//������������ ����
	while (i <= j) {

		// left���� ū ���Ұ� �ִ��� �˻� 
		while (i <= j && arr[i] <= p) {
			i++;
		}
		// right���� ���� ���Ұ� �ִ��� �˻�
		while (i <= j && arr[j] >= p) {
			j--;
		}

		// ������ �߰ߵ� ���� �ִٸ� swap
		if (i < j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//while���� ���Դٴ°� �����ȴٴ� ��
	//�ǹ��� ������ �������Ƿ�, arr[i]�� �ǹ��� �ְ�
	// LT, EQ, GT�� ����
	temp = arr[i];
	arr[i] = arr[r];
	arr[r] = temp;

	//�ǹ��� ���� �ε��� i�� ��ġ��
	//�ǹ��� ���� ���Ұ� �󸶳� �ִ��� �˾Ƴ����Ѵ�

	//LT�� l���� a-1
	res.a = i;


	j = r - 1; //�ٽ� ����Ʈ�� ���� ����, ���� r�� �ȵǳ�?

	//�ǹ��� ���� ���Ұ� �ִٸ�
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

	//QuickSort ����
	inPlaceQuickSort(arr, 0, n - 1);

	//������ print
	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	//�޸𸮹ݳ�
	free(arr);
}


