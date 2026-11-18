#include <stdio.h>
#include "flow.h"
static void test_ford_fulkerson(void)
{
    printf("1. Ford-Fulkerson Maximum Flow\n");
    int capacity[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES] = {0};
    capacity[0][1] = 16;
    capacity[0][2] = 13;
    capacity[1][2] = 10;
    capacity[2][1] = 4;
    capacity[1][3] = 12;
    capacity[3][2] = 9;
    capacity[2][4] = 14;
    capacity[4][3] = 7;
    capacity[3][5] = 20;
    capacity[4][5] = 4;
    long long result = ford_fulkerson(capacity, 6, 0, 5);
    printf("Maximum flow: %lld\n\n", result);
}
static void test_bipartite_matching(void)
{
    printf("2. Maximum Bipartite Matching\n");
    int adjacency[FLOW_MAX_VERTICES][FLOW_MAX_VERTICES] = {0};
    adjacency[0][0] = 1;
    adjacency[0][1] = 1;
    adjacency[1][0] = 1;
    adjacency[1][2] = 1;
    adjacency[2][1] = 1;
    adjacency[2][3] = 1;
    adjacency[3][2] = 1;
    adjacency[3][3] = 1;
    int left_match[FLOW_MAX_VERTICES];
    int right_match[FLOW_MAX_VERTICES];
    int result = maximum_bipartite_matching( 4, 4, adjacency, left_match, right_match);
    printf("Maximum matching size: %d\n", result);
    printf("Assignments:\n");
    for (int i = 0; i < 4; i++) {
        if (left_match[i] != -1) {
            printf("Sample %d -> Analysis Slot %d\n", i + 1, left_match[i] + 1);
        }
    }
    printf("\n");
}
int main(void)
{
    test_ford_fulkerson();
    test_bipartite_matching();
    return 0;
}