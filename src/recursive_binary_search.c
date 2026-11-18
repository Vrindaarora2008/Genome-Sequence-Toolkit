#include "search.h"
#include "annotation.h"
int recursive_binary_search( Annotation records[], int left, int right,long target)
{
    //search range is empty.
    if (left > right) {
        return -1;
    }
    int middle = left + (right - left) / 2;
    if (records[middle].start == target) {
        return middle;
    }
    if (records[middle].start < target) {
        return recursive_binary_search(records, middle + 1, right, target);
    }
    return recursive_binary_search(records, left, middle - 1, target
    );
}
