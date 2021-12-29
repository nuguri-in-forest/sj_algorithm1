#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct idx {
	int a;
	int b;
}IDX;
int findPivot(int l, int r) {
	int k;
	srand(time(NULL));
	k = rand() % (r - l + 1) + l;
	return k;
}
IDX inPlacePartition(int* arr, int l, int r, int k) {
	IDX res;

	//피벗 설정 및 숨기기
	int p = arr[k];

	int temp = arr[k];
	arr[k] = arr[r];
	arr[r] = temp;

	int i = l;
	int j = r - 1;

	//엇갈릴때까지 분할
	//LT와 GT로 분할
	while (i <= j) {

		//left에서 큰 것 찾기
		//만약 p보다 큰게 LT구간에 있으면
		// i는 거기서 STOP
		while (i <= j && arr[i] <= p) {
			i++;
		}
		//right에서 작은 것 찾기
		//만약 p보다 작은게 GT구간에 있으면
		// j는 거기서 stop
		while (i <= j && arr[j] >= p) {
			j--;
		}

		if (i < j) {
			//swap 
			//피봇기준으로 LT,GT 그룹으로 옮겨주는 것
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//피벗의 역할이 끝났으므로 다시 가져옴
	temp = arr[i];
	arr[i] = arr[r];
	arr[r] = temp;
	//인덱스 i를 기준으로 
	// 0 ~ i-1 ==> LT
	// i+1 ~ j ==> GT 로 분할된 상태
	res.a = i;
	j = r - 1;
	//사용한 피벗을 가져와서 인덱스 i에 저장하고
	// EQ구간을 구한다
	while ((i + 1) <= j && arr[i + 1] == p) {
		i++;
	}
	res.b = i;
	return res;

}

void inPlaceQuickSort(int* arr, int l, int r) {
	if (l >= r) return;
	IDX res;
	//분할
	int k = findPivot(l, r);
	res = inPlacePartition(arr, l, r, k);
	//재귀
	inPlaceQuickSort(arr, l, (res.a) - 1);
	inPlaceQuickSort(arr, (res.b) + 1, r);
	//통치
}
int main() {
	int n;
	scanf("%d", &n);
	int* arr = malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	inPlaceQuickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int *arr, int l, int r);// 완
void inPlacePartition(int *arr, int l, int r, int k, int *arr2); // 완
void inPlaceQuickSort(int* arr,int l, int r);

int main(){
    int size, *arr, i, k, arr2[2];
    scanf("%d", &size);
    arr = (int*)malloc(sizeof(int)*size);
    for(i=0;i<size;i++)
        scanf("%d",&arr[i]);
    k = findPivot(arr, 0, size-1);
    inPlaceQuickSort(arr, 0, size-1);
    for(i=0;i<size;i++)
        printf(" %d",arr[i]);
    free(arr);
}

void inPlaceQuickSort(int* arr,int l, int r){
    int k, arr2[2];
    if(l>=r)
        return;
    k = findPivot(arr, l, r);
    inPlacePartition(arr, l, r, k, arr2); //
    inPlaceQuickSort(arr, l, arr2[0]-1);
    inPlaceQuickSort(arr, arr2[1]+1, r);
}



void inPlacePartition(int *arr, int l, int r, int k, int* arr2){
    int pivot, swap, i, j, index, index2, a, b;
    pivot = arr[k];
    j=r;
    for(index=l; index<=r;index++){
        if(arr[index]==pivot){
            for(index2=j;index2>=l;index2--){
                if(arr[index2]!=pivot&&index<index2){
                    swap = arr[index2];
                    arr[index2] = arr[index];
                    arr[index] = swap;
                    j = index2-1;
                    break;
                }
            }
        }
    }
    for(index=l; index<=r; index++){
        if(pivot==arr[index]){
            j = index-1;
            break;
        }
    }
    //printf("infront pivot: %d\n",j);
    i = l;
    while(i<=j){
        while(arr[i]<=pivot&&i<=j)
            i = i + 1;
        while(i<=j&&arr[j]>=pivot)
            j = j - 1;
        if(i<j){
            swap = arr[i];
            arr[i] = arr[j];
            arr[j] = swap;
        }
    }
    //printf("pivot last swap index: %d\n",i);
    for(index=l; index<=r; index++){
        if(pivot==arr[index]){
            j = index-1;
            break;
        }
    }
    //printf("infront pivot: %d\n",j);
    index2 = r;
    for(index=i;index<=j;index++){ // i는 피봇이 가야할 위치, j는 피봇보다 큰 값이 있는 것 중 마지막 인덱스
        swap = arr[index];
        arr[index] = arr[index2];
        arr[index2] = swap;
        index2 --;
    }
    for(index=l;index<=r;index++){
        if(arr[index]==pivot){
            a = index;
            break;
        }
    }
    for(index=r;index>=l;index--){
        if(arr[index]==pivot){
            b = index;
            break;
        }
    }
    arr2[0] = a;
    arr2[1] = b;
}

int findPivot(int *arr, int l, int r){
    int k;
    srand(time(NULL));
    k = rand()%(r-l+1)+l;
    return k;
}
*/