#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

typedef struct splay_node {
    splay_node* l;
    splay_node* r;
    int v;
} splay_node;

const splay_node* splay_find(const splay_node *tree, int v, int* found);

const splay_node* splay_insert(const splay_node *tree, int v);

const splay_node* splay_remove(const splay_node *tree, int v);

void splay_traverse(const splay_node *tree, void (*callback)(int));

#endif //SPLAY_TREE_H
