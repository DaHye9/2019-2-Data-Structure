#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph{
	int count;
	struct vertex* first;
	int (*compare)(void* argu1, void* argu2);
}graph;

typedef struct vertex {
	struct vertex* pNextVertex;
	void* dataPtr;
	int inDegree;
	int outDegree;
	bool processed;
	struct arc* pArc;
}vertex;

typedef struct arc {
	struct vertex* destination;
	struct arc* pNextArc;
	int weight;
}arc;

graph* graphCreate(int (*compare)(void* argu1, void* argu2)) {
	graph* pGraph = (graph*)malloc(sizeof(graph));

	if (pGraph == NULL)
		return NULL;

	pGraph->count = 0;
	pGraph->first = NULL;
	pGraph->compare = compare;

	return pGraph;
}

int graphInsertVertex(graph* graph, void* dataInPtr) {
	vertex* newPtr = (vertex*)malloc(sizeof(vertex));
	vertex* pre = NULL, * loc = NULL;

	if (newPtr == NULL)
		return -1;

	newPtr->dataPtr = dataInPtr;
	newPtr->inDegree = 0;
	newPtr->outDegree = 0;
	newPtr->pArc = NULL;
	newPtr->pNextVertex = NULL;
	newPtr->processed = 0;

	graph->count++;

	if ((loc = graph->first) == NULL) {
		graph->first = newPtr;
	}
	else {
		while (loc && (graph->compare)(dataInPtr, loc->dataPtr) > 0) {
			pre = loc;
			loc = loc->pNextVertex;
		}

		if (pre == NULL)
			graph->first = newPtr;
		else 
			pre->pNextVertex = newPtr;
		
		newPtr->pNextVertex = loc;
	}
	
	return 1;
}

int _insert(graph* pGraph, void* from, void* to, int weight) {
	arc* newPtr = (arc*)malloc(sizeof(arc));
	arc* aPre = NULL, * aLoc = NULL;
	vertex* vPre = NULL, * vTo = NULL;

	vTo = vPre = pGraph->first;

	while (vPre && (pGraph->compare)(from, vPre->dataPtr) > 0)
		vPre = vPre->pNextVertex;

	if (!vPre || pGraph->compare(from, vPre->dataPtr) != 0)
		return -2; //no from vertex

	while (vTo && (pGraph->compare)(to, vTo->dataPtr) > 0)
		vTo = vTo->pNextVertex;

	if (!vTo || pGraph->compare(to, vTo->dataPtr) != 0)
		return -3; //no to vertex

	if (newPtr == NULL)
		return -1;
	++(vPre->outDegree);
	++(vTo->inDegree);
	newPtr->destination = vTo;
	newPtr->weight = weight;
	newPtr->pNextArc = NULL;

	if (vPre->pArc == NULL) {
		vPre->pArc = newPtr;
		newPtr->pNextArc = NULL;
		return 1;
	}

	aLoc = vPre->pArc;

	while (aLoc && pGraph->compare(to, aLoc->destination->dataPtr) >= 0) {
		aPre = aLoc;
		aLoc = aLoc->pNextArc;
	}

	if (aPre == NULL)
		vPre->pArc = newPtr;
	else
		aPre->pNextArc = newPtr;
	newPtr->pNextArc = aLoc;
	return 1;
}

int graphInsertArc(graph* pGraph, void* from, void* to, int weight) {
	if (_insert(pGraph, from, to, weight) < 0)
		return -1;
	if (_insert(pGraph, to, from, weight) < 0)
		return -1;

	/*++vPre->outDegree;
	++vTo->inDegree;
	newPtr->destination = vTo;

	if (vPre->pArc == NULL) {
		vPre->pArc = newPtr;
		newPtr->pNextArc = NULL;
		return 1;
	}
	
	aLoc = vPre->pArc;

	while (aLoc && pGraph->compare(to, aLoc->destination->dataPtr) >= 0) {
		aPre = aLoc;
		aLoc = aLoc->pNextArc;
	}

	if (aPre == NULL)
		vPre->pArc = newPtr;
	else
		aPre->pNextArc = newPtr;
	newPtr->pNextArc = aLoc;
	return 1;
	*/
}

