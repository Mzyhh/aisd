#include "list_persistent.h"
#include <stdlib.h>

static void update_heads(list_persistent *list) {
    if (list->last_version >= list->heads_capacity) {
        list->heads_capacity <<= 1;
        list->heads= (node**)realloc(list->heads, sizeof(node*)*list->heads_capacity);
    }
    list->heads[list->last_version] = list->heads[list->last_version-1];
    return;
}

list_persistent create_empty() {
    list_persistent result;
    result.heads_capacity = DEFAULT_HEADS_CAPACITY;
    result.heads = (node**)malloc(sizeof(node*)*result.heads_capacity);
    result.heads[0] = NULL;
    result.last_version = 0;
    return result;
}

node* get_node(list_persistent* list, int index) {
    node *p = list->heads[list->last_version];
    for (int i = 0; i < index && p; i++) {
        if (WAS_CHANGED(p) && p->changelog.field == POINTER) {
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
        if (old->changelog.field == DATA) {
            cnode->data = old->changelog.new_value.data;
        } else {
            cnode->next = old->changelog.new_value.next;
        }
    }
    return cnode;
}

node *node_copying(list_persistent *list, node *old) {
    node *cnode = copy_node(old);
    if (!old->rev) {
        list->heads[list->last_version] = cnode;
        return cnode;
    }
    if (WAS_CHANGED(old->rev)) {
        cnode->rev = node_copying(list, old->rev);
        cnode->rev->next = cnode;
    } else {
        update upd = {.field = POINTER, .version = list->last_version, .new_value.next = cnode}; 
        old->rev->changelog = upd;
    }
    return cnode;
}

void insert_at(list_persistent* list, int index, int value) {
    node *next = NULL, *rev = NULL;
    list->last_version++;
    update_heads(list);
    if (index == 0) { 
        next = list->heads[list->last_version-1];
        list->heads[list->last_version] = new_node(value, next, rev);
        if (next) 
            next->rev = list->heads[list->last_version]; 
        return;
    }
    rev = get_node(list, index-1);
    next = rev->next;
    node *nnode = new_node(value, next, rev);
    if (next)
        next->rev = nnode;
    if (WAS_CHANGED(rev)) {
        node *cnode = node_copying(list, rev);
        nnode->rev = cnode;
    } else {
        update upd = {.field = POINTER, .version = list->last_version, 
                      .new_value.next = nnode};
        rev->changelog = upd;
    }
}

int get(const list_persistent* list, int version, int index) {
    node *p = list->heads[version];
    for (int i = 0; i < index; ++i) {
        if (WAS_CHANGED(p) && p->changelog.field == POINTER && p->changelog.version <= version) {
            p = p->changelog.new_value.next;
        } else {
            p = p->next;
        }
    }
    return (WAS_CHANGED(p) && p->changelog.field == DATA)? p->changelog.new_value.data : p->data;
}


void set(list_persistent* list, int index, int value) {
    list->last_version++;
    update_heads(list);
    node *target = get_node(list, index);
    if (WAS_CHANGED(target)) {
        node *cnode = node_copying(list, target);
        cnode->data = value;
        if (target->next) target->next->rev = cnode;

    } else {
        update upd = {.field = DATA, .version = list->last_version, .new_value.data = value};
        target->changelog = upd;
    }
}


void iterate(const list_persistent* list, int version, void (*callback)(int)) {
    node *p = list->heads[version];
    while (p) {
        callback((WAS_CHANGED(p) && p->changelog.field == DATA)? p->changelog.new_value.data : p->data);
        if (WAS_CHANGED(p) && p->changelog.field == POINTER && p->changelog.version <= version) {
            p = p->changelog.new_value.next;
        } else {
            p = p->next;
        }
    }
}
