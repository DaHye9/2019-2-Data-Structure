#include <stdio.h>
#include <stdlib.h>
#define	N	10

void printArr(int arr[], const size_t size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void merge(int arr[], int low, int mid, int high)
{
	int sorted[N] = { 0 };
	int l = low, sort_num = low;
	int m = mid + 1;
	while (l <= mid && m <= high) {
		if (arr[l] < arr[m]) {
			sorted[sort_num++] = arr[l++];
		}
		else {
			sorted[sort_num++] = arr[m++];
		}
	}
	if (l > mid) { // 작은 배열 쪽이 끝남
		for (; m <= high; m++) {
			sorted[sort_num++] = arr[m];
		}
	}
	else {
		for (; l <= mid; l++) {
			sorted[sort_num++] = arr[l];
		}
	}
	while (low <= high) {
		arr[low] = sorted[low];
		low++;
	}
}

void mergeSort(int arr[], int low, int high)
{
	if (low < high) {
		int mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

int main()
{
	int values[N] = { 1,0,6,7,3, 9,6,6,2,8 };

	printArr(values, N);

	mergeSort(values, 0, N - 1);

	printArr(values, N);

	return 0;
}
