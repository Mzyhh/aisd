#ifndef SORTS_H
#define SORTS_H

void swap(int *a, const int i, const int j);

void bubble_sort(int *data, int n);
void insertion_sort(int *data, int n);
void insertion_sort_optimized(int *data, int n);
void selection_sort(int *data, int n);
void shell_sort(int *data, int n);
void merge_sort(int *data, int n);
void merge_bottom_up_sort(int *data, int n);
void merge_sort_emulated_recursion(int *data, int n);

enum merge_sort_op { SORT, MERGE };
struct merge_sort_stack_frame {
    int l;
    int m; // used only for op MERGE
    int r;
    enum merge_sort_op op;
};

#endif //SORTS_H
