#include <stdio.h>
#include <stdlib.h>
#include "tree_23.h"

int main(void) {
    node_23 *root = NULL;
    root = add(root, 2);
    root = add(root, 3);
    root = add(root, 4);
    root = add(root, 0);
    root = add(root, 5);
    root = add(root, 1);
    root = add(root, 10);
    root = add(root, -1);
    root = add(root, 7);
    root = add(root, 100);
    print_node(root);
    print_node(root->left);
    print_node(root->left->left);
    print_node(root->left->right);
    print_node(root->right);
    print_node(root->right->left);
    print_node(root->right->right);
    printf("\n");   
    // root = add(root, 25);
    // root = add(root, 39);
    // root = add(root, 12);
    // root = add(root, -7);
    // root = add(root, 6);
    char *p = malloc(100*sizeof(char));
    print(root, p);
    printf("%s\n\n", p);
    return 0;
}
