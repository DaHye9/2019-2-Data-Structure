#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tQueueNode {
	int data;
	struct tQueueNode* next;
}QueueNode;

typedef struct {
	int count, size;
	QueueNode* front, * rear;
}Queue;

Queue* CreateQueue(int size) {
	Queue* pNewQueue = (Queue*)malloc(sizeof(Queue));
	if (pNewQueue == NULL)
		return NULL;
	pNewQueue->front = pNewQueue->rear = NULL;
	pNewQueue->count = 0;
	pNewQueue->size = size;
	return pNewQueue;
}
int IsFullQueue(Queue* q) {
	if (q->size==q->count)
		return 1;
	else
		return 0;
}

int IsEmptyQueue(Queue* q)
{
	if (!q->count)
		return 1;
	else
		return 0;
}

void enqueue(Queue* pQueue, int item) {
	QueueNode* pNewNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (pNewNode == NULL)
		return;
	pNewNode->data = item;
	pNewNode->next = NULL;
	if (pQueue->count <= 0) {
		pQueue->front = pQueue->rear = pNewNode;
	}
	else {
		pQueue->rear->next = pNewNode;
		pQueue->rear = pNewNode;
	}
	pQueue->count++;
}

int dequeue(Queue* pQueue) {
	QueueNode* pFront = NULL;
	int item = 0;
	if (pQueue->count <= 0)
		return 0;
	pFront = pQueue->front;
	item = pFront->data;
	if (pQueue->count == 1) {
		pQueue->front = pQueue->rear = NULL;
	}
	else {
		pQueue->front = pFront->next;
	}
	free(pFront);
	pQueue->count--;
	return item;
}

int queueFront(Queue* pQueue) {
	if (pQueue->count <= 0) {
		return INT_MIN;
	}
	return pQueue->front->data;
}

int queueCount(Queue* pQueue) {
	return pQueue->count;
}

void destroyQueue(Queue* pQueue) {
	QueueNode* pCur = NULL, * pNext = NULL;

	for (pCur = pQueue->front; pQueue->count > 0; pQueue->count--, pCur = pNext) {
		pNext = pCur->next;
		free(pCur);
	}
	pQueue->front = pQueue->rear = NULL;
	free(pQueue);
}


int main() {
	int customer_num;
	printf("number of customer : ");
	scanf("%d", &customer_num);
	Queue* patience = CreateQueue(customer_num);
	for (int i = 0; i < customer_num; i++) {
		int temp_patience;
		printf("Patience of customer : ");
		scanf("%d", &temp_patience);
		enqueue(patience, temp_patience);
	}
	int sold_hotdogs = 0, time=0;
	while (1) {
		dequeue(patience);
		sold_hotdogs++;

		QueueNode* prev, *curr;
		
		while (!IsEmptyQueue(patience) && patience->front->data - time == 0) {
			dequeue(patience);
		}
		if (IsEmptyQueue(patience))
			break;
		for (prev = patience->front, curr = patience->front->next; curr != NULL;) {
			if (curr->data - time == 0) {
				prev->next = curr->next;
				free(curr);
				curr = prev->next;
				patience->count--;
			}
			else {
				prev = prev->next;
				curr = curr->next;
			}
		}
		time++;
	}
	destroyQueue(patience);
	printf("I sell %d hotdogs", sold_hotdogs);
	return 0;
}