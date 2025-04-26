#ifndef DISTINCT_NUMBERS_H
#define DISTINCT_NUMBERS_H

typedef struct {

} container;

container build_structure(const int* numbers, int n);

int get_distinct_number_count(const container* container, int l, int r);

#endif //DISTINCT_NUMBERS_H