int graphRemoveVertex(graph* pGraph, void* deleteKey) {
	vertex* vLoc = pGraph->first;
	vertex* vPre = NULL;

	if (vLoc == NULL)
		return -1;

	while (vLoc && pGraph->compare(deleteKey, vLoc->dataPtr) > 0) {
		vPre = vLoc;
		vLoc = vLoc->pNextVertex;
	}

	if (!vLoc || pGraph->compare(deleteKey, vLoc->dataPtr) != 0) {
		return -1;
	}
	
	if (vLoc->inDegree > 0 || vLoc->outDegree > 0)
		return -1;

	if (vPre == NULL)
		pGraph->first = vLoc->pNextVertex;
	else {
		vPre->pNextVertex = vLoc->pNextVertex;
	}

	--pGraph->count;
	return 1;
}

int _remove(graph* pGraph, void* from, void* to) {
	vertex* vPre = pGraph->first, *vLoc = NULL;
	arc* aPre = NULL, * aLoc = NULL;

	if (vPre == NULL)
		return -1;

	while (vPre && pGraph->compare(from, vPre->dataPtr) > 0) {
		vPre = vPre->pNextVertex;
	}

	if (!vPre || pGraph->compare(from, vPre->dataPtr) != 0) {
		return -1;
	}

	if (vPre->pArc == NULL)
		return -1;

	aLoc = vPre->pArc;

	while (aLoc && pGraph->compare(to, aLoc->destination->dataPtr)) {
		aPre = aLoc;
		aLoc = aLoc->pNextArc;
	}

	if (!aLoc || pGraph->compare(to, aLoc->destination->dataPtr) != 0)
		return -1;

	vLoc = aLoc->destination;
	--vPre->outDegree;
	--vLoc->inDegree;

	if (!aPre)
		vPre->pArc = aLoc->pNextArc;
	else
		aPre->pNextArc = aLoc->pNextArc;

	free(aLoc);

	return 1;

}

int graphRemoveArc(graph* pGraph, void* from, void* to) {
	if (_remove(pGraph, from, to) < 0)
		return -1;
	if (_remove(pGraph, to, from) < 0)
		return -1;

	return 1;
}

void graphDestroy(graph* pGraph) {
	if (pGraph == NULL)
		return;

	vertex* vDel = NULL, * vLoc = pGraph->first;
	arc* aDel = NULL, * aLoc = NULL;

	while (vLoc != NULL) {
		aLoc = vLoc->pArc;
		while (aLoc != NULL) {
			aDel = aLoc;
			aLoc = aLoc->pNextArc;
			free(aDel);
		}
		vDel = vLoc;
		free(vDel->dataPtr);
		vLoc = vLoc->pNextVertex;
		free(vDel);
	}

	free(pGraph);
}

int compare(int* a, int* b) {
	return *a - *b;
}

void traverse(graph* pGraph) {
	vertex* vLoc = pGraph->first;
	arc* aLoc = vLoc->pArc;

	while (vLoc != NULL) {
		aLoc = vLoc->pArc;
		printf("vertex : %d, %d\n", *(int*)(vLoc->dataPtr), vLoc->inDegree);
		while (aLoc != NULL) {
			printf("arc : %d weight : %d\n", *(int*)aLoc->destination->dataPtr, aLoc->weight);
			aLoc = aLoc->pNextArc;
		}
		vLoc = vLoc->pNextVertex;
		
	}
	printf("\n");
}

