#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
void merge(Annotation records[], int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;
    Annotation *L = malloc(n1 * sizeof(Annotation));
    Annotation *R = malloc(n2 * sizeof(Annotation));
    if (L == NULL || R == NULL) {
        printf("Memory allocation failed.\n");
        free(L);
        free(R);
        return;
    }
//copying datat to temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = records[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = records[middle + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].start <= R[j].start) {
            records[k] = L[i];
            i++;
        } 
        else {
            records[k] = R[j];
            j++;
        }

        k++;
    }
    while (i < n1) {
        records[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        records[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}
void merge_sort(Annotation records[], int left, int right)
{
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(records, left, middle);
        merge_sort(records, middle + 1, right);
        merge(records, left, middle, right);
    }
}
