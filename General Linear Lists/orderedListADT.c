#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool retrieve(LIST* pList, void* pKey, void** pDataOut)
{
	NODE* pPre;
	NODE* pCur;

	if (_search(pList, &pPre, &pCur, pKey))
	{
		*pDataOut = pCur->pData;
		return true;
	}
	else
	{
		*pDataOut = NULL;
		return false;
	}
}

static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pKey)
{
#define COMPARE (((*pList->compare)(pKey, (*pLoc)->pData)))
#define COMPARE_LAST ((*pList->compare) (pKey, pList->rear->pData))

	int result;
	*pPre = NULL;
	*pLoc = pList->head;
	if (pList->size == 0)
		return false;

	if (COMPARE_LAST > 0)
	{
		*pPre = pList->rear;
		*pLoc = NULL;
		return false;
	}

	while ((result = COMPARE) > 0)
	{
		*pPre = *pLoc;
		*pLoc = (*pLoc)->next;
	}

	if (result == 0)
		return true;
	else
		return false;
}
LIST* createList(int(*compare)(void* pArg1, void* pArg2)) {
	LIST* list = (LIST*)malloc(sizeof(LIST));

	if (list == NULL) {
		return NULL;
	}

	list->size = 0;
	list->pos = list->head = list->rear = NULL;
	list->compare = compare;

	return list;
}

LIST* destroyList(LIST* pList) {
	NODE* pPre;
	for (pList->pos = pList->head; pList->pos != NULL;) {
		pPre = pList->pos;
		pList->pos = pList->pos->next;
		free((STUDENT*)pPre->pData);
		free(pPre);
	}
	free(pList);
	return NULL;
}

bool insert(LIST* pList, void* pDataIn) {
	NODE* pLoc=NULL, * pPre=NULL;
	if (_search(pList, &pPre, &pLoc, pDataIn)) {
		return false;
	}
	else {
		_insert(pList, pPre, pDataIn);
		return true;
	}
}

bool delete(LIST* pList, void* pKey) {
	NODE* pPre, * pLoc;
	if (_search(pList, &pPre, &pLoc, pKey)) {
		_delete(pList, pPre, pLoc);
		return true; 
	}
	
	return false;
}

int size(LIST* pList) {
	return pList->size;
}

bool isEmpty(LIST* pList) {
	if (pList->size == 0)
		return true;
	return false;
}

bool iterate(LIST* pList, void** pDataOut) {
	if (pList->pos == NULL) {
		pList->pos = pList->head;
	}
	else {
		pList->pos = pList->pos->next;
	}
	if (pList->pos != NULL) {
		*pDataOut = pList->pos->pData;
		return true;
	}
	else {
		*pDataOut = 0;
		return false;
	}
}

void initIterator(LIST* pList) {
	pList->pos = pList->head;
}

void printList(LIST* pList, void(*print)(void* pArg)) {
	for (pList->pos=pList->head; pList->pos != NULL; pList->pos = pList->pos->next) {
		print(pList->pos->pData);
	}
}

void printStudent(void* pArg) {
	printf("STUDENT ID: %d\n", (((STUDENT*)pArg)->id));
	printf("NAME: %s\n", (((STUDENT*)pArg)->name));
	printf("EMAIL: %s\n", (((STUDENT*)pArg)->email));
	printf("--------------------\n");
}

int cmpStudentId(void* pStudent1, void* pStudent2) {
	return ((STUDENT*)pStudent1)->id - ((STUDENT*)pStudent2)->id;
}

static bool _insert(LIST* pList, NODE* pPre, void* pDataIn) {
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	pNewNode->pData = (STUDENT*)pDataIn;

	if (pPre == NULL) {
		pNewNode->next = pList->head;
		pList->head = pNewNode;
		pList->rear = pNewNode;
	}
	else if (pPre->next == NULL) {
		pPre->next = pNewNode;
		pList->rear = pNewNode;
		pNewNode->next = NULL;
	}
	else {
		pNewNode->next = pPre->next;
		pPre->next = pNewNode;
	}
	pList->size++;
}
static void _delete(LIST* pList, NODE* pPre, NODE* pCur) {
	if (pPre == NULL) {
		pList->head = pCur->next;
	}
	else if (pCur == pList->rear) {
		pList->rear = pPre;
		pPre->next = NULL;
	}
	else {
		pPre->next = pCur->next;
	}
	free(pCur->pData);
	free(pCur);
	pList->size--;
}