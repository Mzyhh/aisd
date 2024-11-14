#include "nth_element.h"
#include "sort.h"
#include <stdlib.h>

/**
 *This function generate random integer number in semi-interval [l, r).
 *There is no calling srand() function inside it.
 *@param l The left border of the semi-interval
 *@param r The right border of the semi-interval
 */
int rand_in(const int l, const int r) {
    return rand() % (r - l) + l;
}

int partition(int *data, int l, int r, int p) {
    swap(data, p, r - 1);
    const int pivot = data[r - 1];
    int i = l - 1;
    for (int  j = l; j < r - 1; ++j) {
        if (data[j] < pivot) {
            ++i;
            swap(data, i, j);
        }
    }
    swap(data, i + 1, r - 1);
    return i + 1;
}

void quicksort(int *data, int l, int r) {
    if (l < r) {
        const int p = partition(data, l, r, rand_in(l, r));
        quicksort(data, l, p);
        quicksort(data, p + 1, r);
    }
}

int quick_select_recursive(int *data, int l, int r, int k) {
    const int p = partition(data, l, r, rand_in(l, r));
    if (p == k) {
        return data[p];
    }
    if (p < k) {
        return quick_select_recursive(data, p + 1, r, k);
    }
    return quick_select_recursive(data, l, p, k);
}

int quick_select(int *data, int n, int k) {
    return quick_select_recursive(data, 0, n, k);
}

int partition5(int *data, int l, int r) {
    quicksort(data, l, r);
    return (l + r) / 2;
}

int pivot(int *data, int l, int r) {
    if (r - l <= 5) {
        return partition5(data, l, r);
    }

    for (int i = l; i < r; i += 5) {
        const int m = partition5(data, i, i + 5 < r ? i + 5 : r);
        swap(data, l + (i - l) / 5, m);
    }
    r = l + (r - l) / 5;
    const int m = select0(data, l, r, (l + r) / 2);
    return m;
}

int select0(int *data, int l, int r, int k) {
    const int p = pivot(data, l, r);
    const int m = partition(data, l, r, p);
    if (k == m) {
        return m;
    }
    if (m > k) {
        return select0(data, l, m, k);
    }
    return select0(data, m + 1, r, k);
}

int median_of_median(int *data, int n, int k) {
    return data[select0(data, 0, n, k)];
}
