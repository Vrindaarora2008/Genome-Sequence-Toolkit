#include "search.h"
#include "annotation.h"
int binary_search(Annotation records[], int n, long target)
{
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (records[middle].start == target) {
            return middle;
        }
        else if (records[middle].start < target) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return -1;
}
