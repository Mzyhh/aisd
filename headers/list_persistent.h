#ifndef LIST_PERSISTENT_H
#define LIST_PERSISTENT_H

struct node;

typedef struct {
    int version;
    enum {Data, Pointer} field;
    union {int data; struct node* next;};
} update;

typedef struct node {
    // node origin version, pointer to next node, value, rev pointer, changelog

    int data;
    struct node* next;

    update changelog;
    struct node* rev;
} node;

typedef struct list_persistent {
    // last version, access pointers array and so on
    // https://doi.org/10.1016/0022-0000(89)90034-2

    node* head;
    int version;
} list_persistent;


list_persistent create_empty();

void insert_at(list_persistent* list, int index, int value);

void set(list_persistent* list, int version, int index, int value);

// void delete(list_persistent* list, int index);

int get(const list_persistent* list, int version, int index);

void iterate(const list_persistent* list, int version, void (*callback)(int));

#endif //LIST_PERSISTENT_H
