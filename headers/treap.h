#ifndef TREAP_H
#define TREAP_H

typedef struct treap_node {
    int key, prior;
    struct treap_node *left, *right;
} node;

typedef struct treap{
    node *root;
} treap;

typedef struct {
    node *first, *second;
} node_ptr_pair;

treap build_treap(const int* numbers, int n);

void add_number(treap* treap, int v);

void delete_number(treap* treap, int v);

int get_numbers_count(const treap* treap, int l, int r);

void iterate_treap(const treap* treap, void (*callback)(int));

void iterate_statistics(const treap* treap, int k, int m, void (*callback)(int));

node_ptr_pair split_treap(node *t, int k);

node *merge_treap(node *t1, node *t2);

#endif //TREAP_H
