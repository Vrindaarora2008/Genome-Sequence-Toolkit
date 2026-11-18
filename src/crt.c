#include <stdio.h>
#include <limits.h>
#include "crt.h"
static long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
static long long extended_gcd(
    long long a,
    long long b,
    long long *x,
    long long *y
)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}
static int modular_inverse(
    long long a,
    long long m,
    long long *inverse
)
{
    long long x, y;
    long long g = extended_gcd(a, m, &x, &y);
    if (g != 1)
        return 0;
    *inverse = x % m;
    if (*inverse < 0)
        *inverse += m;
    return 1;
}
static long long multiply_mod(
    long long a,
    long long b,
    long long mod
)
{
    long long result = 0;
    a %= mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            if (result >= mod - a)
                result -= mod - a;
            else
                result += a;
        }
        if (a >= mod - a)
            a -= mod - a;
        else
            a += a;
        b /= 2;
    }
    return result;
}
int chinese_remainder_theorem(
    const long long residues[],
    const long long moduli[],
    size_t n,
    long long *solution,
    long long *combined_modulus
)
{
    if (residues == NULL || moduli == NULL || solution == NULL || combined_modulus == NULL || n == 0 || n > CRT_MAX_EQUATIONS)
    {
        return 0;
    }
    long long x = 0;
    long long M = 1;
    for (size_t i = 0; i < n; i++)
    {
        if (moduli[i] <= 1)
            return 0;
        for (size_t j = 0; j < i; j++)
        {
            if (gcd(moduli[i], moduli[j]) != 1)
                return 0;
        }
        if (M > LLONG_MAX / moduli[i])
            return 0;
        long long m = moduli[i];
        long long r = residues[i] % m;
        if (r < 0)
            r += m;
        long long current = x % m;
        long long difference;
        if (r >= current)
            difference = r - current;
        else
            difference = m - (current - r);
        long long inverse;
        if (!modular_inverse(M % m, m, &inverse))
            return 0;
        long long k = multiply_mod(difference, inverse, m);
        x += M * k;
        M *= m;
    }
    *solution = x;
    *combined_modulus = M;
    return 1;
}
