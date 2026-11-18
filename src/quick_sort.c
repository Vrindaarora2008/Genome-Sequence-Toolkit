#include "sort.h"
#include "annotation.h"
void swap(Annotation *a, Annotation *b)
{
    Annotation temp = *a;
    *a = *b;
    *b = temp;
}
int partition(Annotation records[], int low, int high)
{
    long pivot = records[high].start;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (records[j].start <= pivot) {
            i++;
            swap(&records[i], &records[j]);
        }
    }
    swap(&records[i + 1], &records[high]);
    return i + 1;
}
void quick_sort(Annotation records[], int low, int high)
{
    if (low < high) {
        int pivot_index = partition(records, low, high);
        quick_sort(records, low, pivot_index - 1);
        quick_sort(records, pivot_index + 1, high);
    }
}
