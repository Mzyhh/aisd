#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

typedef struct leftist_heap_node {
    struct leftist_heap_node *left, *right;
    int key, dist;
} node;

typedef struct {
    node *root;
} leftist_heap;

leftist_heap leftist_build(const int* numbers, int n);

void leftist_insert(leftist_heap* heap, int v);

int leftist_get_max(const leftist_heap* heap);

void leftist_delete_max(leftist_heap* heap);

void leftist_delete(leftist_heap* heap, int v);

#endif //LEFTIST_HEAP_H
