#ifndef BIGNUM_H
#define BIGNUM_H

struct bignum {
    int* digits;
    int n;
};

struct bignum karatsuba_polynomial(struct bignum n1, struct bignum n2);

struct bignum karatsuba_binary_numbers(struct bignum n1, struct bignum n2);

#endif //BIGNUM_H
