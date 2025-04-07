#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

int* generate_test_values(int n, int* test_size) {
    *test_size = n / 2;
    int* test = (int*)malloc(*test_size * sizeof(int));
    for (int i = 0; i < *test_size; i++) {
        test[i] = rand() % (n + 1);
    }
    return test;
}

int main() {
    int n;
    printf("test with values from 0 to: ");
    scanf("%d", &n);

    srand(time(NULL));

    int test_size;
    int* test = generate_test_values(n, &test_size);

    const char* orders[] = {"increasing", "decreasing", "random"};
    int num_orders = 3;

    for (int order = 0; order < num_orders; order++) {
        bst* root = NULL;
        struct timespec start, end;

        printf("\nOrder: %s\n", orders[order]);

        clock_gettime(CLOCK_MONOTONIC, &start);
        if (order == 0) {
            for (int i = 0; i <= n; i++) {
                root = bst_insert(root, i);
            }
        } else if (order == 1) {
            for (int i = n; i >= 0; i--) {
                root = bst_insert(root, i);
            }
        } else {
            int* temp = (int*)malloc((n + 1) * sizeof(int));
            for (int i = 0; i <= n; i++) {
                temp[i] = i;
            }
            for (int i = n; i > 0; i--) {
                int j = rand() % (i + 1);
                int swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
            for (int i = 0; i <= n; i++) {
                root = bst_insert(root, temp[i]);
            }
            free(temp);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double insert_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
        printf("Insertion took: %.3f ms\n", insert_time);

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < test_size; i++) {
            bst_search(root, test[i]);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double search_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
        printf("Search took: %.3f ms\n", search_time);

        clock_gettime(CLOCK_MONOTONIC, &start);
        bst_free(root);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double dealloc_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
        printf("Deallocation took: %.3f ms\n", dealloc_time);
    }

    free(test);

    return 0;
}
