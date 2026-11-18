#include "backtracking.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//N-QUEENS
static void nqueens_recursive(
    int n,
    int row,
    unsigned int columns,
    unsigned int diag_left,
    unsigned int diag_right,
    unsigned int mask,
    int current[],
    int first_solution[],
    long long *count
)
{
    if (row == n) {
        (*count)++;
        if (*count == 1) {
            for (int i = 0; i < n; i++)
                first_solution[i] = current[i];
        }
        return;
    }
    unsigned int available = mask & ~(columns | diag_left | diag_right);
    while (available) {
        unsigned int position = available & (~available + 1U);
        available ^= position;
        int column = 0;
        unsigned int temp = position;
        while (temp > 1U) {
            temp >>= 1;
            column++;
        }
        current[row] = column + 1;
        nqueens_recursive(
            n,
            row + 1,
            columns | position,
            ((diag_left | position) << 1) & mask,
            (diag_right | position) >> 1,
            mask,
            current,
            first_solution,
            count
        );
    }
}
long long nqueens_solve(int n, int first_solution[])
{
    if (n <= 0 || n > MAX_NQUEENS || !first_solution)
        return -1;
    int current[MAX_NQUEENS] = {0};
    for (int i = 0; i < n; i++)
        first_solution[i] = 0;
    long long count = 0;
    unsigned int mask = (1U << n) - 1U;
    nqueens_recursive(
        n, 0, 0, 0, 0,
        mask,
        current,
        first_solution,
        &count
    );

    return count;
}

//SUBSET SUM
static int subset_recursive(
    const int values[],
    int n,
    int index,
    long long remaining,
    int selected[]
)
{
    if (remaining == 0)
        return 1;
    if (index == n)
        return 0;
    selected[index] = 1;
    if (subset_recursive(values, n, index + 1, remaining - values[index], selected))
        return 1;
    selected[index] = 0;
    if (subset_recursive(values, n, index + 1, remaining, selected))
        return 1;
    return 0;
}
int subset_sum_find(
    const int values[],
    int n,
    long long target,
    int selected[]
)
{
    if (!values || !selected || n <= 0)
        return -1;
    memset(selected, 0, (size_t)n * sizeof(int));
    return subset_recursive(values, n, 0, target, selected);
}

//BRANCH-AND-BOUND KNAPSACK
typedef struct {
    int original_index;
    int weight;
    int value;
    long double ratio;
} BnBItem;
typedef struct {
    int level;
    long long weight;
    long long profit;
    long double bound;
    uint64_t mask;
} BnBNode;
static int compare_items(const void *a, const void *b)
{
    const BnBItem *x = a;
    const BnBItem *y = b;
    if (x->ratio < y->ratio)
        return 1;
    if (x->ratio > y->ratio)
        return -1;
    return 0;
}

//Fractional-knapsack upper bound.
static long double calculate_bound(
    const BnBItem items[],
    int n,
    int capacity,
    const BnBNode *node
)
{
    if (node->weight > capacity)
        return 0;
    long long total_weight = node->weight;
    long double bound = node->profit;
    int i = node->level;
    while (i < n && total_weight + items[i].weight <= capacity) {
        total_weight += items[i].weight;
        bound += items[i].value;
        i++;
    }
    if (i < n && total_weight < capacity) {
        int remaining = capacity - (int)total_weight;
        bound += (long double)remaining * items[i].ratio;
    }
    return bound;
}
static int push_node(
    BnBNode **nodes,
    size_t *count,
    size_t *capacity,
    BnBNode node
)
{
    if (*count == *capacity) {
        size_t new_capacity = (*capacity == 0) ? 64 : (*capacity * 2);
        if (new_capacity < *capacity || new_capacity > SIZE_MAX / sizeof(BnBNode))
            return 0;
        BnBNode *new_nodes = realloc(*nodes, new_capacity * sizeof(BnBNode));
        if (!new_nodes)
            return 0;
        *nodes = new_nodes;
        *capacity = new_capacity;
    }
    (*nodes)[(*count)++] = node;
    return 1;
}
static BnBNode pop_node(
    BnBNode nodes[],
    size_t *count,
    size_t *head,
    BnBStrategy strategy
)
{
    if (strategy == BNB_FIFO) {
        return nodes[(*head)++];
    }
    if (strategy == BNB_LIFO) {
        return nodes[--(*count)];
    }
    size_t best_index = 0;
    for (size_t i = 1; i < *count; i++) {
        if (nodes[i].bound > nodes[best_index].bound)
            best_index = i;
    }
    BnBNode chosen = nodes[best_index];
    nodes[best_index] = nodes[*count - 1];
    (*count)--;
    return chosen;
}
int bnb_knapsack(
    const int weights[],
    const int values[],
    int n,
    int capacity,
    BnBStrategy strategy,
    long long max_nodes,
    long long *best_profit,
    int selected[]
)
{
    if (!weights || !values || !best_profit || !selected || n <= 0 || n > 63 || capacity < 0 || max_nodes <= 0 || strategy < BNB_FIFO || strategy > BNB_LEAST_COST)
        return 0;
    *best_profit = 0;
    memset(selected, 0, (size_t)n * sizeof(int));
    BnBItem *items = malloc((size_t)n * sizeof(BnBItem));
    if (!items)
        return -1;
    for (int i = 0; i < n; i++) {
        if (weights[i] <= 0 || values[i] < 0) {
            free(items);
            return 0;
        }
        items[i].original_index = i;
        items[i].weight = weights[i];
        items[i].value = values[i];
        items[i].ratio = (long double)values[i] / weights[i];
    }
    qsort(items, (size_t)n, sizeof(BnBItem), compare_items);
    BnBNode *nodes = NULL;
    size_t count = 0;
    size_t node_capacity = 0;
    size_t head = 0;
    BnBNode root = {0};
    root.level = 0;
    root.weight = 0;
    root.profit = 0;
    root.mask = 0;
    root.bound = calculate_bound(items, n, capacity, &root);
    if (!push_node(&nodes, &count, &node_capacity, root)) {
        free(items);
        return -1;
    }
    long long expanded = 0;
    uint64_t best_mask = 0;
    while ((strategy == BNB_FIFO && head < count) || (strategy != BNB_FIFO && count > 0)) {
        if (expanded >= max_nodes) {
            free(nodes);
            free(items);
            return -2;
        }
        BnBNode current = pop_node(nodes, &count, &head, strategy);
        expanded++;
        if (current.bound <= *best_profit)
            continue;
        if (current.level >= n)
            continue;
        int i = current.level;
        BnBNode include = current;
        include.level = i + 1;
        include.weight += items[i].weight;
        include.profit += items[i].value;
        include.mask |= (UINT64_C(1) << i);
        if (include.weight <= capacity) {
            if (include.profit > *best_profit) {
                *best_profit = include.profit;
                best_mask = include.mask;
            }
            include.bound = calculate_bound(items, n, capacity, &include);
            if (include.level < n && include.bound > *best_profit) {
                if (!push_node(&nodes, &count, &node_capacity, include)) {
                    free(nodes);
                    free(items);
                    return -1;
                }
            }
        }
        BnBNode exclude = current;
        exclude.level = i + 1;
        exclude.bound = calculate_bound(items, n, capacity, &exclude);
        if (exclude.level < n && exclude.bound > *best_profit) {
            if (!push_node(&nodes, &count, &node_capacity, exclude)) {
                free(nodes);
                free(items);
                return -1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (best_mask & (UINT64_C(1) << i)) {
            int original = items[i].original_index;
            selected[original] = 1;
        }
    }
    free(nodes);
    free(items);
    return 1;
}