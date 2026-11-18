#ifndef SORT_H
#define SORT_H
#include "annotation.h"
//Sorts annotation records by their starting coordinates.
void merge_sort(Annotation records[], int left, int right);
void quick_sort(Annotation records[], int low, int high);
#endif

