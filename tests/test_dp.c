#include <stdio.h>
#include <string.h>
#include "dp.h"
int main(void)
{
    //Knapsack
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    printf("1. 0/1 Knapsack\n");
    printf("Maximum value: %lld\n\n", knapsack_01(weights, values, 4, 5));

    //Matrix Chain
    int dimensions[] = {10, 30, 5, 60};
    printf("2. Matrix Chain Multiplication\n");
    printf("Minimum multiplications: %lld\n\n", matrix_chain_order(dimensions, 3, NULL));

    // LCS
    char *a = "AGGTAB";
    char *b = "GXTXAYB";
    char sequence[20];
    printf("3. Longest Common Subsequence\n");
    printf("LCS length: %d\n", lcs_length(a, b));
    int lcs_size = lcs_sequence(a, b, sequence, 20);
    if (lcs_size >= 0)
        printf("LCS sequence: %s\n\n", sequence);

    //Optimal BST
    int frequencies[] = {34, 8, 50};
    printf("4. Optimal Binary Search Tree\n");
    printf("Minimum search cost: %lld\n\n", optimal_bst(frequencies, 3));

    //Bellman-Ford
    int edges[][3] = {
        {0, 1, 4},
        {0, 2, 5},
        {1, 2, -2},
        {1, 3, 6},
        {2, 3, 3}
    };
    long long distances[4];
    printf("5. Bellman-Ford\n");
    int result = bellman_ford(4, edges, 5, 0, distances);
    if (result == 1) {
        for (int i = 0; i < 4; i++)
            printf("Distance to %d: %lld\n", i, distances[i]);
    } 
    else if (result == -1) {
        printf("Reachable negative cycle detected.\n");
    }
    printf("\n");

    //Floyd-Warshall
    long long graph[MAX_TSP_CITIES][MAX_TSP_CITIES];
    for (int i = 0; i < MAX_TSP_CITIES; i++) {
        for (int j = 0; j < MAX_TSP_CITIES; j++) {
            graph[i][j] = (i == j) ? 0 : DP_INF;
        }
    }
    graph[0][1] = 5;
    graph[0][3] = 10;
    graph[1][2] = 3;
    graph[2][3] = 1;
    printf("6. Floyd-Warshall\n");
    floyd_warshall(4, graph);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (graph[i][j] == DP_INF)
                printf("INF ");
            else
                printf("%lld ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //Held-Karp TSP
    long long tsp_graph[MAX_TSP_CITIES][MAX_TSP_CITIES];
    for (int i = 0; i < MAX_TSP_CITIES; i++) {
        for (int j = 0; j < MAX_TSP_CITIES; j++) {
            tsp_graph[i][j] = (i == j) ? 0 : DP_INF;
        }
    }
    tsp_graph[0][1] = 10;
    tsp_graph[0][2] = 15;
    tsp_graph[0][3] = 20;

    tsp_graph[1][0] = 10;
    tsp_graph[1][2] = 35;
    tsp_graph[1][3] = 25;

    tsp_graph[2][0] = 15;
    tsp_graph[2][1] = 35;
    tsp_graph[2][3] = 30;

    tsp_graph[3][0] = 20;
    tsp_graph[3][1] = 25;
    tsp_graph[3][2] = 30;

    printf("7. Bounded TSP (Held-Karp)\n");
    printf("Minimum tour cost: %lld\n\n", tsp_held_karp(4, tsp_graph));
    return 0;
}