#include <stdio.h>
#include "motif_search.h"
int main(void)
{
    const char *dna = "ATGCATGACT";
    const char *motif = "ATG";
    size_t positions[100];
    size_t count = naive_search(
        dna,
        motif,
        positions,
        100
    );
    printf("DNA Sequence: %s\n", dna);
    printf("Motif: %s\n", motif);
    if (count > 0) {
        printf("\nMotif found!\n");
        printf("Total occurrences: %zu\n", count);
        printf("Starting positions: ");
        size_t stored = count < 100 ? count : 100;
        for (size_t i = 0; i < stored; i++) {
            printf("%zu ", positions[i]);
        }
        printf("\n");
    }
    else {
        printf("\nMotif not found.\n");
    }
    return 0;
}
