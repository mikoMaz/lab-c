#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "shared_queue.h"

struct queue* queue_init(size_t size) {
    int shm_fd = shm_open("/my_queue", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(struct queue) + size * sizeof(int));
    struct queue* queue = mmap(NULL, sizeof(struct queue) + size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    queue->size = size;
    queue->head = 0;
    queue->tail = 0;
    queue->buffer = (int*)((char*)queue + sizeof(struct queue));
    return queue;
}

void queue_destroy(struct queue* queue) {
    munmap(queue, sizeof(struct queue) + queue->size * sizeof(int));
    shm_unlink("/my_queue");
}

int enqueue(struct queue* queue, int item) {
    queue->buffer[queue->head] = item;
    queue->head = (queue->head + 1) % queue->size;
    return 0;
}

int dequeue(struct queue* queue) {
    int item = queue->buffer[queue->tail];
    queue->tail = (queue->tail + 1) % queue->size;
    return item;
}

int full(struct queue queue) {
    return ((queue.head + 1) % queue.size) == queue.tail;
}

int empty(struct queue queue) {
    return queue.head == queue.tail;
}
