#ifndef FLOW_H
#define FLOW_H
#define FLOW_MAX_VERTICES 20
long long ford_fulkerson(
    int capacity[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES],
    int vertices,
    int source,
    int sink
);
int maximum_bipartite_matching(
    int left_count,
    int right_count,
    int adjacency[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES],
    int left_match[],
    int right_match[]
);
#endif