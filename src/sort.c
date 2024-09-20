#include "sort.h"

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

}

void insertion_sort_optimized(int *data, const int n) {

}

void selection_sort(int *data, const int n) {

}

void shell_sort(int *data, const int n) {

}

void merge_sort(int *data, const int n) {

}

void merge_bottom_up_sort(int *data, const int n) {

}

void merge_sort_emulated_recursion(int *data, const int n) {

}
