#include "nth_element.h"
#include "sort.h"
#include <stdlib.h>


int partition(int *data, int l, int r, int p) {
    swap(data, p, r);
    const int pivot = data[r];
    int i = l - 1;
    for (int  j = l; j < r; ++j) {
        if (data[j] < pivot) {
            ++i;
            swap(data, i, j);
        }
    }
    swap(data, i + 1, r);
    return i + 1;
}

int quick_select_recursive(int *data, int l, int r, int k) {
    if (l == r) {
        return data[l];
    }
    const int p = partition(data, l, r, rand() % (r - l + 1) + l);
    if (p == k) {
        return data[p];
    }
    if (p < k) {
        return quick_select_recursive(data, p + 1, r, k);
    }
    return quick_select_recursive(data, l, p - 1, k);
}

int quick_select(int *data, int n, int k) {
    return quick_select_recursive(data, 0, n - 1, k);
}

int median_of_median(int *data, int n, int k) {

}
