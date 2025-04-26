#ifndef TREAP_H
#define TREAP_H

typedef struct {

} treap;

treap build_treap(const int* numbers, int n);

void add_number(treap* treap, int v);

void delete_number(treap* treap, int v);

int get_numbers_count(const treap* treap, int l, int r);

void iterate_treap(const treap* treap, void (*callback)(int));

void iterate_statistics(const treap* treap, int k, int m, void (*callback)(int));

#endif //TREAP_H
