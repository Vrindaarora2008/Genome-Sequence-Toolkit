#include <stdlib.h>
#include "greedy.h"
static int compare_intervals(const void *a, const void *b)
{
    const Interval *x = a;
    const Interval *y = b;
    if (x->start < y->start) return -1;
    if (x->start > y->start) return 1;
    return 0;
}
typedef struct {
    int finish;
    int room;
} Room;
static void swap_rooms(Room *a, Room *b)
{
    Room temp = *a;
    *a = *b;
    *b = temp;
}
static void heapify_down(Room heap[], int size, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && heap[left].finish < heap[smallest].finish) {
        smallest = left;
    }
    if (right < size && heap[right].finish < heap[smallest].finish) {
        smallest = right;
    }
    if (smallest != i) {
        swap_rooms(&heap[i], &heap[smallest]);
        heapify_down(heap, size, smallest);
    }
}
static void heapify_up(Room heap[], int i)
{
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].finish <= heap[i].finish) {
            break;
        }
        swap_rooms(&heap[parent], &heap[i]);
        i = parent;
    }
}
int interval_partitioning(
    Interval intervals[],
    int n,
    int room_assignment[])
{
    if (intervals == NULL || room_assignment == NULL || n <= 0) {
        return 0;
    }
    Interval *copy = malloc((size_t)n * sizeof(Interval));
    Room *heap = malloc((size_t)n * sizeof(Room));
    if (copy == NULL || heap == NULL) {
        free(copy);
        free(heap);
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (intervals[i].start > intervals[i].finish) {
            free(copy);
            free(heap);
            return -1;
        }
        copy[i] = intervals[i];
    }
    qsort(copy, (size_t)n, sizeof(Interval), compare_intervals);
    int heap_size = 0;
    int rooms = 0;
    for (int i = 0; i < n; i++) {
        int room;
        if (heap_size > 0 && heap[0].finish <= copy[i].start) {
            room = heap[0].room;
            heap[0].finish = copy[i].finish;
            heapify_down(heap, heap_size, 0);
        } 
        else {
            room = rooms++;
            heap[heap_size].finish = copy[i].finish;
            heap[heap_size].room = room;
            heapify_up(heap, heap_size);
            heap_size++;
        }
        room_assignment[copy[i].id] = room;
    }
    free(copy);
    free(heap);
    return rooms;
}