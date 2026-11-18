#include <stdlib.h>
#include <string.h>
#include "finite_automaton.h"
#define DNA_ALPHABET_SIZE 4
static int dna_value(char base)
{
    switch (base) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return -1;
    }
}
static void build_automaton(
    const char *motif,
    size_t m,
    int **transition,
    size_t *overlap_state)
{
    for (int c = 0; c < DNA_ALPHABET_SIZE; c++) {
        (*transition)[c] = 0;
    }
    (*transition)[dna_value(motif[0])] = 1;
    size_t shadow = 0;
    for (size_t state = 1; state < m; state++) {
        for (int c = 0; c < DNA_ALPHABET_SIZE; c++) {
            (*transition)[state * DNA_ALPHABET_SIZE + c] = (*transition)[shadow * DNA_ALPHABET_SIZE + c];
        }
        int current = dna_value(motif[state]);
        (*transition)[state * DNA_ALPHABET_SIZE + current] = (int)(state + 1);
        shadow = (size_t)(*transition)[shadow * DNA_ALPHABET_SIZE + current];
    }
    *overlap_state = shadow;
}
size_t finite_automaton_search(
    const char *dna,
    const char *motif,
    size_t positions[],
    size_t max_positions)
{
    if (dna == NULL || motif == NULL) {
        return 0;
    }
    size_t n = strlen(dna);
    size_t m = strlen(motif);
    if (m == 0 || m > n) {
        return 0;
    }
    for (size_t i = 0; i < m; i++) {
        if (dna_value(motif[i]) == -1 || m > (size_t)2147483647) {
            return 0;
        }
    }
    if (m > (size_t)-1 / (DNA_ALPHABET_SIZE * sizeof(int))) {
        return 0;
    }
    int *transition = malloc(
        m * DNA_ALPHABET_SIZE * sizeof(int)
    );
    if (transition == NULL) {
        return 0;
    }
    size_t overlap_state = 0;
    build_automaton(
        motif, m, &transition, &overlap_state
    );
    size_t state = 0;
    size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        int current = dna_value(dna[i]);
        if (current == -1) {
            free(transition);
            return 0;
        }
        state = (size_t)transition[state * DNA_ALPHABET_SIZE + current];
        if (state == m) {
            if (positions != NULL && count < max_positions) {
                positions[count] = i + 1 - m;
            }
            count++;
            state = overlap_state;
        }
    }
    free(transition);
    return count;
}
