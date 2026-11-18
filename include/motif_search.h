#ifndef MOTIF_SEARCH_H
#define MOTIF_SEARCH_H
#define MAX_SEQUENCE_LENGTH 10000
#define MAX_MOTIF_LENGTH 1000
#include <stddef.h>
size_t naive_search(const char *dna,
    const char *motif,
    size_t positions[],
    size_t max_positions
);
#endif
