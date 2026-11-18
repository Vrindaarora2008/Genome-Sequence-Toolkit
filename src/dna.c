#include "genome.h" //calling genome.h to use DNAsequence struct and dna_is_valid function
int dna_is_valid(const char *sequence) 
{
    if (sequence == NULL || sequence[0] == '\0') {
        return 0;
    }
    for (size_t i = 0; sequence[i] != '\0'; i++) {
        char base = sequence[i];
        if (base != 'A' && base != 'C' && base != 'G' && base != 'T') { //a DNA sequence has characters A, C, G and T. If these are not present, then the DNA sequence is invalid.
            return 0;
        }
    }
    return 1;
}
