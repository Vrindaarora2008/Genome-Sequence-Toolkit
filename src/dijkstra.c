#include <stdio.h>
#include <limits.h>
#include "greedy.h"
static int minimum_distance(int distance[], int visited[], int n)
{
    int minimum = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && distance[i] < minimum) {
            minimum = distance[i];
            index = i;
        }
    }
    return index;
}
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int n, int source)
{
    if (graph == NULL || n <= 0 || n > MAX_VERTICES || source < 0 || source >= n) {
        printf("Invalid input.\n");
        return;
    }
    int distance[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] < 0) {
                printf("Negative edge weights are not supported.\n");
                return;
            }
        }
        distance[i] = INT_MAX;
    }
    distance[source] = 0;
    for (int count = 0; count < n - 1; count++) {
        int u = minimum_distance(distance, visited, n);
        if (u == -1) {
            break;
        }
        visited[u] = 1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] > 0 &&  distance[u] != INT_MAX && distance[u] <= INT_MAX - graph[u][v] && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }
    printf("\nDIJKSTRA SHORTEST DISTANCES\n");
    for (int i = 0; i < n; i++) {
        if (distance[i] == INT_MAX) {
            printf("Vertex %d: Unreachable\n", i);
        } 
        else {
            printf("Vertex %d: %d\n", i, distance[i]);
        }
    }
}