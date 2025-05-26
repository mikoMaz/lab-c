#ifndef SHARED_QUEUE_H
#define SHARED_QUEUE_H

#include <stddef.h>

struct queue {
    int* buffer;
    size_t size;
    size_t head;
    size_t tail;
};

struct queue* queue_init(size_t size);
void queue_destroy(struct queue* queue);
int enqueue(struct queue* queue, int item);
int dequeue(struct queue* queue);
int full(struct queue queue);
int empty(struct queue queue);

#endif
