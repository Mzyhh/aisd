#include <stdlib.h>

#include "leftist_heap.h"


static void node_swap_children_(node *n) {
    node *tmp = n->left;
    n->left = n->right;
    n->right = tmp;
}

static int dist_(node *n) {
    if (!n) return 0;
    return n->dist;
}

static node *create_empty_node_(const int key) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->key = key;
    new_node->dist = 0;
    new_node->left = new_node->right = NULL;
    return new_node;
}

static node *merge(node *x, node *y) {
    if (!x) return y;
    if (!y) return x;
    if (y->key > x->key)
        return merge(y, x);
    x->right = merge(x->right, y);
    if (dist_(x->right) >= dist_(x->left))
        node_swap_children_(x);
    x->dist = x->right ? 1 + dist_(x->right) : 0;
    return x;
}

leftist_heap leftist_build(const int* numbers, int n) {
    leftist_heap res = {NULL};
    if (!numbers || n <= 0) return res;
    node **heaps = (node**)malloc(n * sizeof(node*));
    for (int i = 0; i < n; i++)
        heaps[i] = create_empty_node_(numbers[i]);
    while (n > 1) {
        for (int i = 0; i + 1 < n; i += 2)
            heaps[i / 2] = merge(heaps[i], heaps[i + 1]);
        if (n % 2 == 1) {
            heaps[n / 2] = heaps[n - 1];
            n = (n + 1) / 2;
        } else {
            n = n / 2;
        }
    }
    res.root = heaps[0];
    free(heaps);
    return res;
}

void leftist_insert(leftist_heap* heap, int k) {
    heap->root = merge(heap->root, create_empty_node_(k));
}
 
int leftist_get_max(const leftist_heap* heap) {
    if (!heap || !heap->root) return -1;
    return heap->root->key;
}

void leftist_delete_max(leftist_heap* heap) {
    if (!heap || !heap->root) return;
    node *to_delete = heap->root;
    heap->root = merge(heap->root->left, heap->root->right);
    free(to_delete);
}

static node *decrease_key_(node *x, int val, int *is_found) {
    if (!x) return NULL;
    if (*is_found) return x;
    if (x->key == val) {
        *is_found = 1;
        node *merged = merge(x->left, x->right);
        free(x);
        return merged;
    } 
    x->left = decrease_key_(x->left, val, is_found);
    x->right = decrease_key_(x->right, val, is_found);
    if (!x->left || dist_(x->left) < dist_(x->right))
        node_swap_children_(x);
    if (!x->right) x->dist = 0;
    else x->dist = dist_(x->right) + 1;
    return x;
}

void leftist_delete(leftist_heap* heap, int v) {
    if (!heap || !heap->root) return;
    int is_found = 0;
    heap->root = decrease_key_(heap->root, v, &is_found);
}
