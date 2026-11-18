#include <stdlib.h>
#include <string.h>
#include "divide_conquer.h"
int matrix_multiply_classical(
    const long long *A,
    const long long *B,
    long long *C,
    int n)
{
    if (A == NULL || B == NULL || C == NULL || n <= 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
    return 1;
}
static void add_matrix(
    const long long *A,
    const long long *B,
    long long *C,
    int n)
{
    for (int i = 0; i < n * n; i++) {
        C[i] = A[i] + B[i];
    }
}
static void subtract_matrix(
    const long long *A,
    const long long *B,
    long long *C,
    int n)
{
    for (int i = 0; i < n * n; i++) {
        C[i] = A[i] - B[i];
    }
}
static void get_quadrant(
    const long long *A,
    long long *Q,
    int n,
    int half,
    int row_offset,
    int col_offset)
{
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            Q[i * half + j] = A[(i + row_offset) * n + j + col_offset];
        }
    }
}
static void put_quadrant(
    long long *C,
    const long long *Q,
    int n,
    int half,
    int row_offset,
    int col_offset)
{
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[(i + row_offset) * n + j + col_offset] = Q[i * half + j];
        }
    }
}
//Recursive Strassen
static int strassen_recursive(
    const long long *A,
    const long long *B,
    long long *C,
    int n)
{
    if (n == 1) {
        C[0] = A[0] * B[0];
        return 1;
    }
    int h = n / 2;
    size_t size = (size_t)h * h;
    long long *a11 = malloc(size * sizeof(long long));
    long long *a12 = malloc(size * sizeof(long long));
    long long *a21 = malloc(size * sizeof(long long));
    long long *a22 = malloc(size * sizeof(long long));

    long long *b11 = malloc(size * sizeof(long long));
    long long *b12 = malloc(size * sizeof(long long));
    long long *b21 = malloc(size * sizeof(long long));
    long long *b22 = malloc(size * sizeof(long long));

    long long *m1 = malloc(size * sizeof(long long));
    long long *m2 = malloc(size * sizeof(long long));
    long long *m3 = malloc(size * sizeof(long long));
    long long *m4 = malloc(size * sizeof(long long));
    long long *m5 = malloc(size * sizeof(long long));
    long long *m6 = malloc(size * sizeof(long long));
    long long *m7 = malloc(size * sizeof(long long));

    long long *s1 = malloc(size * sizeof(long long));
    long long *s2 = malloc(size * sizeof(long long));

    if (!a11 || !a12 || !a21 || !a22 || !b11 || !b12 || !b21 || !b22 || !m1 || !m2 || !m3 || !m4 || !m5 || !m6 || !m7 || !s1 || !s2) {
        free(a11); free(a12); free(a21); free(a22);
        free(b11); free(b12); free(b21); free(b22);
        free(m1); free(m2); free(m3); free(m4);
        free(m5); free(m6); free(m7);
        free(s1); free(s2);
        return 0;
    }
    get_quadrant(A, a11, n, h, 0, 0);
    get_quadrant(A, a12, n, h, 0, h);
    get_quadrant(A, a21, n, h, h, 0);
    get_quadrant(A, a22, n, h, h, h);

    get_quadrant(B, b11, n, h, 0, 0);
    get_quadrant(B, b12, n, h, 0, h);
    get_quadrant(B, b21, n, h, h, 0);
    get_quadrant(B, b22, n, h, h, h);

    add_matrix(a11, a22, s1, h);
    add_matrix(b11, b22, s2, h);

    if (!strassen_recursive(s1, s2, m1, h)) {
        goto failure;
    }
    add_matrix(a21, a22, s1, h);
    if (!strassen_recursive(s1, b11, m2, h)) {
        goto failure;
    }
    subtract_matrix(b12, b22, s2, h);
    if (!strassen_recursive(a11, s2, m3, h)) {
        goto failure;
    }
    subtract_matrix(b21, b11, s2, h);
    if (!strassen_recursive(a22, s2, m4, h)) {
        goto failure;
    }
    add_matrix(a11, a12, s1, h);
    if (!strassen_recursive(s1, b22, m5, h)) {
        goto failure;
    }
    subtract_matrix(a21, a11, s1, h);
    add_matrix(b11, b12, s2, h);
    if (!strassen_recursive(s1, s2, m6, h)) {
        goto failure;
    }
    subtract_matrix(a12, a22, s1, h);
    add_matrix(b21, b22, s2, h);
    if (!strassen_recursive(s1, s2, m7, h)) {
        goto failure;
    }
    long long *c11 = malloc(size * sizeof(long long));
    long long *c12 = malloc(size * sizeof(long long));
    long long *c21 = malloc(size * sizeof(long long));
    long long *c22 = malloc(size * sizeof(long long));
    if (!c11 || !c12 || !c21 || !c22) {
        free(c11); free(c12); free(c21); free(c22);
        goto failure;
    }
    for (int i = 0; i < h * h; i++) {
        c11[i] = m1[i] + m4[i] - m5[i] + m7[i];
        c12[i] = m3[i] + m5[i];
        c21[i] = m2[i] + m4[i];
        c22[i] = m1[i] - m2[i] + m3[i] + m6[i];
    }
    put_quadrant(C, c11, n, h, 0, 0);
    put_quadrant(C, c12, n, h, 0, h);
    put_quadrant(C, c21, n, h, h, 0);
    put_quadrant(C, c22, n, h, h, h);
    free(c11); free(c12); free(c21); free(c22);
    free(a11); free(a12); free(a21); free(a22);
    free(b11); free(b12); free(b21); free(b22);
    free(m1); free(m2); free(m3); free(m4);
    free(m5); free(m6); free(m7);
    free(s1); free(s2);
    return 1;
failure:
    free(a11); free(a12); free(a21); free(a22);
    free(b11); free(b12); free(b21); free(b22);
    free(m1); free(m2); free(m3); free(m4);
    free(m5); free(m6); free(m7);
    free(s1); free(s2);
    return 0;
}

//Public Strassen function
int matrix_multiply_strassen(
    const long long *A,
    const long long *B,
    long long *C,
    int n)
{
    if (A == NULL || B == NULL || C == NULL || n <= 0) {
        return 0;
    }
    if ((n & (n - 1)) != 0) {
        return 0;
    }
    return strassen_recursive(A, B, C, n);
}