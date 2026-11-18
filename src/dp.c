#include "dp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//0/1 KNAPSACK
long long knapsack_01(const int weights[], const int values[],int n, int capacity)
{
    if (!weights || !values || n <= 0 || capacity < 0)
        return -1;
    long long *dp = calloc((size_t)capacity + 1, sizeof(long long));
    if (!dp)
        return -1;
    for (int i = 0; i < n; i++) {
        if (weights[i] <= 0) {
            free(dp);
            return -1;
        }
        for (int w = capacity; w >= weights[i]; w--) {
            long long candidate = dp[w - weights[i]] + values[i];
            if (candidate > dp[w])
                dp[w] = candidate;
        }
    }
    long long answer = dp[capacity];
    free(dp);
    return answer;
}

//MATRIX CHAIN MULTIPLICATION
long long matrix_chain_order(const int dimensions[], int n, int *split)
{
    if (!dimensions || n <= 0)
        return -1;
    for (int i = 0; i <= n; i++) {
        if (dimensions[i] <= 0)
            return -1;
    }
    long long *dp = calloc((size_t)n * n, sizeof(long long));
    if (!dp)
        return -1;
    #define DP(i, j) dp[(size_t)(i) * n + (j)]
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            DP(i, j) = LLONG_MAX;
            for (int k = i; k < j; k++) {
                long long cost = DP(i, k) + DP(k + 1, j) + (long long)dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                if (cost < DP(i, j)) {
                    DP(i, j) = cost;
                    if (split)
                        split[i * n + j] = k;
                }
            }
        }
    }
    long long answer = DP(0, n - 1);
    free(dp);
    #undef DP
    return answer;
}

//LONGEST COMMON SUBSEQUENCE
int lcs_length(const char *a, const char *b)
{
    if (!a || !b)
        return -1;
    int m = (int)strlen(a);
    int n = (int)strlen(b);
    int *dp = calloc((size_t)(m + 1) * (n + 1), sizeof(int));
    if (!dp)
        return -1;
    #define LCS(i, j) dp[(size_t)(i) * (n + 1) + (j)]
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1])
                LCS(i, j) = LCS(i - 1, j - 1) + 1;
            else if (LCS(i - 1, j) >= LCS(i, j - 1))
                LCS(i, j) = LCS(i - 1, j);
            else
                LCS(i, j) = LCS(i, j - 1);
        }
    }
    int answer = LCS(m, n);
    free(dp);
    #undef LCS
    return answer;
}
int lcs_sequence(const char *a, const char *b, char *result, int result_size)
{
    if (!a || !b || !result || result_size <= 0)
        return -1;
    int m = (int)strlen(a);
    int n = (int)strlen(b);
    int *dp = calloc((size_t)(m + 1) * (n + 1), sizeof(int));
    if (!dp)
        return -1;
    #define LCS2(i, j) dp[(size_t)(i) * (n + 1) + (j)]
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1])
                LCS2(i, j) = LCS2(i - 1, j - 1) + 1;
            else if (LCS2(i - 1, j) >= LCS2(i, j - 1))
                LCS2(i, j) = LCS2(i - 1, j);
            else
                LCS2(i, j) = LCS2(i, j - 1);
        }
    }
    int length = LCS2(m, n);
    if (length + 1 > result_size) {
        free(dp);
        return -1;
    }
    result[length] = '\0';
    int i = m;
    int j = n;
    int pos = length - 1;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            result[pos--] = a[i - 1];
            i--;
            j--;
        } 
        else if (LCS2(i - 1, j) >= LCS2(i, j - 1)) {
            i--;
        } 
        else {
            j--;
        }
    }
    free(dp);
    #undef LCS2
    return length;
}

