#include "HeapADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Heap* heapCreate(int size) {
	Heap* pHeap = NULL;
	pHeap = (Heap*)malloc(sizeof(Heap));

	if (pHeap == NULL)
		return NULL;

	pHeap->size = 0;
	pHeap->maxSize = size;
	pHeap->heapAry = (int*)malloc(sizeof(int) * pHeap->maxSize);

	return pHeap;
}

int reheapUp(Heap* pHeap, int index) {
	if (index <= 0 || index > pHeap->size)
		return 0;

	int parentIndex = (index - 1) / 2;
	if (pHeap->heapAry[index] > pHeap->heapAry[parentIndex]) {
		int temp = pHeap->heapAry[index];
		pHeap->heapAry[index] = pHeap->heapAry[parentIndex];
		pHeap->heapAry[parentIndex] = temp;
		reheapUp(pHeap, parentIndex);
	}
	return 1;
}


void heapInsert(Heap* pHeap, int data) {
	if (pHeap->size >= pHeap->maxSize) {
		printf("Heap is full\n");
		return;
	}

	pHeap->heapAry[pHeap->size++] = data;
	reheapUp(pHeap, pHeap->size - 1);
}


void reheapDown(Heap* pHeap, int index) {
	if (index<0 || index>pHeap->size)
		return;

	if (index * 2 + 1 < pHeap->size) {
		int maxChild = index * 2 + 1;
		if (maxChild + 1 < pHeap->size && pHeap->heapAry[maxChild + 1] > pHeap->heapAry[maxChild])
			maxChild++;

		if (pHeap->heapAry[maxChild] > pHeap->heapAry[index]) {
			int temp = pHeap->heapAry[index];
			pHeap->heapAry[index] = pHeap->heapAry[maxChild];
			pHeap->heapAry[maxChild] = temp;
			reheapDown(pHeap, maxChild);
		}
	}
}

int heapDelete(Heap* pHeap) {
	if (pHeap->size <= 0) {
		printf("Heap is empty\n");
	}

	int pDataOut = pHeap->heapAry[0];
	pHeap->heapAry[0] = pHeap->heapAry[--pHeap->size];
	reheapDown(pHeap, 0);

	return pDataOut;
}



int heapCount(Heap* pHeap) {
	return pHeap->size;
}

bool heapFull(Heap* pHeap) {
	return pHeap->size == pHeap->maxSize ? true : false;
}

bool heapEmpty(Heap* pHeap) {
	return pHeap->size == 0 ? true : false;
}

void heapDestroy(Heap* pHeap) {
	free(pHeap->heapAry);
	free(pHeap);
}

int* heapSort(Heap* pHeap) {
	int* sorted = (int*)malloc(sizeof(int) * pHeap->size);
	int size = pHeap->size;

	for (int i = pHeap->size/2; i >= 0; i--) {
		reheapUp(pHeap, i);
	}

	for (int i = 0; i < size; i++) {
		sorted[i] = heapDelete(pHeap);
	}

	return sorted;
}