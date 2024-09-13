//
// Created by mrak1990 on 13.09.2024.
//

#include "sorts.h"

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

void selection_sort(int *data, unsigned int n) {

}
