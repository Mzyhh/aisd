#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct {
    int* digits;
    int n;
} bignum;

bignum karatsuba_polynomial(bignum n1, bignum n2);

bignum karatsuba_binary_numbers(bignum n1, bignum n2); 

#endif //BIGNUM_H
