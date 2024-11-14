#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "nth_element.h"
#include "bignum.h"

void printArray(const int* const array, const int n) {
    for (int i = 0; i < n; ++i)
        printf("array[%d] = %d\n", i, array[i]);
}

int main(void) {
    int a[] = {0};
    int b[] = {0};
    bignum n1 = {a, 1},
           n2 = {b, 1};
    bignum result = karatsuba_binary_numbers(n1, n2);
    printf("a:\n");
    printArray(a, 1);
    printf("b:\n");
    printArray(b, 1);
    printf("c:\n");
    printArray(result.digits, 2);
    return 0;
}
