#include "segment_tree.h"
#include <memory.h>
#include <stdlib.h>
#include <math.h>


static int closest_bigger_2pow(int n) {
    if ((n & (n - 1)) == 0)
        return n;
    return 1 << (int)(ceil(log2(n)));
}

int min_int(const int a, const int b) {
    return a > b ? b : a;
}

int max_int(const int a, const int b) {
    return a > b ? a : b;
}

int (*masop)(const int, const int) = min_int;
int (*mainop)(const int, const int) = max_int;

static int actual_value(const segment_tree* tree, int i) {
    return masop(tree->array[i].value, tree->array[i].deferred);
}

/**
* Build segment tree from array `numbers` of length `n`
*
* @param numbers Target array
* @param n Size of array `numbers`
*/
segment_tree build_segment_tree(const int* numbers, const int n) {
    segment_tree result = {NULL};
    if (!numbers || n <= 0) return result;

    result.n = closest_bigger_2pow(n);
    result.array = malloc(result.n * 2 * sizeof(node));
    for (int i = 0; i < 2 * result.n; ++i) {
        if (result.n <= i && i < result.n + n)
            result.array[i].value = numbers[i - result.n];
        else
            result.array[i].value = NO_VALUE;
        result.array[i].deferred = NO_DEFERRED;
    }
    for (int i = result.n - 1; i > 0; --i)
        result.array[i].value = mainop(result.array[2 * i].value, result.array[2 * i + 1].value);
    return result;
}

static void push_deferred(segment_tree* tree, int i) {
    if (!tree || i >= tree->n || tree->array[i].deferred == NO_DEFERRED) return;
    tree->array[2 * i].deferred = masop(tree->array[2 * i].deferred,
                                        tree->array[i].deferred); 
    tree->array[2 * i + 1].deferred = masop(tree->array[2 * i + 1].deferred,
                                            tree->array[i].deferred); 
    tree->array[i].deferred = NO_DEFERRED; 
}

static int get_max_recursive_(segment_tree *tree, int node, int nl, int nr, int l, int r) {
    if (!tree || node >= tree->n * 2 || nr < l || nl > r) return NO_VALUE;
    if (l <= nl && nr <= r) {
        return actual_value(tree, node);
    }
    push_deferred(tree, node);
    int mid = (nl + nr) / 2;
    int ans = mainop(get_max_recursive_(tree, 2 * node, nl, mid, l, r), 
              get_max_recursive_(tree, 2 * node + 1, mid + 1, nr, l, r));
    tree->array[node].value = mainop(actual_value(tree, 2 * node), actual_value(tree, 2 * node + 1));

    return ans;
}
/**
 * Return maximum value on segment [l, r].
 *
 * @param tree Segment tree containing target array
 * @param l Left border of segment (array indexing)
 * @param r Right border of segment (array indexing)
 */
int get_max(segment_tree* tree, int l, int r) {
    return get_max_recursive_(tree, 1, 0, tree->n - 1, l, r);
}

static void set_min_recursive_(segment_tree *tree, int node, int nl, int nr, int l, int r, int v) {
    if (!tree || node >= tree->n * 2) return;
    if (nr < l || nl > r)  return;
    if (l <= nl && nr <= r) {
        tree->array[node].deferred = masop(tree->array[node].deferred, v);
        return;
    }

    int mid = (nl + nr) / 2;
    push_deferred(tree, node);
    set_min_recursive_(tree, 2 * node, nl, mid, l, r, v);
    set_min_recursive_(tree, 2 * node + 1, mid + 1, nr, l, r, v);
    tree->array[node].value = mainop(actual_value(tree, 2 * node), actual_value(tree, 2 * node + 1));
}

/**
* Set minimum of a[i] and v to a[i] from [l, r].
*
* @param tree The target tree
* @param l Left border of segment
* @param r Right border of segment
* @param v Value to compare and assign with
*/
void set_min(segment_tree* tree, int l, int r, int v) {
    return set_min_recursive_(tree, 1, 0, tree->n - 1, l, r, v);
}
