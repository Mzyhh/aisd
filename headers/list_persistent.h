#ifndef LIST_PERSISTENT_H
#define LIST_PERSISTENT_H

typedef struct list_persistent {
    // last version, access pointers array and so on
    // https://doi.org/10.1016/0022-0000(89)90034-2
} list_persistent;

typedef struct node {
    // node origin version, pointer to next node, value, rev pointer, changelog
} node;

list_persistent create_empty();

void insert_at(list_persistent* list, int index, int value);

void set(list_persistent* list, int version, int index, int value);

// void delete(list_persistent* list, int index);

int get(const list_persistent* list, int version, int index);

void iterate(const list_persistent* list, int version, void (*callback)(int));

#endif //LIST_PERSISTENT_H
