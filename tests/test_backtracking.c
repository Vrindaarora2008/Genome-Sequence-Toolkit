#include <stdio.h>
#include "backtracking.h"
static void test_nqueens(void)
{
    printf("1. N-Queens\n");
    int solution[MAX_NQUEENS];
    long long count = nqueens_solve(4, solution);
    printf("Number of solutions for N=4: %lld\n", count);
    printf("One valid solution (column per row): ");
    for (int i = 0; i < 4; i++)
        printf("%d ", solution[i]);
    printf("\n\n");
}
static void test_subset_sum(void)
{
    printf("2. Subset Sum\n");
    int values[] = {3, 4, 5, 2};
    int selected[4];
    int result = subset_sum_find( values, 4, 9, selected);
    if (result == 1) {
        printf("Subset found: ");
        for (int i = 0; i < 4; i++) {
            if (selected[i])
                printf("%d ", values[i]);
        }
        printf("\n");
    } 
    else {
        printf("No subset found.\n");
    }
    printf("\n");
}
static void test_branch_bound(void)
{
    printf("3. Branch-and-Bound Knapsack\n");
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int capacity = 5, n = 4;
    const char *strategy_names[] = {
        "FIFO",
        "LIFO",
        "Least-cost / Best-bound"
    };
    BnBStrategy strategies[] = {
        BNB_FIFO,
        BNB_LIFO,
        BNB_LEAST_COST
    };
    for (int s = 0; s < 3; s++) {
        int selected[4] = {0};
        long long best_profit = 0;
        int status = bnb_knapsack(
            weights,
            values,
            n,
            capacity,
            strategies[s],
            100000,
            &best_profit,
            selected
        );
        printf("\nStrategy: %s\n", strategy_names[s]);
        if (status == 1) {
            printf("Optimal profit: %lld\n", best_profit);
            printf("Selected jobs: ");
            for (int i = 0; i < n; i++) {
                if (selected[i])
                    printf("%d ", i + 1);
            }
            printf("\n");
        } 
        else if (status == -2) {
            printf("Optimality not proven.\n");
        } 
        else {
            printf("Error\n");
        }
    }
}
int main(void)
{
    test_nqueens();
    test_subset_sum();
    test_branch_bound();
    return 0;
}