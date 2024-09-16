#include <stdio.h>
#include "sort.h"

int main(void) {
    setbuf(stdout, NULL);
    printf("Hello, World!\n");

    int input[] = {5, 3, 2, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int size = sizeof(input) / sizeof(input[0]);
    printf("Before sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("input[%d] = %d\n", i, input[i]);
    }
    bubble_sort(input, size);
    printf("After sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("input[%d] = %d\n", i, input[i]);
    }

    return 0;
}
