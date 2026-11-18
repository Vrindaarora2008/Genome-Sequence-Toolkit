#ifndef FINITE_AUTOMATON_H
#define FINITE_AUTOMATON_H
#include <stddef.h>
size_t finite_automaton_search(
    const char *dna,
    const char *motif,
    size_t positions[],
    size_t max_positions
);
#endif
