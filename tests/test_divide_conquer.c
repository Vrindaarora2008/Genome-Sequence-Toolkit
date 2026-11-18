#include <stdio.h>
#include "divide_conquer.h"
static void test_max_subarray(void)
{
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    long long result;
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("\nMAXIMUM SUBARRAY\n");
    if (max_subarray_sum(arr, n, &result)) {
        printf("Maximum sum: %lld\n", result);
    }
}

static void test_fast_power(void)
{
    printf("\nFAST EXPONENTIATION\n");
    printf("2^10 = %lld\n", fast_power(2, 10));
    printf("3^4  = %lld\n", fast_power(3, 4));
}

static void test_celebrity(void)
{
    int matrix[] = {
        0, 1, 1,
        0, 0, 1,
        0, 0, 0
    };

    printf("\nCELEBRITY PROBLEM\n");
    int result = find_celebrity(matrix, 3);
    if (result == -1) {
        printf("No celebrity found.\n");
    } 
    else {
        printf("Celebrity is person %d\n", result);
    }
}

static void test_matrix_multiplication(void)
{
    long long A[] = {
        1, 2,
        3, 4
    };
    long long B[] = {
        5, 6,
        7, 8
    };
    long long C1[4];
    long long C2[4];

    printf("\nMATRIX MULTIPLICATION\n");
    if (!matrix_multiply_classical(A, B, C1, 2)) {
        printf("Classical multiplication failed.\n");
        return;
    }
    if (!matrix_multiply_strassen(A, B, C2, 2)) {
        printf("Strassen multiplication failed.\n");
        return;
    }
    printf("Classical result:\n");
    for (int i = 0; i < 4; i++) {
        printf("%lld ", C1[i]);
        if (i % 2 == 1) {
            printf("\n");
        }
    }
    printf("Strassen result:\n");
    for (int i = 0; i < 4; i++) {
        printf("%lld ", C2[i]);
        if (i % 2 == 1) {
            printf("\n");
        }
    }
}
int main(void)
{
    test_max_subarray();
    test_fast_power();
    test_celebrity();
    test_matrix_multiplication();
    return 0;
}