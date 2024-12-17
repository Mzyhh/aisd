#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tree_23.h"

void print_node(node_23 *node) {
    if (node->type == node_2) {
        printf("node_2:\nvalue_left = %d\n", node->value_left);
        if (node->left)
            printf("left = %d\nright = %d\n", node->left->value_left, node->right->value_left);
        if (node->parent)
            printf("parent = %d\n", node->parent->value_left);
    } else {
        printf("node_3:\n");
        printf("value_left = %d\nvalue_right = %d\n", node->value_left, node->value_right);
        if (node->left)
            printf("left = %d\nmiddle = %d\nright = %d\n", node->left->value_left, node->middle->value_left, node->right->value_left);
        if (node->parent)
            printf("parent = %d\n", node->parent->value_left);
    }
    printf("\n");
}

void print_all_nodes(node_23 *tree) {
    if (!tree) return;
    print_node(tree);
    print_all_nodes(tree->left);
    if (tree->type == node_3)
        print_all_nodes(tree->middle);
    print_all_nodes(tree->right);
}

int main(void) {
    srand(time(NULL));
    node_23 *root = NULL;
    int n;
    scanf("%d", &n);
    int *number = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        number[i] = rand() % 1000;
        root = add(root, number[i]);
    }
    char *res = malloc(100000*sizeof(char));
    print(root, res);
    printf("\n%s\n\n", res);
    print_all_nodes(root);
    int_pair p = get_shortest_longest_path(root);
    printf("%d %d", p.n1, p.n2);
    return 0;
}
