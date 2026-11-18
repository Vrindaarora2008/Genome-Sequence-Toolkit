#include <stdio.h>
#include "greedy.h"
int main(void)
{
    //Activity Selection
    Activity activities[] = {
        {1, 3, 0},
        {2, 5, 1},
        {4, 7, 2},
        {6, 9, 3},
        {8, 10, 4},
        {9, 11, 5}
    };
    int selected[6];
    int count = activity_selection(activities, 6, selected);
    printf("\nACTIVITY SELECTION\n");
    if (count < 0) {
        printf("Activity selection failed.\n");
    } 
    else {
        printf("Selected activities: ");
        for (int i = 0; i < count; i++) {
            printf("A%d ", selected[i] + 1);
        }
        printf("\nTotal: %d\n", count);
    }

    //Interval Partitioning 
    Interval intervals[] = {
        {1, 4, 0},
        {2, 5, 1},
        {3, 6, 2},
        {6, 8, 3}
    };
    int assignments[4];
    int rooms = interval_partitioning(intervals, 4, assignments);
    printf("\nINTERVAL PARTITIONING\n");
    if (rooms < 0) {
        printf("Interval partitioning failed.\n");
    } 
    else {
        printf("Rooms required: %d\n", rooms);
        for (int i = 0; i < 4; i++) {
            printf("Interval %d -> Room %d\n",
                   i + 1, assignments[i] + 1);
        }
    }

    //Huffman Coding
    printf("\nHUFFMAN CODING\n");
    huffman_coding("ABRACADABRA");

    //Dijkstra
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 10, 0, 0, 0},
        {10, 0, 5, 0, 0},
        {0, 5, 0, 7, 0},
        {0, 0, 7, 0, 3},
        {0, 0, 0, 3, 0}
    };
    printf("\nDIJKSTRA\n");
    dijkstra(graph, 5, 0);

    //Prim
    printf("\nPRIM\n");
    prim_mst(graph, 5);

    //Kruskal
    Edge edges[] = {
        {0, 1, 10},
        {1, 2, 5},
        {2, 3, 7},
        {3, 4, 3},
        {0, 4, 20},
        {1, 3, 15}
    };
    printf("\nKRUSKAL\n");
    kruskal_mst(edges, 5, 6);
    return 0;
}