graph* MST(graph* pGraph) {
	graph* result = (graph*)malloc(sizeof(graph));
	result->compare = pGraph->compare;
	result->count = 0;
	result->first = NULL;
	vertex* vLoc = pGraph->first;
	arc* aLoc = NULL;
	int count = pGraph->count;
	int* visited = (int*)malloc(sizeof(int) * count);
	int** distance = (int**)malloc(sizeof(int*) * 2);

	for (int i = 0; i < 2; i++) distance[i] = (int*)malloc(sizeof(int) * count);
	for (int i = 0; i < count; i++) {
		visited[i] = 0;
		distance[0][i] = 99;
		distance[1][i] = i;
		int* data = (int*)malloc(sizeof(int));
		*data = *(int*)vLoc->dataPtr;
		graphInsertVertex(result, data);
		vLoc = vLoc->pNextVertex;
	}

	visited[0] = 1;

	for (int i = 0; i < count - 1; i++) {
		for (int j = 1; j < count; j++) {
			vLoc = pGraph->first;
			if (visited[j] == false) {//찾을 arc
				for (int k = 0; k < count; k++) {//찾을 vertex
					if (visited[k] == true) {
						int* a = (int*)malloc(sizeof(int));
						*a = k;
						while (vLoc && pGraph->compare(a, vLoc->dataPtr) > 0) {
							vLoc = vLoc->pNextVertex;
						}
						if (!vLoc || pGraph->compare(a, vLoc->dataPtr) != 0)
							return NULL;

						*a = j;
						aLoc = vLoc->pArc;

						while (aLoc && pGraph->compare(a, aLoc->destination->dataPtr) > 0) {
							aLoc = aLoc->pNextArc;
						}
						if (!aLoc || pGraph->compare(a, aLoc->destination->dataPtr) != 0) {
							free(a);
							continue;
						}

						if (aLoc->weight < distance[0][j]) {
							distance[0][j] = aLoc->weight;
							distance[1][j] = k;
						}

						free(a);
					}
				}

			}
		}
		int min = 0; int min_distance = distance[0][0];
		for (int k = 0; k < count; k++) {

			if (visited[k] == false && distance[0][k] < min_distance) {
				min_distance = distance[0][k];
				min = k;
			}
		}
		visited[min] = true;
		int* from = (int*)malloc(sizeof(int));
		int* to = (int*)malloc(sizeof(int));

		*from = min;
		*to = distance[1][min];
		graphInsertArc(result, from, to, min_distance);
		free(from); free(to);
	}
	return result;
}

int main() {
	graph* pGraph = graphCreate(compare);

	int* input = (int*)malloc(sizeof(int));
	*input = 0;
	graphInsertVertex(pGraph, input);
	traverse(pGraph);

	input = (int*)malloc(sizeof(int));
	*input = 3;
	graphInsertVertex(pGraph, input);
	traverse(pGraph);

	input = (int*)malloc(sizeof(int));
	*input = 2;
	graphInsertVertex(pGraph, input);
	traverse(pGraph);

	input = (int*)malloc(sizeof(int));
	*input = 1;
	graphInsertVertex(pGraph, input);
	traverse(pGraph);

	int* from = (int*)malloc(sizeof(int));
	int* to = (int*)malloc(sizeof(int));
	*from = 1; *to = 3;
	graphInsertArc(pGraph, from, to, 8);
	traverse(pGraph);

	from = (int*)malloc(sizeof(int));
	to = (int*)malloc(sizeof(int));
	*from = 2; *to = 1;
	graphInsertArc(pGraph, from, to, 2);
	traverse(pGraph);

	from = (int*)malloc(sizeof(int));
	to = (int*)malloc(sizeof(int));
	*from = 3; *to = 0;
	graphInsertArc(pGraph, from, to, 1);
	traverse(pGraph);

	from = (int*)malloc(sizeof(int));
	to = (int*)malloc(sizeof(int));
	*from = 0; *to = 1;
	graphInsertArc(pGraph, from, to, 5);
	traverse(pGraph);

	printf("result :\n");

	graph* result = MST(pGraph);
	traverse(result);
	
	graphDestroy(pGraph);
	graphDestroy(result);
}