#ifndef NTH_SMALLEST_H
#define NTH_SMALLEST_H


int quick_select(int *data, int n, int k);
int median_of_median(int *data, int n, int k);
int partition(int *data, int l, int r, int p);
int select0(int *data, int l, int r, int k);

#endif //NTH_SMALLEST_H
