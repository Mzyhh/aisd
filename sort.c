#include "sort.h"

void swap(int *a, unsigned int i, unsigned int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void bubble_sort(int *data, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (data[j] > data[j + 1]) {
                swap(data, j, j + 1);
            }
        }
    }
}

void insertion_sort(int *data, int n) {

}

void selection_sort(int *data, int n) {

}

int *merge_sort(int *data, int n) {

}
