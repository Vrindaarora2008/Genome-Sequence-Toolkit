#include <stdio.h>
#include <limits.h>
#include "greedy.h"
void prim_mst(
    int graph[MAX_VERTICES][MAX_VERTICES],
    int n)
{
    if (graph == NULL || n <= 0 || n > MAX_VERTICES) {
        printf("Invalid input.\n");
        return;
    }
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int included[MAX_VERTICES] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] < 0) {
                printf("Negative edge weights are not supported.\n");
                return;
            }
        }
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[0] = 0;
    for (int count = 0; count < n; count++) {
        int minimum = INT_MAX;
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!included[v] && key[v] < minimum) {
                minimum = key[v];
                u = v;
            }
        }
        if (u == -1) {
            printf("Graph is disconnected. No spanning tree exists.\n");
            return;
        }
        included[u] = 1;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 && !included[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    int total = 0;
    printf("\nPRIM MINIMUM SPANNING TREE\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d : %d\n", parent[i], i, key[i]);
        total += key[i];
    }
    printf("Total MST weight: %d\n", total);
}