#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <limits.h>

#define NO_DEFERRED INT_MAX
#define NO_VALUE INT_MIN

typedef struct {
    int value;
    int deferred;
} node;

typedef struct {
    node* array; // origin array(crown) + ancestors
    int n; // half length of array
} segment_tree;

segment_tree build_segment_tree(const int* numbers, const int n);

int get_max(segment_tree* tree, int l, int r);

// numbers[i] = min(numbers[i], v), i = l ... r
void set_min(segment_tree* tree, int l, int r, int v);

#endif //SEGMENT_TREE_H
