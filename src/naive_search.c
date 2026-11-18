#include <string.h>
#include "motif_search.h"
size_t naive_search(
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
    size_t count = 0;
    for (size_t i = 0; i <= n - m; i++) {
        size_t j;
        for (j = 0; j < m; j++) {
            if (dna[i + j] != motif[j]) {
                break;
            }
        }
        if (j == m) {
            if (positions != NULL && count < max_positions) {
                positions[count] = i;
            }
            count++;
        }
    }
    return count;
}
