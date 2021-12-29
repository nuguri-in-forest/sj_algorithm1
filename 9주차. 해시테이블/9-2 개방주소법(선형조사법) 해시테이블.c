#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

int* Table;
int M;

// h(x) = x % M
// �����ּҹ� �ؽ����̺�
int h(int x) {
	return x % M;
}

int Nextindex(int v, int i) {
	return (v + i) % M;
}


void insertItem(int x) {

	int v = h(x), i = 0;
	int idx;

	while (i < M) {
		idx = Nextindex(v, i);
		//�̵��� ������ empty���
		if (Table[idx] == 0) {
			//����
			Table[idx] = x;
			//�浹Ƚ����ŭ C ���
			for (int j = 0; j < i; j++) {
				printf("C");
			}
			//������ �ּ� �ε��� ���
			printf("%d\n", idx);
			return;
		}
		else {
			i++;
		}
	}
}

void searchItem(int x) {

	int v = h(x), i = 0;
	int idx;

	while (i < M) {
		idx = Nextindex(v, i);
		if (Table[idx] == 0) {
			printf("-1\n");
			return;
		}
		else if (Table[idx] == x) {
			printf("%d %d\n", idx, Table[idx]);
			return;

		}
		else {
			i++;
		}

	}
	printf("-1\n");

}

int main() {

	int n, key;
	char com;
	scanf("%d", &M);
	//Mũ���� �迭�� �ؽ����̺� �����Ҵ�
	Table = (int*)malloc(sizeof(int) * M);

	//���̺� �ʱ�ȭ
	for (int i = 0; i < M; i++) {
		*(Table + i) = 0;
	}
	scanf("%d", &n);

	while (1) {
		scanf("%c", &com);

		if (com == 'i') {
			scanf("%d", &key);
			insertItem(key);
			getchar();
		}
		else if (com == 's') {
			scanf("%d", &key);
			searchItem(key);
		}
		else if (com == 'e') {
			break;

		}

	}
	//�޸�����
	free(Table);

}