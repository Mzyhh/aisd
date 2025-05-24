#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "treap.h"


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
    node* new_node = malloc(sizeof(node));
    new_node->key = k;
    new_node->prior = rand();
    new_node->left = NULL;
    new_node->right = NULL;
    node_ptr_pair p = split_treap(t->root, k);
    t->root = merge_treap(merge_treap(p.first, new_node), p.second);

 // if (!t->root) {
 //     t->root = new_node;
 //     return;
 // }
 // node* prev = NULL, *curr = t->root;
 // int lflag = 0;
 // while (curr && curr->prior >= new_node->prior) {
 //     prev = curr;
 //     if (k < curr->key) {
 //         curr = curr->left;
 //         lflag = 1;
 //     } else {
 //         curr = curr->right;
 //         lflag = 0;
 //     }
 // }
 // if (curr) {
 //     node_ptr_pair p = split_treap(curr, k);
 //     new_node->left = p.first;
 //     new_node->right = p.second;
 // }
 // if (prev) {
 //     if (lflag) prev->left = new_node;
 //     else prev->right = new_node;
 // } else {
 //     t->root = new_node;
 // }
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
    node *prev = NULL, *curr = treap->root;
    while (curr && curr->key != k) {
        prev = curr;
        if (k < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    if (!curr) return;
    node *merged = merge_treap(curr->left, curr->right);
    if (prev) {
        if (prev->right == curr) prev->right = merged;
        else prev->left = merged;
    } else {
        treap->root = merged;
    }
    //free(curr);
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
