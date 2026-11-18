#ifndef GREEDY_H
#define GREEDY_H
#include <stddef.h>
#define MAX_VERTICES 20
typedef struct {
    int start;
    int finish;
    int id;
} Activity;

typedef struct {
    int start;
    int finish;
    int id;
} Interval;

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

//Activity Selection
int activity_selection(
    Activity activities[],
    int n,
    int selected[]
);

//Interval Partitioning 
int interval_partitioning(
    Interval intervals[],
    int n,
    int room_assignment[]
);

//Huffman Coding 
void huffman_coding(const char text[]);

//Dijkstra
void dijkstra(
    int graph[MAX_VERTICES][MAX_VERTICES],
    int n,
    int source
);

//Prim 
void prim_mst(
    int graph[MAX_VERTICES][MAX_VERTICES],
    int n
);

//Krukal
void kruskal_mst(
    Edge edges[],
    int vertices,
    int edge_count
);
#endif