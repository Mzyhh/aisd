#include <stdio.h>
#include "sort.h"
#include "nth_element.h"

int main(void) {
    setbuf(stdout, NULL);

    int input[] = {10, 3, 50, 4, 6, 7, 8, 9, 10, 6, 11, 13, 14, 15};
    int size = sizeof(input) / sizeof(input[0]);
    printf("Before partitioning:\n");
    for (int i = 0; i < size; i++) {
        printf("input[%d] = %d\n", i, input[i]);
    }

    // int p = partition(input, 0, size);
    // printf("After partitioning:\n");
    // printf("pivot = %d\n", p);
    // for (int i = 0; i < size; i++) {
    //     printf("input[%d] = %d\n", i, input[i]);
    // }

    for (int i = 0; i < size; ++i) {
        printf("stat(%d) = %d\n", i, quick_select(input, size, i));

    }

    return 0;
}
