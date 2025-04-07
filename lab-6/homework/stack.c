#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListStack {
    Node* top;
} ListStack;

ListStack* list_stack_create() {
    ListStack* stack = (ListStack*)malloc(sizeof(ListStack));
    stack->top = NULL;
    return stack;
}

void list_stack_push(ListStack* stack, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = stack->top;
    stack->top = new_node;
}

int list_stack_pop(ListStack* stack) {
    if (stack->top == NULL) {
        printf("List stack is empty!\n");
        exit(1);
    }
    Node* temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    return value;
}

int list_stack_is_empty(ListStack* stack) {
    return stack->top == NULL;
}

void list_stack_free(ListStack* stack) {
    while (!list_stack_is_empty(stack)) {
        list_stack_pop(stack);
    }
    free(stack);
}

typedef struct ArrayStack {
    int* array;
    int top;
    int capacity;
} ArrayStack;

ArrayStack* array_stack_create(int initial_capacity) {
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    stack->array = (int*)malloc(initial_capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = initial_capacity;
    return stack;
}

void array_stack_push(ArrayStack* stack, int value) {
    if (stack->top + 1 == stack->capacity) {
        stack->capacity *= 2;
        stack->array = (int*)realloc(stack->array, stack->capacity * sizeof(int));
    }
    stack->top++;
    stack->array[stack->top] = value;
}

int array_stack_pop(ArrayStack* stack) {
    if (stack->top == -1) {
        printf("Array stack is empty!\n");
        exit(1);
    }
    int value = stack->array[stack->top];
    stack->top--;
    return value;
}

int array_stack_is_empty(ArrayStack* stack) {
    return stack->top == -1;
}

void array_stack_free(ArrayStack* stack) {
    free(stack->array);
    free(stack);
}

int main() {
    int n;
    printf("Enter number of elements to test: ");
    scanf("%d", &n);

    srand(time(NULL));

    printf("\n=== List Stack Performance ===\n");
    ListStack* ls = list_stack_create();
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        list_stack_push(ls, rand());
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double push_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Push %d elements: %.3f ms\n", n, push_time);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        list_stack_pop(ls);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double pop_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Pop %d elements: %.3f ms\n", n, pop_time);

    list_stack_free(ls);

    printf("\n=== Array Stack Performance ===\n");
    ArrayStack* as = array_stack_create(10);
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        array_stack_push(as, rand());
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    push_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Push %d elements: %.3f ms\n", n, push_time);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        array_stack_pop(as);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    pop_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Pop %d elements: %.3f ms\n", n, pop_time);

    array_stack_free(as);

    return 0;
}
