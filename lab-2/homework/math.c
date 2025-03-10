/* math.c */
#include "math.h"

int factorial(int n) {
    if (n < 0) {
        return -1; // Błąd dla liczb ujemnych
    }
    if (n == 0) {
        return 1; // 0! = 1
    }
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}
