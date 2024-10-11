#include "sort.h"
#include <stdlib.h>
#include <math.h>

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

void swap(int *a, const int i, const int j) {
    const int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void bubble_sort(int *data, const int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (data[j] > data[j + 1]) {
                swap(data, j, j + 1);
            }
        }
    }
}

void insertion_sort(int *data, const int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (data[j] >= data[j-1]) {
                break;
            }
            swap(data, j, j-1);
        }
    }
}

void insertion_sort_optimized(int *data, const int n) {

}

void selection_sort(int *data, const int n) {
    for (int i = 0; i < n; i++) {
        int min = data[i], index = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j] < min) {
                min = data[j];
                index = j;
            }
        }
        swap(data, i, index);
    }
}

int* pratt_sequence(const int n) {
    const int size = (((int)log2((double)n/2)) + 2)*(((int)log2(n)))/2;
    int* sequence = (int*)malloc(sizeof(int)*(size + 1));
    int count = 1;
    sequence[1] = 1;
    int i2 = 1, i3 = 1;
    int n2, n3;
    while (1) {
        n2 = 2 * sequence[i2];
        n3 = 3 * sequence[i3];
        if (MIN(n2, n3) > n/2) {
            break;
        }
        if (count >= size) {
            sequence[0] = count;
            return sequence;
        }
        sequence[++count] = MIN(n2, n3);
        i2 += n2 <= n3 ? 1 : 0;
        i3 += n2 >= n3 ? 1 : 0;
    }
    sequence[0] = count;
    return sequence;
}

void shell_sort(int *data, const int n) {
    int* s = pratt_sequence(n);
    for (int i = s[0]; i > 0; --i) {
        const int step = s[i];
        for (int j = step; j < n; j += 1) {
            const int temp = data[j];
            int k;
            for (k = j; k >= step && data[k - step] > temp; k -= step) {
                data[k] = data[k - step];
            }
            data[k] = temp;
        }
    }
    free(s);
}

void merge(int *data, const int l, const int m, const int r) {
    int i = 0, j = 0;
    int *tmp = (int*)malloc(sizeof(int)*(r - l));
    while (i < m - l && j < r - m) {
        if (data[i + l] < data[j + m]) {
            tmp[i + j] = data[i + l];
            i++;
        } else {
            tmp[i + j] = data[j + m];
            j++;
        }
    }
    while (i < m - l) {
        tmp[i + j] = data[i + l];
        i++;
    }
    while (j < r - m) {
        tmp[i + j] = data[j + m];
        j++;
    }
    for (int k = 0; k < r - l; k++) {
        data[l + k] = tmp[k];
    }
    free(tmp);
}

void merge_sort_recursive(int *data, const int l, const int r) {
    if (r - l <= 1) {
        return;
    }
    const int m = (l + r) / 2;
    merge_sort_recursive(data, l, m);
    merge_sort_recursive(data, m, r);
    merge(data, l, m, r);
}

void merge_sort(int *data, const int n) {
    merge_sort_recursive(data, 0, n);
}

void merge_bottom_up_sort(int *data, const int n) {
    for (int size = 1; size <= n - 1; size *= 2) {
        for (int l = 0; l < n - 1; l += 2*size) {
            const int m = MIN(l + size, n);
            const int r = MIN(l + 2*size, n);
            merge(data, l, m, r);
        }
    }
}

void push(struct merge_sort_stack_frame* stack, int* size, const int l, const int m, const int r, enum merge_sort_op op) {
    const struct merge_sort_stack_frame el = {.l = l, .r = r, .m = m, .op = op};
    stack[*size] = el;
    *size += 1;
}

void merge_sort_emulated_recursion(int *data, const int n) {
    struct merge_sort_stack_frame* stack = (struct merge_sort_stack_frame*)malloc(sizeof(struct merge_sort_stack_frame) * n * ceil(log2(n+1))*2 + 2);
    int size = 0;
    push(stack, &size, 0, -1, n, SORT);
    while (size > 0) {
        const struct merge_sort_stack_frame frame = stack[--size];
        if (frame.op == SORT) {
            if (frame.r - frame.l <= 1) {
                continue;
            }
            const int m = (frame.l + frame.r) / 2;
            push(stack, &size, frame.l, m, frame.r, MERGE);
            push(stack, &size, frame.l, -1, m, SORT);
            push(stack, &size, m, -1, frame.r, SORT);
        }
        if (frame.op == MERGE) {
            merge(data, frame.l, frame.m, frame.r);
        }
    }
    free(stack);
}
