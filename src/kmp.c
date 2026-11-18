#include <stdlib.h>
#include <string.h>
#include "kmp.h"
static void build_lps(const char *motif, size_t m, size_t lps[])
{
    size_t length = 0;
    size_t i = 1;
    lps[0] = 0;
    while (i < m) {
        if (motif[i] == motif[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0) {
                length = lps[length - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
size_t kmp_search(
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
    size_t *lps = malloc(m * sizeof(size_t));
    if (lps == NULL) {
        return 0;
    }
    build_lps(motif, m, lps);
    size_t i = 0;  /* Index for DNA sequence */
    size_t j = 0;  /* Index for motif */
    size_t count = 0;
    while (i < n) {
        if (dna[i] == motif[j]) {
            i++;
            j++;
        }
        if (j == m) {
            if (positions != NULL && count < max_positions) {
                positions[count] = i - j;
            }
            count++;
            j = lps[j - 1];
        }
        else if (i < n && dna[i] != motif[j]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    free(lps);
    return count;
}
