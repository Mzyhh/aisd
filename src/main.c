#include <stdio.h>
#include "list_persistent.h"

void print_node(int value) {
    fprintf(stderr, "%d ", value);
}

int main(void) {
    list_persistent list = create_empty();
    insert_at(&list, 0, 1);
    insert_at(&list, 1, 2);
    insert_at(&list, 2, 3);
    insert_at(&list, 0, 4);
    insert_at(&list, 0, 5);
    insert_at(&list, 5, 6);
    set(&list, 4, 100);
    set(&list, 4, 200);
    set(&list, 4, 300);
    for (int i = 0; i <= list.last_version; ++i) {
        fprintf(stderr, "version %d: ", i);
        iterate(&list, i, print_node);
        fprintf(stderr, "\n");
    }
    return 0;
}
