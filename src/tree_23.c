#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "tree_23.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


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

const node_23 *find(const node_23 *tree, int value) {
    if (!tree) return NULL;
    if (value == tree->value_left || (tree->type == node_3 && tree->value_right == value)) return tree;
    if (value < tree->value_left) return find(tree->left, value);
    int tmp = tree->type == node_2 ? tree->value_left : tree->value_right;
    if (value >= tmp) return find(tree->right, value);
    return find(tree->middle, value);
}

int_pair base_case = {INT_MAX, INT_MIN};

int_pair get_shortest_longest_path(const node_23 *tree) {
    int_pair result = {0, 0};
    if (!tree->left && !tree->right && (tree->type == node_2 || !tree->middle)) return result;
    int_pair left, middle, right;
    left = middle = right = base_case;
    left = get_shortest_longest_path(tree->left);
    middle = tree->type == node_3 ? get_shortest_longest_path(tree->middle) : middle;
    right = get_shortest_longest_path(tree->right);
    result.n1 = MIN(MIN(left.n1, middle.n1), right.n1) + 1;
    result.n2 = MAX(MAX(left.n2, middle.n2), right.n2) + 1;
    return result;
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

node_23 *__find(node_23 *tree, int value) {
    if (!tree->left) return tree;
    if (value < tree->value_left) return __find(tree->left, value);
    int tmp = tree->type == node_2 ? tree->value_left : tree->value_right;
    if (value >= tmp) return __find(tree->right, value);
    return __find(tree->middle, value);
}

typedef struct node_4 {
    node_23 *n;
    int value_middle;
    struct node_23 *middle2;
} node_4;

node_23 *node_4to2(node_4 *node) {
    node_23 *new_node = malloc(sizeof(node_23));
    new_node->type = node_2;
    new_node->parent = node->n->parent;
    new_node->left = node->middle2;
    new_node->right = node->n->right;
    new_node->value_left = node->n->value_right;

    node->n->type = node_2;
    node->n->right = node->n->middle;

    return new_node;
}

node_4 *node_3to4(node_23 *node, int value) {
    node_4 *res = (node_4*)malloc(sizeof(node_4));
    res->n = node;
    if (value < node->value_left) {
        res->value_middle = res->n->value_left;
        res->n->value_left = value;
    } else if (value < node->value_right) {
        res->value_middle = value;
    } else {
        res->value_middle = res->n->value_right;
        res->n->value_right = value;     
    }
    res->middle2 = NULL;
    return res;
}

node_23 *split(node_4 **container) {
    node_4 *node4 = *container;
    node_23 *node23 = node4->n;
    node_23 *right_child = node_4to2(node4);
    node_23 *left_child = node4->n;
    node_23 *parent = node4->n->parent;
    if (right_child->left) {
            right_child->left->parent = right_child;
            right_child->right->parent = right_child;
    }
    if (!parent) { // node is root node
        node_23 *new_root = malloc(sizeof(node_23));
        new_root->type = node_2;
        new_root->value_left = node4->value_middle;
        new_root->parent = NULL;
        left_child->parent = new_root;
        right_child->parent = new_root;
        new_root->left = left_child;
        new_root->right = right_child;
        free(node4);
        *container = NULL;
        return new_root;
    }
    if (parent->type == node_2) {
        parent->type = node_3;
        if (parent->left == node23) {
            parent->value_right = parent->value_left;
            parent->value_left = node4->value_middle;
            parent->left = left_child;
            parent->middle = right_child;
        } else {
            parent->value_right = node4->value_middle;
            parent->middle = left_child;
            parent->right = right_child;
        }
        *container = NULL;
    } else {
        node_4 *parent4 = node_3to4(parent, node4->value_middle);
        if (parent->left == node23) {
            parent4->middle2 = parent->middle;
            parent->middle = right_child;
        } else if (parent->middle == node23) {
            parent4->middle2 = right_child;
        } else {
            parent4->middle2 = left_child;
            parent->right = right_child;
        }
        *container = parent4;
    }
    free(node4);
    return node23;
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

    node_4 *tmp = node_3to4(node, value);
    while (tmp) {
        node = split(&tmp);
        if (!node->parent) return node;
    }
    return tree;
}