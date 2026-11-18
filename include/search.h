#ifndef SEARCH_H
#define SEARCH_H
#include "annotation.h"
//Searches for an annotation by starting coordinate.
int linear_search(Annotation records[], int n, long target);
//searches for an annotation by starting coordinate using binary search.
int binary_search(Annotation records[], int n, long target);
int recursive_binary_search(
    Annotation records[],
    int left,
    int right,
    long target
);
#endif


