#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include <stdint.h>
#define MAX_NQUEENS 15
typedef enum {
    BNB_FIFO = 1,
    BNB_LIFO = 2,
    BNB_LEAST_COST = 3
} BnBStrategy;

//N-Queens
long long nqueens_solve(int n, int first_solution[]);

//Subset Sum
int subset_sum_find(const int values[], int n, long long target, int selected[]);

//Branch-and-Bound 0/1 Knapsack.
int bnb_knapsack(
    const int weights[],
    const int values[],
    int n,
    int capacity,
    BnBStrategy strategy,
    long long max_nodes,
    long long *best_profit,
    int selected[]
);
#endif