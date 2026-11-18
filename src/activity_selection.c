#include <stdio.h>
#include <stdlib.h>
#include "greedy.h"
static int compare_activities(const void *a, const void *b)
{
    const Activity *x = a;
    const Activity *y = b;
    if (x->finish < y->finish) return -1;
    if (x->finish > y->finish) return 1;
    return 0;
}
int activity_selection(Activity activities[], int n, int selected[])
{
    if (activities == NULL || selected == NULL || n <= 0) {
        return 0;
    }
    Activity *copy = malloc((size_t)n * sizeof(Activity));
    if (copy == NULL) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (activities[i].start > activities[i].finish) {
            free(copy);
            return -1;
        }
        copy[i] = activities[i];
    }
    qsort(copy, (size_t)n, sizeof(Activity), compare_activities);
    int count = 0;
    int last_finish = -1;
    for (int i = 0; i < n; i++) {
        if (count == 0 || copy[i].start >= last_finish) {
            selected[count++] = copy[i].id;
            last_finish = copy[i].finish;
        }
    }
    free(copy);
    return count;
}