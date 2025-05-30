#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "treap.h"


static node* find_treap_node(node *root, int k) {
    while (root && root->key != k) {
        if (k < root->key) root = root->left;
        else root = root->right;
    }
    return root;
}

node_ptr_pair split_treap(node *t, int k) {
    node_ptr_pair res = {NULL, NULL};
    if (t == NULL) return res;
    if (k > t->key) {
        res = split_treap(t->right, k);
        t->right = res.first;
        res.first = t;
        return res;
    }
    res = split_treap(t->left, k);
    t->left = res.second;
    res.second = t;
    return res;
}

node *merge_treap(node *t1, node *t2) {
    if (!t2) return t1;
    if (!t1) return t2;
    if (t1->prior > t2->prior) {
        t1->right = merge_treap(t1->right, t2);
        return t1;
    } else {
        t2->left = merge_treap(t1, t2->left);
        return t2;
    }
}

void add_number(treap* t, int k) {
    node *curr = find_treap_node(t->root, k);
    if (curr) return;

    node* new_node = malloc(sizeof(node));
    new_node->key = k;
    new_node->prior = rand();
    new_node->left = NULL;
    new_node->right = NULL;
    node_ptr_pair p = split_treap(t->root, k);
    t->root = merge_treap(merge_treap(p.first, new_node), p.second);
}

treap build_treap(const int* numbers, int n) {
    srand(time(NULL));
    treap res = {NULL};
    for (int i = 0; i < n; ++i) {
        add_number(&res, numbers[i]);
    }
    return res;
}

void delete_number(treap* treap, int k) {
    node *curr = find_treap_node(treap->root, k);
    if (!curr) return;

    node_ptr_pair p1 = split_treap(treap->root, k);
    node_ptr_pair p2 = split_treap(p1.second, k + 1);
    treap->root = merge_treap(p1.first, p2.second);
    free(curr);
}

static int get_numbers_count_recursive_(node *n, int l, int r) {
    if (!n) return 0;
    if (n->key < l) 
        return get_numbers_count_recursive_(n->right, l, r);
    if (n->key >= r) 
        return get_numbers_count_recursive_(n->left, l, r);

    return get_numbers_count_recursive_(n->left, l, r) + 
           get_numbers_count_recursive_(n->right, l, r) + 1;
}

int get_numbers_count(const treap* treap, int l, int r) {
    return get_numbers_count_recursive_(treap->root, l, r);
}

void iterate_treap_recursive_(node* n, void (*callback)(int)) {
    if (!n) return;
    iterate_treap_recursive_(n->left, callback);
    callback(n->key);
    iterate_treap_recursive_(n->right, callback);
}

void iterate_treap(const treap* treap, void (*callback)(int)) {
    iterate_treap_recursive_(treap->root, callback);
}

void iterate_statistics(const treap* treap, int k, int m, void (*callback)(int)) {

}
