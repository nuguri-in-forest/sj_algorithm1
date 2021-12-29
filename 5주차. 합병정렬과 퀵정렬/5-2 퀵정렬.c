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

	//�ǹ� ���� �� �����
	int p = arr[k];

	int temp = arr[k];
	arr[k] = arr[r];
	arr[r] = temp;

	int i = l;
	int j = r - 1;

	//������������ ����
	//LT�� GT�� ����
	while (i <= j) {

		//left���� ū �� ã��
		//���� p���� ū�� LT������ ������
		// i�� �ű⼭ STOP
		while (i <= j && arr[i] <= p) {
			i++;
		}
		//right���� ���� �� ã��
		//���� p���� ������ GT������ ������
		// j�� �ű⼭ stop
		while (i <= j && arr[j] >= p) {
			j--;
		}

		if (i < j) {
			//swap 
			//�Ǻ��������� LT,GT �׷����� �Ű��ִ� ��
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//�ǹ��� ������ �������Ƿ� �ٽ� ������
	temp = arr[i];
	arr[i] = arr[r];
	arr[r] = temp;
	//�ε��� i�� �������� 
	// 0 ~ i-1 ==> LT
	// i+1 ~ j ==> GT �� ���ҵ� ����
	res.a = i;
	j = r - 1;
	//����� �ǹ��� �����ͼ� �ε��� i�� �����ϰ�
	// EQ������ ���Ѵ�
	while ((i + 1) <= j && arr[i + 1] == p) {
		i++;
	}
	res.b = i;
	return res;

}

void inPlaceQuickSort(int* arr, int l, int r) {
	if (l >= r) return;
	IDX res;
	//����
	int k = findPivot(l, r);
	res = inPlacePartition(arr, l, r, k);
	//���
	inPlaceQuickSort(arr, l, (res.a) - 1);
	inPlaceQuickSort(arr, (res.b) + 1, r);
	//��ġ
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

int findPivot(int *arr, int l, int r);// ��
void inPlacePartition(int *arr, int l, int r, int k, int *arr2); // ��
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
    for(index=i;index<=j;index++){ // i�� �Ǻ��� ������ ��ġ, j�� �Ǻ����� ū ���� �ִ� �� �� ������ �ε���
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