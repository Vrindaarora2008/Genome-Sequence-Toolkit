#ifndef KMP_H
#define KMP_H
#include <stddef.h>
size_t kmp_search(
    const char *dna,
    const char *motif,
    size_t positions[],
    size_t max_positions
);
#endif
