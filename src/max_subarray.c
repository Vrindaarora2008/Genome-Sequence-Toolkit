#include <limits.h>
#include <stddef.h>
#include "divide_conquer.h"
static long long max_crossing_sum(
    const int arr[],
    int left,
    int mid,
    int right)
{
    long long sum = 0;
    long long left_sum = LLONG_MIN;
    long long right_sum = LLONG_MIN;
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
        }
    }
    sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
        }
    }
    return left_sum + right_sum;
}
static long long max_subarray_recursive(
    const int arr[],
    int left,
    int right)
{
    if (left == right) {
        return arr[left];
    }
    int mid = left + (right - left) / 2;
    long long left_max = max_subarray_recursive(arr, left, mid);
    long long right_max = max_subarray_recursive(arr, mid + 1, right);
    long long crossing_max = max_crossing_sum(arr, left, mid, right);
    long long best = left_max;
    if (right_max > best) {
        best = right_max;
    }
    if (crossing_max > best) {
        best = crossing_max;
    }
    return best;
}
int max_subarray_sum(
    const int arr[],
    int n,
    long long *result)
{
    if (arr == NULL || result == NULL || n <= 0) {
        return 0;
    }
    *result = max_subarray_recursive(arr, 0, n - 1);
    return 1;
}