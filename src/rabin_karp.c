#include <string.h>
#include "rabin_karp.h"
#define BASE 5
#define MOD 101
// Convert DNA bases into numerical values. 
static int dna_value(char base)
{
    switch (base) {
        case 'A': return 1;
        case 'C': return 2;
        case 'G': return 3;
        case 'T': return 4;
        default: return -1;
    }
}
size_t rabin_karp_search(
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
    int highest_power = 1;
    for (size_t i = 0; i < m - 1; i++) {
        highest_power = (highest_power * BASE) % MOD;
    }
    int motif_hash = 0;
    int window_hash = 0;
    //Calculate initial hashes.
    for (size_t i = 0; i < m; i++) {
        int motif_digit = dna_value(motif[i]);
        int dna_digit = dna_value(dna[i]);
        if (motif_digit == -1 || dna_digit == -1) {
            return 0;
        }
        motif_hash = (motif_hash * BASE + motif_digit) % MOD; //formula for hash of motif
        window_hash = (window_hash * BASE + dna_digit) % MOD;
    }
    size_t count = 0;
    for (size_t i = 0; i <= n - m; i++) 
    {
        if (motif_hash == window_hash && strncmp(dna + i, motif, m) == 0) {
            if (positions != NULL && count < max_positions) {
                positions[count] = i;
            }
            count++;
        }
        if (i < n - m) {
            int outgoing = dna_value(dna[i]);
            int incoming = dna_value(dna[i + m]);
            if (incoming == -1) {
                return count;
            }
            window_hash = (window_hash - outgoing * highest_power) % MOD;
            if (window_hash < 0) {
                window_hash += MOD;
            }
            window_hash = (window_hash * BASE + incoming) % MOD;
        }
    }
    return count;
}
