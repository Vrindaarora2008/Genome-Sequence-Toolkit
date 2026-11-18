#include <stdio.h>
#include "rabin_karp.h"
int main(void)
{
    const char *dna = "ATGCATGACT";
    const char *motif = "ATG";
    size_t positions[100];
    size_t count = rabin_karp_search(
        dna, motif, positions, 100
    );
    printf("DNA Sequence: %s\n", dna);
    printf("Motif: %s\n", motif);
    if (count > 0) {
        printf("\nMotif found!\n");
        printf("Total occurrences: %zu\n", count);
        printf("Starting positions: ");
        for (size_t i = 0; i < count && i < 100; i++) {
            printf("%zu ", positions[i]);
        }
        printf("\n");
    } 
    else {
        printf("\nMotif not found.\n");
    }
    return 0;
}
