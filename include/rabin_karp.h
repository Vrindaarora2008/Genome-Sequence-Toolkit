#ifndef RABIN_KARP_H
#define RABIN_KARP_H
#include <stddef.h>
size_t rabin_karp_search(
    const char *dna,
    const char *motif,
    size_t positions[],
    size_t max_positions
);
#endif
