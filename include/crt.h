#ifndef CRT_H
#define CRT_H
#include <stddef.h>
#define CRT_MAX_EQUATIONS 20
int chinese_remainder_theorem(
    const long long residues[],
    const long long moduli[],
    size_t n,
    long long *solution,
    long long *combined_modulus
);
#endif
