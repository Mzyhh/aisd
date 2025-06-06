#include <stdio.h>

#include "leftist_heap.h"

void print_tree(node *n) {
    if (!n) return;
    printf("(%d, %d) ", n->key, n->dist);
    print_tree(n->left);
    print_tree(n->right);
}

int main(int arc, char** argv) {
    int n = 5;
    int ar[] = {1, 0, -10, 4, 7};

    leftist_heap h = leftist_build(ar, n);
    printf("%d\n", leftist_get_max(&h));

    leftist_delete(&h, 7);
    printf("%d\n", leftist_get_max(&h));

    leftist_delete(&h, 0);
    printf("%d\n", leftist_get_max(&h));

    leftist_delete(&h, 4);
    printf("%d\n", leftist_get_max(&h));

    leftist_delete(&h, 1);
    printf("%d\n", leftist_get_max(&h));
    return 0;
}
