#include <stdio.h>
#include "sort.h"
int main(void)
{
    Annotation records[5] = {0};
    records[0].start = 500;
    records[1].start = 100;
    records[2].start = 900;
    records[3].start = 250;
    records[4].start = 50;
    printf("Before sorting\n");
    for (int i = 0; i < 5; i++) {
        printf("%ld ", records[i].start);
    }
    merge_sort(records, 0, 4);
    printf("\nAfter sorting\n");
    for (int i = 0; i < 5; i++) {
        printf("%ld ", records[i].start);
    }
    printf("\n");
    return 0;
}
