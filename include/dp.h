#ifndef DP_H
#define DP_H
#define DP_INF 1000000000000LL
#define MAX_TSP_CITIES 18
long long knapsack_01(const int weights[], const int values[], int n, int capacity);
long long matrix_chain_order(const int dimensions[], int n, int *split);
int lcs_length(const char *a, const char *b);
int lcs_sequence(const char *a, const char *b, char *result, int result_size);
long long optimal_bst(const int frequencies[], int n);
int bellman_ford(int vertices, const int edges[][3], int edge_count, int source, long long distances[]);
void floyd_warshall(int vertices, long long distances[][MAX_TSP_CITIES]);
long long tsp_held_karp(int n, const long long graph[MAX_TSP_CITIES][MAX_TSP_CITIES]);
#endif