#include "list_persistent.h"
#include <stdlib.h>

list_persistent create_empty() {
    list_persistent result = {.head = NULL, .version = 0};
    return result;
}

node* get_node(list_persistent* list, int index) {
    node *p = list->head;
    for (int i = 0; i < index && p; i++) {
        if (WAS_CHANGED(p) && p->changelog.field == Pointer) {
            p = p->changelog.new_value.next;
        } else {
            p = p->next;
        }
    }
    return p;
}

node* new_node(int value, node *next, node *rev) {
    node *nnode = (node*)malloc(sizeof(node));
    nnode->data = value;
    nnode->changelog.version = -1;
    nnode->next = next;
    nnode->rev = rev;
    return nnode;
}

node *copy_node(node *old) {
    node *cnode = new_node(old->data, old->next, old->rev);
    if (WAS_CHANGED(old)) {
        if (old->changelog.field == Data) {
            cnode->data = old->changelog.new_value.data;
        } else {
            cnode->next = old->changelog.new_value.next;
        }
    }
    return cnode;
}

node *node_copying(node *old, int version) {
    node *cnode = copy_node(old);
    if (!old->rev) return cnode;
    if (WAS_CHANGED(old->rev)) {
        cnode->rev = node_copying(old->rev, version);
        cnode->rev->next = cnode;
    } else {
        update upd = {.field = Pointer, .version = version, .new_value.next = cnode}; 
        old->rev->changelog = upd;
    }
    return cnode;
}

// TODO: modify in case of changing list's head
void insert_at(list_persistent* list, int index, int value) {
    list->version++;
    node *next = get_node(list, index);
    node *prev = next->rev;
    node *nnode = new_node(value, next, prev);
    next->rev = nnode;

    if (WAS_CHANGED(prev)) {
        node *cnode = node_copying(prev, list->version);
        nnode->rev = cnode;
    } else {
        update upd = {.field = Pointer, .version = list->version, .new_value.next = nnode};
        prev->changelog = upd;
    }
}

int get(const list_persistent* list, int version, int index) {
    node *p = list->head;
    for (int i = 0; i < index; ++i) {
        if (WAS_CHANGED(p) && p->changelog.field == Pointer && p->changelog.version <= version) {
            p = p->changelog.new_value.next;
        } else {
            p = p->next;
        }
    }
    return (WAS_CHANGED(p) && p->changelog.field == Data)? p->changelog.new_value.data : p->data;
}


void set(list_persistent* list, int index, int value) {
    list->version++;
    node *target = get_node(list, index);
    if (WAS_CHANGED(target)) {
        node *cnode = node_copying(target, list->version);
        cnode->data = value;
        if (target->next) target->next->rev = cnode;

    } else {
        update upd = {.field = Data, .version = list->version, .new_value.data = value};
        target->changelog = upd;
    }
}


void iterate(const list_persistent* list, int version, void (*callback)(int)) {
    node *p = list->head;
    while (p) {
        callback((WAS_CHANGED(p) && p->changelog.field == Data)? p->changelog.new_value.data : p->data);
        if (WAS_CHANGED(p) && p->changelog.field == Pointer && p->changelog.version <= version) {
            p = p->changelog.new_value.next;
        } else {
            p = p->next;
        }
    }
}
