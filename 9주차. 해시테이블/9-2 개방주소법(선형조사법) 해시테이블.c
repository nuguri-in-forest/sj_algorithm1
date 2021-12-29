#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

int* Table;
int M;

// h(x) = x % M
// 개방주소법 해시테이블
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
		//이동한 버켓이 empty라면
		if (Table[idx] == 0) {
			//삽입
			Table[idx] = x;
			//충돌횟수만큼 C 출력
			for (int j = 0; j < i; j++) {
				printf("C");
			}
			//삽입한 주소 인덱스 출력
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
	//M크기의 배열로 해시테이블 동적할당
	Table = (int*)malloc(sizeof(int) * M);

	//테이블 초기화
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
	//메모리해제
	free(Table);

}