#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct user {
    const int key;
    const char *const data;
} user;

typedef struct node {
    const struct node *const l;
    const struct node *const r;
    const user d;
} node;

const node* insert(const node *tree, user data);

const node* remove(const node *tree, int key);

const node* find(const node *tree, int key);

void traverse(const node *tree, void (*callback)(user));

const node* rotate_left(const node *tree, int key);

const node* rotate_right(const node *tree, int key);

#endif //BINARY_TREE_H
