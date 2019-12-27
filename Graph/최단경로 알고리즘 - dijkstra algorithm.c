#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int w[10][10] = {
{0, 6, 3, 0, 9, 0, 0, 0, 0, 0},
{6, 0, 4, 2, 0, 0, 0, 9, 0, 0},
{3, 4, 0, 2, 9, 9, 0, 0, 0, 0},
{0, 2, 2, 0, 0, 8, 0, 9, 0, 0},
{9, 0, 9, 0, 0, 8, 0, 0, 0, 18},
{0, 0, 9, 8, 8, 0, 9, 7, 0, 10},
{0, 0, 0, 0, 0, 9, 0, 5, 1, 3},
{0, 9, 0, 9, 0, 7, 5, 0, 4, 0},
{0, 0, 0, 0, 0, 0, 1, 4, 0, 4},
{0, 0, 0, 0, 18,10, 3, 0, 4, 0}
};

bool all_visited(int visited[]) {
	for (int i = 0; i < 10; i++) {
		if (visited[i] == 0)
			return false;
	}
	return true;
}

int main() {
	int result[10][10] = { 0 };
	int distance[10];
	int connected[10];
	for (int i = 0; i < 10; i++) {
		distance[i] = 99;
		connected[i] = i;
	}
	distance[0] = 0;
	int visited[10] = { false }; visited[0] = true;
	int recent_visited = 0;

	while (1) {
		for (int i = 1; i < 10; i++) { // distance °»½Å
			if (visited[i] == false && w[recent_visited][i] > 0) {
				if (distance[i] > (distance[recent_visited] + w[recent_visited][i])) {
					distance[i] = distance[recent_visited] + w[recent_visited][i];
					connected[i] = recent_visited;
				}
			}
		}
		int min, min_distance = 99;
		for (int i = 0; i < 10; i++) {
			if (visited[i] == false && min_distance > distance[i]) {
				min_distance = distance[i];
				min = i;
			}
		}
		visited[min] = true;
		recent_visited = min;

		if (all_visited(visited) == true)
			break;
	}

	for (int i = 0; i < 10; i++) {
		result[connected[i]][i] = result[i][connected[i]] = w[connected[i]][i];
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}

	printf("path : ");

	for (int i = 0; i < 10; i++)
		printf("%d ", distance[i]);

	return 0;
}