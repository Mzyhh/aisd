#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct {
    int* digits;
    int n;
} bignum;

bignum karatsuba_polynomial(struct bignum n1, struct bignum n2);

bignum karatsuba_binary_numbers(struct bignum n1, struct 

#endif //BIGNUM_H
