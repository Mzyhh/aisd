#ifndef TREE_23_H
#define TREE_23_H

typedef enum {
    node_2,
    node_3,
    node_4,
} node_type;

/*
 * 2-node:
 * type = node_2
 * middle - undefined
 * middle2 - undefined
 * value_right - undefined
 * value_middle - undefined
 *
 * 3-node:
 * type = node_3
 * middle2 - undefined
 * value_middle - undefined
 * 
 * 4-node:
 * type = node_4
 */
typedef struct node_23 {
    struct node_23 *parent;
    struct node_23 *left;
    struct node_23 *middle;
    struct node_23 *middle2;
    struct node_23 *right;
    int value_left;
    int value_middle;
    int value_right;
    node_type type;
} node_23;

void print(const node_23 *tree, char* result);

const node_23 *find(const node_23 *tree, int value);

typedef struct int_pair {
    int n1;
    int n2;
} int_pair;

int_pair get_shortest_longest_path(const node_23 *tree);

/*
 * Get all nodes with key_min <= key < key_max
 * node_23* res is array with capacity 1000
 */
void get_nodes_with_key_between(const node_23 *tree, int key_min, int key_max, node_23* res);

node_23 *add(node_23 *tree, int value);

void print_node(node_23 *node);

#endif //TREE_23_H
