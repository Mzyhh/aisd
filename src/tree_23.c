#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree_23.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void print_node(node_23 *node) {
    if (node->type == node_2) {
        printf("node_2:\nvalue_left = %d\nleft = %p\nright = %p\nself = %p\nparent = %p\n", 
        node->value_left, node->left, node->right, node, node->parent);
    } else {
        printf("node_3:\nvalue_left = %d\nvalue_right = %d\nleft = %p\nmiddle = %p\nright = %p\nself = %p\nparent = %p\n",
         node->value_left, node->value_right, node->left, node->middle, node->right, node, node->parent);
    }
    printf("\n");
}

int print_recursive(const node_23 *tree, char *result, size_t position) {
    if (!tree) return position;
    position = print_recursive(tree->left, result, position);
    position += sprintf(result + position, "%d ", tree->value_left);
    if (tree->type == node_3) {
        position = print_recursive(tree->middle, result, position);
        position += sprintf(result + position, "%d ", tree->value_right);
    }
    position = print_recursive(tree->right, result, position);
    return position;
}

void print(const node_23 *tree, char *result) {
    result[print_recursive(tree, result, 0) - (tree != NULL)] = '\0';
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

int get_nodes_with_key_between_recursive(const node_23 *tree, int key_min, int key_max, node_23 *res, size_t position) {
    if (!tree) return position;
    if (tree->value_left >= key_min)
        position = get_nodes_with_key_between_recursive(tree->left, key_min, key_max, res, position);

    if (tree->value_left >= key_min && tree->value_left < key_max || 
        tree->type == node_3 && 
        tree->value_right >= key_min && tree->value_right < key_max)
        res[position++] = *tree;

    if (tree->type == node_3 && key_max > tree->value_left && key_min <= tree->value_right)
        position = get_nodes_with_key_between_recursive(tree->middle, key_min, key_max, res, position);

    int value = tree->type == node_2 ? tree->value_left : tree->value_right;
    if (value < key_max)
        position = get_nodes_with_key_between_recursive(tree->right, key_min, key_max, res, position);
    return position;
}

void get_nodes_with_key_between(const node_23 *tree, int key_min, int key_max, node_23* res) {
    get_nodes_with_key_between_recursive(tree, key_min, key_max, res, 0);    
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
    node_23 *new_node = malloc(sizeof(node_23));
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
    node->middle2 = NULL;
}

node_23 *split(node_23 *node) {
    node_23 *right_child = node_4to2(node);
    node_23 *left_child = node;
    node_23 *parent = node->parent;
    if (!parent) { // node is root node
        node_23 *new_root = malloc(sizeof(node_23));
        new_root->type = node_2;
        new_root->value_left = node->value_middle;
        new_root->parent = NULL;
        left_child->parent = new_root;
        right_child->parent = new_root;
        new_root->left = left_child;
        new_root->right = right_child;
        if (right_child->left) {
            right_child->left->parent = right_child;
            right_child->right->parent = right_child;
        }
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
            parent->middle2 = parent->middle;
            parent->middle = right_child;
        } else if (parent->middle == node) {
            parent->middle2 = right_child;
        } else {
            parent->middle2 = left_child;
            parent->right = right_child;
        }
    }
    return node;
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
        node->middle = NULL;
        return tree;
    }

    node_3to4(node, value);
    while (node->type == node_4) {
        node = split(node);
        if (!node->parent) return node;
        node = node->parent;
    }
    return tree;
}
