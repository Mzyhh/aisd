#include <stddef.h>

#include "tree_23.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


void print(const node_23 *tree, char *result) {
    result[0] = '\0';
}

/*
* Find for balanced 2-3 tree
*/
const node_23 *find(const node_23 *tree, int value) {
    if (!tree) return NULL;
    if (value < tree->value_left) return find(tree->left, value);
    int tmp = tree->type == node_2 ? tree->value_left : tree->value_right;
    if (value >= tmp) return find(tree->right, value);
    return find(tree->middle, value);
}

int_pair get_shortest_longest_path(const node_23 *tree) {
    int_pair res = {.n1 = 0, .n2 = 0};
    return res;
}

void get_nodes_with_key_between(const node_23 *tree, int key_min, int key_max, node_23 *res) {

}

/*
* Find position for balanced 2-3 tree
*/
node_23 *__find(node_23 *tree, int value) {
    if (!tree->left) return tree;
    if (value < tree->value_left) return __find(tree->left, value);
    int tmp = tree->type == node_2 ? tree->value_left : tree->value_right;
    if (value >= tmp) return __find(tree->right, value);
    return __find(tree->middle, value);
}

/*
*   Returns right produced node with type node_2
*/
node_23 *node_4to2(node_23 *node) {
    node_23 *new_node = calloc(1, sizeof(node_23));
    new_node->type = node_2;
    new_node->parent = node->parent;
    new_node->left = node->middle2;
    new_node->right = node->right;
    new_node->value_left = node->value_right;

    node->type = node_2;
    node->right = node->middle;

    return new_node;
}

void node_3to4(node_23 *node, int value) {
    if (value < node->value_left) {
        node->value_middle = node->value_left;
        node->value_left = value;
    } else if (value < node->value_right) {
        node->value_middle = value;
    } else {
        node->value_middle = node->value_right;
        node->value_right = value;        
    }
    node->type = node_4;
}

node_23 *split(node_23 *node, int value) {
    node_23 *right_child = node_4to2(node);
    node_23 *left_child = node;
    node_23 *parent = node->parent;
    if (!node->parent) { // node is root node
        node_23 *new_root = calloc(1, sizeof(node_23));
        new_root->type = node_2;
        new_root->value_left = node->value_middle;
        new_root->parent = NULL;
        node->parent = new_root;
        new_root->left = node;
        new_root->right = right_child;
        return new_root;
    }
    if (parent->type == node_2) {
        parent->type = node_3;
        if (parent->left == node) {
            parent->value_right = parent->value_left;
            parent->value_left = node->value_middle;
            parent->left = left_child;
            parent->middle = right_child;
        } else {
            parent->value_right = node->value_middle;
            parent->middle = left_child;
            parent->right = right_child;
        }
    } else {
        node_3to4(parent, node->value_middle);
        if (parent->left == node) {
            parent->middle2 = node->parent->middle;
            parent->middle = right_child;
        } else if (parent->middle == node) {
            parent->middle2 = right_child;
        } else {
            parent->middle2 = left_child;
            parent->right = right_child;
        }
    }
    return parent;
}

node_23 *add(node_23 *tree, int value) {
    if (!tree) { // empty tree
        tree = malloc(sizeof(node_23));
        tree->type = node_2;
        tree->value_left = value;
        tree->left = tree->right = tree->parent = NULL;
        return tree;
    }

    if (find(tree, value)) return tree; // tree already contains value

    node_23 *node = __find(tree, value);
    if (node->type == node_2) {
        if (node->value_left < value) {
            node->value_right = value;
        } else {
            node->value_right = node->value_left;
            node->value_left = value;
        }
        node->type = node_3;
        return tree;
    }

    node_3to4(node, value);
    while (node->type = node_4) {
        node = split(node, value);
        if (!node->parent) return node;
    }
    return tree;
}
