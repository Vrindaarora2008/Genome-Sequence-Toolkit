#ifndef DIVIDE_CONQUER_H
#define DIVIDE_CONQUER_H
#include <stddef.h>
/// Maximum Subarray Sum
int max_subarray_sum(
    const int arr[],
    int n,
    long long *result
);
//Fast Exponentiation
long long fast_power(long long base, unsigned int exponent);

// Celebrity Problem
int find_celebrity(const int *matrix, int n);

// Matrix Multiplication
int matrix_multiply_classical(
    const long long *A,
    const long long *B,
    long long *C,
    int n
);
// Strassen's Matrix Multiplication
int matrix_multiply_strassen(
    const long long *A,
    const long long *B,
    long long *C,
    int n
);

#endif