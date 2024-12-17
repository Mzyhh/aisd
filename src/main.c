#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tree_23.h"


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
    for (int i = 0; i < n; ++i)
        if (find(root, number[i]) == NULL) printf("%d ", number[i]);
    print(root, res);
    printf("\n%s\n\n", res);
    // print_all_nodes(root);
    return 0;
}
