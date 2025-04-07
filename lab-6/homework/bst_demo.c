#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

double measure_time_ms(clock_t start, clock_t end) {
    return ((double)(end - start) * 1000) / CLOCKS_PER_SEC;
}

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
        clock_t start, end;

        printf("\nOrder: %s\n", orders[order]);

        start = clock();
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
        end = clock();
        printf("Insertion took: %.0f ms\n", measure_time_ms(start, end));

        start = clock();
        for (int i = 0; i < test_size; i++) {
            bst_search(root, test[i]);
        }
        end = clock();
        printf("Search took: %.0f ms\n", measure_time_ms(start, end));

        start = clock();
        bst_free(root);
        end = clock();
        printf("Deallocation took: %.0f ms\n", measure_time_ms(start, end));
    }

    free(test);

    return 0;
}
