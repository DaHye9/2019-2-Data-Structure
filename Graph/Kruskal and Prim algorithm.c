#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int map[10][10] = {{0, 6, 0, 3, 0, 9, 0, 0, 0, 0},
					 {6, 0, 2, 4, 0, 0, 9, 0, 0, 0},
					 { 0, 2, 0, 2, 8, 0, 9, 0, 0, 0 },
					 { 3, 4, 2, 0, 9, 9, 0, 0, 0, 0 },
					 { 0, 0, 8, 9, 0, 8, 7, 9, 0,10 },
					 { 9, 0, 0, 9, 8, 0, 0, 0, 0,18 },
					 { 0, 9, 9, 0, 7, 0, 0, 5, 4, 0 },
					 { 0, 0, 0, 0, 9, 0, 5, 0, 1, 3 },
					 { 0, 0, 0, 0, 0, 0, 4, 1, 0, 4 },
					 { 0, 0, 0, 0,10,18, 0, 3, 4, 0 }};

//Kruskal's algorithm

typedef struct edge {
	int num;
	int connected;
	int weight;
}edge;

typedef struct list {
	edge data[100];
	int n;
} edgeList;

edgeList edgelist;
int graph1[10][10] = { 0 };
int sum = 0;

void sort_edgelist() {
	edge temp;

	for (int i = 0; i < edgelist.n; i++) {
		for (int k = 0; k < edgelist.n - i - 1; k++) {
			if (edgelist.data[k].weight > edgelist.data[k + 1].weight) {
				temp = edgelist.data[k + 1];
				edgelist.data[k + 1] = edgelist.data[k];
				edgelist.data[k] = temp;
			}
		}
	}
}

int getParent(int relation[], int a) {
	if (relation[a] == a) return a;
	else return relation[a] = getParent(relation, relation[a]);
}


bool isSameParent(int relation[], int a, int b) {
	if (getParent(relation, a) == getParent(relation, b)) return true;
	return false;
}

void kruskal() {
	int relation[10];//부모노드 확인
	for (int i = 0; i < 10; i++) {
		relation[i] = i;
	}

	edgelist.n = 0;
	for (int i = 0; i < 10; i++) {
		for (int k = i + 1; k < 10; k++) {
			if (map[i][k] != 0) {
				edgelist.data[edgelist.n].num = i;
				edgelist.data[edgelist.n].connected = k;
				edgelist.data[edgelist.n++].weight = map[i][k];
			}
		} // 노드에 넣기
	}

	sort_edgelist();  // 가중치 기준으로 edge 정렬

	for (int i = 0; i < edgelist.n; i++) {
		int num = edgelist.data[i].num;
		int connected = edgelist.data[i].connected;
		if (!isSameParent(relation, num, connected)) {//연결된게 같은 부모가 아닐 대
			int a = getParent(relation, num);
			int b = getParent(relation, connected);
			if (a < b) {
				relation[connected] = a;
				for (int i = 0; i < 10; i++) { // 연결된 노드들 parent union
					if (relation[i] == b) {
						relation[i] = a;
					}
				}
			}
			else {
				relation[num] = b;
				for (int i = 0; i < 10; i++) {
					if (relation[i] == a) {
						relation[i] = b;
					}
				}
			}
			graph1[num][connected] = 1;
			graph1[connected][num] = 1;

			sum += edgelist.data[i].weight;
		}
	}
}

//Prim's algorithm

int graph2[10][10] = { 0 };
int sum2 = 0;

void change(int distance[][10], bool visited[], int key) {
	for (int i = 0; i < 10; i++) {
		if (map[key][i] != 0 && visited[i] == false && distance[0][i] > map[key][i]) {
			distance[0][i] = map[key][i];
			distance[1][i] = key;
		}
	}
}

int find_min(int distance[][10], bool visited[]) {
	int min_distance = 999;
	int min;

	for (int i = 0; i < 10; i++) {
		if (visited[i] == false && distance[0][i] < min_distance) {
			min_distance = distance[0][i];
			min = i;
		}
	}

	visited[min] = true;
	return min;
}

void prim() {
	int distance[2][10];
	for (int i = 0; i < 10; i++) {
		distance[0][i] = 99;
		distance[1][i] = i;
	}
	distance[0][0] = 0;
	bool visited[10] = { false };

	change(distance, visited, 0);
	for (int i = 0; i < 9; i++) {
		int min = find_min(distance, visited);
		change(distance, visited, min);
	}

	for (int i = 1; i < 10; i++) {
		sum2 += distance[0][i];
		graph2[i][distance[1][i]] = 1;
		graph2[distance[1][i]][i] = 1;
	}
 }


int main() {
	kruskal();
	
	for (int i = 0; i < 10; i++) {
		for (int k = 0; k < 10; k++) {
			printf("%d ", graph1[i][k]);
		}
		printf("\n");
	}

	printf("Kruskal sum : %d\n\n", sum);

	prim();

	for (int i = 0; i < 10; i++) {
		for (int k = 0; k < 10; k++) {
			printf("%d ", graph2[i][k]);
		}
		printf("\n");
	}

	printf("Prim sum : %d", sum2);

	return 0;
}