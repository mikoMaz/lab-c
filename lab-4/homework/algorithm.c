/* algorithm.c */
#include "algorithm.h"

void swap_ints(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void swap(void *a, void *b, size_t size) {
    void *c = malloc(size);
    
    memcpy(c, a, size);
    memcpy(a, b, size);
    memcpy(b, c, size);

    free(c);
}

// int* da_index(int **array, int *size, int index) {
//     if (*array == NULL) {
//         *size = index + 1;
//         *array = (int*)calloc(*size, sizeof(int));
//     } else if (index >= *size) {
//         int new_size = index + 1;
//         int *new_array = (int*)realloc(*array, new_size * sizeof(int));
//         if (new_array == NULL) return NULL;
//         *array = new_array;
//         *size = new_size;
//     }

//     return &(*array)[index];
// }

// int* da_index(int **array, int *size, int index) {
//     if (*array == NULL && *size == 0) {
//         *array = (int*)calloc(index + 1, sizeof(int));
//         *size = index + 1;
//         return &(*array)[index];
//     }
    
//     if (index < *size) {
//         return &(*array)[index];
//     }
    
//     int new_size = index + 1;
//     int *temp = (int*)realloc(*array, new_size * sizeof(int));
    
//     for (int i = *size; i < new_size; i++) {
//         temp[i] = 0;
//     }
    
//     *array = temp;
//     *size = new_size;
    
//     return &(*array)[index];
// }

int* da_index(int **array, int *size, int index) {
    // Sprawdzamy poprawność argumentów
    if (array == NULL || size == NULL || index < 0) {
        return NULL;
    }

    // Przypadek 1: Pusta tablica
    if (*array == NULL && *size == 0) {
        *array = (int*)calloc(index + 1, sizeof(int));
        if (*array == NULL) {
            return NULL; // Błąd alokacji
        }
        *size = index + 1;
        return *array + index; // Dla index = 0 będzie to *array
    }

    // Przypadek 2: Dostęp do istniejącego elementu
    if (index < *size) {
        return *array + index;
    }

    // Przypadek 3: Powiększenie tablicy
    int new_size = index + 1;
    int *temp = (int*)realloc(*array, new_size * sizeof(int));
    if (temp == NULL) {
        return NULL; // Błąd realokacji
    }

    // Inicjalizacja nowych elementów na 0
    for (int i = *size; i < new_size; i++) {
        temp[i] = 0;
    }

    *array = temp;
    *size = new_size;
    return *array + index;
}
