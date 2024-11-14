#include "bignum.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Generate new bignum that is num with size - num.n zeros in last digits
 */
int *expandWithZeros(const bignum num, const int size) {
    int *result = calloc(size, sizeof(int));
    memcpy(result, num.digits, num.n*sizeof(int));
    return result;
}

int binPowerSuccessor(const int n) {
    return 1 << (int)(ceil(log2(n)));
}

void handleOverflow(bignum num, const int base) {
    int acc = 0;
    for (int i = 0; i < num.n; ++i) {
        const int c = num.digits[i] + acc;
        num.digits[i] = c % base;
        acc = c / base;
    }
}

void karatsuba(const int* const a, const int* const b, int* const result, const int n) {
    if (n == 1) {
        result[0] += a[0] * b[0];
        return;
    }
    const int k = n / 2;
    int *sum1 = calloc(k, sizeof(int)), 
        *sum2 = calloc(k, sizeof(int)),
        *tmp  = calloc(n, sizeof(int));
    
    karatsuba(a, b, result, k);
    karatsuba(a + k, b + k, result + n, k);

    for (int i = 0; i < k; ++i) {
        sum1[i] = a[i] + a[k + i];
        sum2[i] = b[i] + b[k + i];
    }
    karatsuba(sum1, sum2, tmp, k);
    free(sum1);
    free(sum2);

    for (int i = 0; i < k; ++i) {
        const int p = tmp[i] - result[2*k + i] - result[i];
        const int q = tmp[k + i] - result[k + i] - result[3*k + i]; 
        result[k + i] += p;
        result[n + i] += q;
    }
    free(tmp);
}

bignum karatsuba_polynomial(bignum n1, bignum n2) {
    const int n = binPowerSuccessor(n1.n > n2.n ? n1.n : n2.n);   
    int *a = expandWithZeros(n1, n),
        *b = expandWithZeros(n2, n),
        *c = calloc(2*n, sizeof(int));
    karatsuba(a, b, c, n);
    free(a);
    free(b);

    bignum result = {.digits = realloc(c, (n1.n + n2.n - 1) * sizeof(int)), 
                     .n      = n1.n + n2.n - 1};
    return result;
}

bignum karatsuba_binary_numbers(bignum n1, bignum n2) {
    const int n = binPowerSuccessor(n1.n > n2.n ? n1.n : n2.n);   
    int *a = expandWithZeros(n1, n),
        *b = expandWithZeros(n2, n),
        *c = calloc(2*n, sizeof(int));
    bignum result = {.digits = c, .n = 2*n};
    karatsuba(a, b, c, n);
    free(a);
    free(b);

    handleOverflow(result, 2);
    result.n = n1.n + n2.n - (c[n1.n + n2.n - 1] == 1 ? 0 : 1);
    result.digits = realloc(c, result.n * sizeof(int));
    return result;
}
