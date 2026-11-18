#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include "annotation.h"
//Performs Linear Search on annotation records.
int linear_search(Annotation records[], int n, long target)
{
    for (int i = 0; i < n; i++) {

        if (records[i].start == target) {
            return i;
        }
    }
    return -1;
}
