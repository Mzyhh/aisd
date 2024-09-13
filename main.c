#include <stdio.h>
#include <limits.h>

struct node {
    struct node* prev;
    struct node* next;
    int value;
};

void printList(struct node* head);

int main(void) {
    setbuf(stdout, NULL);

    printf("Hello, World!\n");

    struct node zero_node = { NULL, NULL, INT_MIN};
    zero_node.next = zero_node.prev = &zero_node;

    struct node node_1 = { NULL, NULL, 1};
    struct node node_2 = { NULL, NULL, 2};
    struct node node_3 = { NULL, NULL, 3};

    zero_node.next = &node_1;
    zero_node.prev = &node_3;

    node_1.prev = &zero_node;
    node_1.next = &node_2;
    node_2.prev = &node_1;
    node_2.next = &node_3;
    node_3.prev = &node_2;
    node_3.next = &zero_node;

    printList(&zero_node);
}

void printList(struct node *head) {
    printf("[");

    struct node *current = head->next;
    while (current->value != INT_MIN) {
        printf("%d ", current->value);
        current = current->next;
    }

    printf("]");
}