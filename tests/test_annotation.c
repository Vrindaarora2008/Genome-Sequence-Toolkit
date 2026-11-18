#include <stdio.h>
#include <stddef.h>
#include "annotation.h"
int main(void)
{
    size_t valid = 0;
    size_t invalid = 0;
    if (!annotation_count_records(
            "datasets/Homo_sapiens.GRCh38.92.csv",
            &valid,
            &invalid)) {
        printf("Failed to read the annotation dataset.\n");
        return 1;
    }
    printf("Annotation dataset processed successfully.\n");
    printf("Valid records:   %zu\n", valid);
    printf("Invalid records: %zu\n", invalid);
    return 0;
}
