#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef _MSC_VER
// Windows
#include <Windows.h>
#endif

#define N 10000
#define MAX_VALUE 10000


void runSearch(void* pList, const size_t size, const int target, int* pLoc, bool (*searchFunc)(void*, const size_t, const int, int*))
{
	LARGE_INTEGER freq;
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&beginTime);
	bool result = searchFunc(pList, size, target, pLoc);
	QueryPerformanceCounter(&endTime);

	double duringTime = (double)(endTime.QuadPart - beginTime.QuadPart) / (double)freq.QuadPart;

	printf("Execution time: %.10lf ms\n", duringTime * 10e3);
	if (result)
		printf("Found %d at %d\n", target, *pLoc);
	else
		printf("Cannot found %d\n", target);
}

bool seqSearch(void** pList, const size_t size, const int target, int* pLoc)
{
	unsigned int i = 0;
	int* arr = (int*)pList;
	while (i < size && arr[i] != target)
	{
		i++;
	}
	*pLoc = i;

	return (arr[i] == target);
}

int getRand()
{
	return rand() % MAX_VALUE;
}

void buildHash(void* pList, size_t listSize, void* pHash, size_t* hashSize)
{

	*hashSize = 1999;
	int* add = (int*)pList;
	int H[N] = { 0 };
	for (int i = 0; i < listSize; i++) {
		int hash = add[i] % *hashSize;
		while(H[hash]!=0) {
			hash++;
			if (hash >= N) 
				hash = hash % N;
		}
		((int*)pHash)[i] = add[i];
	}
}

bool hashSearch(void* pHash, const size_t size, const int target, int* pLoc)
{
	int* H = (int*)pHash;
	int new_target = target % size;
	int count = 0;
	if (((int*)pHash)[new_target] == target) {
		*pLoc = new_target;
		return true;
	}
	while (((int*)pHash)[new_target] != 0) {
		new_target++;
		if(new_target==N)
			new_target %= N;
		if (((int*)pHash)[new_target] == target) {
			return true;
			break;
		}
	}
	return false;
}

void deleteHash(void* pHash, const size_t size)
{
	free(pHash);
}

int main()
{
	static int arr[N] = { 0 };

	srand(2019);
	for (int i = 0; i < N; i++)
	{
		arr[i] = getRand();
	}

	int target = getRand();
	int loc = -1;

	size_t hashSize = 0;
	// Make pHash
	int* pHash = (int*)malloc(sizeof(int)*N);

	buildHash(arr, N, pHash, &hashSize);

	runSearch(arr, N, target, &loc, seqSearch);

	runSearch(pHash, hashSize, target, &loc, hashSearch);

	deleteHash(pHash, hashSize);

	return 0;
}