#include <stdio.h>
#include "search.h"
#include "annotation.h"
int main(void)
{
    Annotation records[5] = {0};
    records[0].start = 500;
    records[1].start = 100;
    records[2].start = 900;
    records[3].start = 250;
    records[4].start = 50;
    long target = 250;
    int result = linear_search(records, 5, target);
    if (result != -1) {
        printf("Record found!\n");
        printf("Starting coordinate: %ld\n", records[result].start);
        printf("Index: %d\n", result);
    } 
    else {
        printf("Record not found.\n");
    }
    return 0;
}
