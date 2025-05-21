#include "segment_tree.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

static int closest_bigger_2pow(int n) {
    if ((n & (n - 1)) == 0)
        return n;
    return 1 << (int)(ceil(log2(n)));
}

int is_left_child(int i) {
    return i % 2 == 0;
}

int is_right_child(int i) {
    return i % 2 == 1;
}

/**
* Build segment tree from array `numbers` of length `n`
*
* @param numbers Target array
* @param n Size of array `numbers`
*/
segment_tree build_segment_tree(const int* numbers, const int n) {
    segment_tree result;
    result.n = closest_bigger_2pow(n); 
    result.array = malloc(result.n * 2 * sizeof(int));
    for (int i = 0; i < 2 * result.n; ++i)
        result.array[i] = INT_MIN;
    memcpy(result.array + result.n, numbers, n * sizeof(int));
    for (int i = result.n - 1; i > 0; --i)
        result.array[i] = MAX(result.array[2 * i], result.array[2 * i + 1]);
    return result;
}

/**
 * Return maximum value on segment [l, r].
 *
 * @param tree Segment tree containing target array
 * @param l Left border of segment (array indexing)
 * @param r Right border of segment (array indexing)
 */
int get_max(segment_tree* tree, int l, int r) {
    int result = INT_MIN;
    for (l += tree->n, r += tree->n; l <= r; l >>= 1, r >>= 1) {
        if (is_right_child(l)) {
            result = MAX(result, tree->array[l]);
            l++;
        }
        if (is_left_child(r)) {
            result = MAX(result, tree->array[r]);
            r--;
        }
    }
    return result;
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
    // setting value to leafs
    l += tree->n;
    r += tree->n;
    for (int i = l; i <= r; ++i)
        tree->array[i] = MIN(tree->array[i], v);

    // resetting ancestors
    for (r /= 2, l /= 2; l > 0; l /= 2, r /= 2) {
        for (int j = l; j <= r; ++j) 
            tree->array[j] = MAX(tree->array[2 * j], tree->array[2 * j + 1]);
    }
}
