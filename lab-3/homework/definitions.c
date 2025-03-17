#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE (1024 * 1024)
#define N 10
#define M 20

int main()
{
    int integers[256] = {};
    uint8_t buffer[BUFFER_SIZE] = {};
    int multiplication[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            multiplication[i][j] = i * j;
        }
    }

    const short value = 12345;

    const short* constant = &value;
}
