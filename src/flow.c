#include "flow.h"
#include <string.h>
#include<limits.h>
//FORD-FULKERSON USING BFS
static int bfs_augmenting_path(
    long long residual[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES],
    int vertices,
    int source,
    int sink,
    int parent[]
)
{
    int visited[FLOW_MAX_VERTICES] = {0};
    int queue[FLOW_MAX_VERTICES];
    int front = 0;
    int rear = 0;
    queue[rear++] = source;
    visited[source] = 1;
    parent[source] = -1;
    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && residual[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;
                if (v == sink)
                    return 1;
            }
        }
    }
    return 0;
}
long long ford_fulkerson(
    int capacity[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES],
    int vertices,
    int source,
    int sink
)
{
    if (!capacity || vertices <= 0 || vertices > FLOW_MAX_VERTICES || source < 0 || source >= vertices || sink < 0 || sink >= vertices ||  source == sink)
        return -1;
    long long residual[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES] = {0};
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (capacity[i][j] < 0)
                return -1;
            residual[i][j] = capacity[i][j];
        }
    }
    int parent[FLOW_MAX_VERTICES];
    long long max_flow = 0;
    while (bfs_augmenting_path(residual, vertices, source, sink, parent)) {
        long long path_flow = LLONG_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            if (residual[u][v] < path_flow)
                path_flow = residual[u][v];
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

//MAXIMUM BIPARTITE MATCHING
static int matching_dfs(
    int left,
    int right_count,
    int adjacency[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES],
    int visited_right[],
    int right_match[]
)
{
    for (int right = 0; right < right_count; right++) {
        if (adjacency[left][right] && !visited_right[right]) {
            visited_right[right] = 1;
            if (right_match[right] == -1 || matching_dfs( right_match[right], right_count, adjacency, visited_right, right_match)) {
                right_match[right] = left;
                return 1;
            }
        }
    }
    return 0;
}
int maximum_bipartite_matching(
    int left_count,
    int right_count,
    int adjacency[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES],
    int left_match[],
    int right_match[]
)
{
    if (!adjacency || !left_match || !right_match || left_count <= 0 || left_count > FLOW_MAX_VERTICES || right_count <= 0 || right_count > FLOW_MAX_VERTICES)
        return -1;
    for (int i = 0; i < left_count; i++) {
        for (int j = 0; j < right_count; j++) {
            if (adjacency[i][j] != 0 &&
                adjacency[i][j] != 1)
                return -1;
        }
    }
    for (int i = 0; i < left_count; i++)
        left_match[i] = -1;
    for (int j = 0; j < right_count; j++)
        right_match[j] = -1;
    int matching_size = 0;
    for (int left = 0; left < left_count; left++) {
        int visited_right[FLOW_MAX_VERTICES] = {0};
        if (matching_dfs(left, right_count, adjacency, visited_right, right_match)) {
            matching_size++;
        }
    }
    for (int right = 0; right < right_count; right++) {
        if (right_match[right] != -1) {
            left_match[right_match[right]] = right;
        }
    }
    return matching_size;
}