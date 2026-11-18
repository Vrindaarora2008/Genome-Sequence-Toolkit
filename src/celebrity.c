#include "divide_conquer.h"
int find_celebrity(const int *matrix, int n)
{
    if (matrix == NULL || n <= 0) {
        return -1;
    }
    int candidate = 0;
    for (int i = 1; i < n; i++) {
        if (matrix[candidate * n + i] == 1) {
            candidate = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (i == candidate) {
            continue;
        }
        if (matrix[candidate * n + i] == 1 || matrix[i * n + candidate] == 0) {
            return -1;
        }
    }
    return candidate;
}