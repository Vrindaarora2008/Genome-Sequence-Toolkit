#include <stdio.h>
#include "crt.h"
int main(void)
{
    long long residues[] = {2, 3, 2};
    long long moduli[] = {3, 5, 7};
    long long solution;
    long long combined_modulus;
    printf("Chinese Remainder Theorem Test\n");
    if (chinese_remainder_theorem(residues, moduli, 3, &solution, &combined_modulus))
    {
        printf("Solution: x = %lld\n", solution);
        printf("Combined modulus: %lld\n", combined_modulus);
        printf("\nVerification:\n");
        for (int i = 0; i < 3; i++)
        {
            printf("%lld mod %lld = %lld\n", solution, moduli[i], solution % moduli[i]);
        }
    }
    else
    {
        printf("No valid solution or invalid input.\n");
    }
    return 0;
}
