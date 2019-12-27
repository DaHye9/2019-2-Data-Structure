#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tHeap {
	int* heapAry;
	int maxSize;
	int size;
}Heap;

Heap* heapCreate(int size);
void heapInsert(Heap* pHeap, int data);
int reheapUp(Heap* pHeap, int index);
int heapDelete(Heap* pHeap);
int heapCount(Heap* pHeap);
bool heapFull(Heap* pHeap);
bool heapEmpty(Heap* pHeap);
void heapDestroy(Heap* pHeap);
int* heapSort(Heap* pHeap);