//OPTIMAL BINARY SEARCH TREE
long long optimal_bst(const int frequencies[], int n)
{
    if (!frequencies || n <= 0)
        return -1;
    long long *dp = calloc((size_t)n * n, sizeof(long long));
    if (!dp)
        return -1;
    long long *prefix = calloc((size_t)n + 1, sizeof(long long));
    if (!prefix) {
        free(dp);
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (frequencies[i] < 0) {
            free(dp);
            free(prefix);
            return -1;
        }
        prefix[i + 1] = prefix[i] + frequencies[i];
    }
    #define OBST(i, j) dp[(size_t)(i) * n + (j)]
    for (int i = 0; i < n; i++)
        OBST(i, i) = frequencies[i];
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            long long sum = prefix[j + 1] - prefix[i];
            OBST(i, j) = LLONG_MAX;
            for (int root = i; root <= j; root++) {
                long long left = (root > i) ? OBST(i, root - 1) : 0;
                long long right = (root < j) ? OBST(root + 1, j) : 0;
                long long cost = left + right + sum;
                if (cost < OBST(i, j))
                    OBST(i, j) = cost;
            }
        }
    }
    long long answer = OBST(0, n - 1);
    free(dp);
    free(prefix);
    #undef OBST
    return answer;
}

//BELLMAN-FORD
int bellman_ford(int vertices, const int edges[][3], int edge_count, int source, long long distances[])
{
    if (vertices <= 0 || edge_count < 0 || source < 0 || source >= vertices || !distances || (edge_count > 0 && !edges))
        return 0;
    for (int i = 0; i < edge_count; i++) {
        if (edges[i][0] < 0 || edges[i][0] >= vertices || edges[i][1] < 0 || edges[i][1] >= vertices)
            return 0;
    }
    for (int i = 0; i < vertices; i++)
        distances[i] = DP_INF;
    distances[source] = 0;
    for (int i = 0; i < vertices - 1; i++) {
        int updated = 0;
        for (int j = 0; j < edge_count; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int weight = edges[j][2];
            if (distances[u] != DP_INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                updated = 1;
            }
        }
        if (!updated)
            break;
    }
    for (int j = 0; j < edge_count; j++) {
        int u = edges[j][0];
        int v = edges[j][1];
        int weight = edges[j][2];
        if (distances[u] != DP_INF && distances[u] + weight < distances[v])
            return -1;
    }
    return 1;
}

//FLOYD-WARSHALL
void floyd_warshall(int vertices, long long distances[][MAX_TSP_CITIES])
{
    if (vertices <= 0 || vertices > MAX_TSP_CITIES || !distances)
        return;
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (distances[i][k] == DP_INF || distances[k][j] == DP_INF)
                    continue;
                long long candidate = distances[i][k] + distances[k][j];
                if (candidate < distances[i][j])
                    distances[i][j] = candidate;
            }
        }
    }
}

//BOUNDED TSP
long long tsp_held_karp(int n, const long long graph[MAX_TSP_CITIES][MAX_TSP_CITIES])
{
    if (!graph || n < 2 || n > MAX_TSP_CITIES)
        return -1;
    int states = 1 << n;
    size_t total = (size_t)states * n;
    long long *dp = malloc(total * sizeof(long long));
    if (!dp)
        return -1;
    for (size_t i = 0; i < total; i++)
        dp[i] = DP_INF;
    #define TSP(mask, city) dp[(size_t)(mask) * n + (city)]
    TSP(1, 0) = 0;
    for (int mask = 1; mask < states; mask++) {
        if (!(mask & 1))
            continue;
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u)))
                continue;
            if (TSP(mask, u) == DP_INF)
                continue;
            for (int v = 1; v < n; v++) {
                if (mask & (1 << v))
                    continue;
                if (graph[u][v] == DP_INF)
                    continue;
                int next_mask = mask | (1 << v);
                long long candidate = TSP(mask, u) + graph[u][v];
                if (candidate < TSP(next_mask, v))
                    TSP(next_mask, v) = candidate;
            }
        }
    }
    int full_mask = states - 1;
    long long answer = DP_INF;
    for (int u = 1; u < n; u++) {
        if (TSP(full_mask, u) == DP_INF || graph[u][0] == DP_INF)
            continue;
        long long candidate = TSP(full_mask, u) + graph[u][0];
        if (candidate < answer)
            answer = candidate;
    }
    free(dp);
    #undef TSP
    return answer == DP_INF ? -1 : answer;
}