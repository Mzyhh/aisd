#include <stdio.h>
#include "segment_tree.h"

void print_list(const int* ar, const int n) {
    for (int i = 0; i < n; ++i) 
        printf("%d ", ar[i]);
    printf("\n");
}

int main(int arc, char** argv) {
    int n = 11;
    int ar[] = {1, 0, -10, 4, 7, 12, 100, -11, 17, 1, 5};
    print_list(ar, n);
    segment_tree t = build_segment_tree(ar, n);
    print_list(t.array, 2*t.n);
    int l, r, v, lm, rm;
    sscanf(argv[1], "%d", &l);
    sscanf(argv[2], "%d", &r);
    sscanf(argv[3], "%d", &v);
    sscanf(argv[4], "%d", &lm);
    sscanf(argv[5], "%d", &rm);
    set_min(&t, l, r, v);
    print_list(t.array, 2*t.n);
    printf("%d\n", get_max(&t, lm, rm));
    return 0;
}
