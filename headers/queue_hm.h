#ifndef QUEUE_HM_H
#define QUEUE_HM_H

typedef struct queue_hm {
    int v;
    // 6 stacks and so on
    // https://doi.org/10.1016/0020-0190(81)90030-2
} queue_hm;

const queue_hm *create_empty();

const queue_hm *enqueue(const queue_hm *queue, int value);

const queue_hm *dequeue(const queue_hm *queue);

int peek(const queue_hm *queue);

#endif //QUEUE_HM_H
