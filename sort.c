#include "sort.h"

void bubble_sort(int *data, unsigned int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i < j && data[i] > data[j]) {
                int tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
        }
    }
}

void insertion_sort(int *data, unsigned int n) {

}

void selection_sort(int *data, unsigned int n) {

}
