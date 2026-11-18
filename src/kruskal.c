#include <stdio.h>
#include <stdlib.h>
#include "greedy.h"
static int compare_edges(const void *a, const void *b)
{
    const Edge *x = a;
    const Edge *y = b;
    if (x->weight < y->weight) return -1;
    if (x->weight > y->weight) return 1;
    return 0;
}
static int find_parent(int parent[], int vertex)
{
    if (parent[vertex] != vertex) {
        parent[vertex] = find_parent(parent, parent[vertex]);
    }
    return parent[vertex];
}
static void union_sets(int parent[], int rank[], int a, int b)
{
    a = find_parent(parent, a);
    b = find_parent(parent, b);
    if (a == b) {
        return;
    }
    if (rank[a] < rank[b]) {
        parent[a] = b;
    } 
    else if (rank[a] > rank[b]) {
        parent[b] = a;
    } 
    else {
        parent[b] = a;
        rank[a]++;
    }
}
void kruskal_mst(Edge edges[], int vertices, int edge_count)
{
    if (edges == NULL || vertices <= 0 ||
        edge_count < 0) {
        printf("Invalid input.\n");
        return;
    }
    for (int i = 0; i < edge_count; i++) {
        if (edges[i].src < 0 || edges[i].src >= vertices || edges[i].dest < 0 || edges[i].dest >= vertices || edges[i].weight < 0) {
            printf("Invalid edge.\n");
            return;
        }
    }
    Edge *sorted = malloc((size_t)edge_count * sizeof(Edge));
    if (sorted == NULL && edge_count > 0) {
        printf("Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < edge_count; i++) {
        sorted[i] = edges[i];
    }
    qsort(sorted, (size_t)edge_count, sizeof(Edge), compare_edges);
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES] = {0};
    if (vertices > MAX_VERTICES) {
        printf("Maximum supported vertices: %d\n", MAX_VERTICES);
        free(sorted);
        return;
    }
    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
    }
    int total = 0;
    int selected = 0;
    printf("\nKRUSKAL MINIMUM SPANNING TREE\n");
    for (int i = 0; i < edge_count && selected < vertices - 1; i++) {
        int u = sorted[i].src;
        int v = sorted[i].dest;
        if (find_parent(parent, u) != find_parent(parent, v)) {
            printf("%d - %d : %d\n", u, v, sorted[i].weight);
            total += sorted[i].weight;
            union_sets(parent, rank, u, v);
            selected++;
        }
    }
    if (selected != vertices - 1) {
        printf("Graph is disconnected. No spanning tree exists.\n");
    } 
    else {
        printf("Total MST weight: %d\n", total);
    }
    free(sorted);
}