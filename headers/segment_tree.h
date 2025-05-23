#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

typedef struct {
    int* array; // origin array(crown) + ancestors
    int n; // half length of array
} segment_tree;

segment_tree build_segment_tree(const int* numbers, const int n);

int get_max(segment_tree* tree, int l, int r);

// numbers[i] = min(numbers[i], v), i = l ... r
void set_min(segment_tree* tree, int l, int r, int v);

#endif //SEGMENT_TREE_H
