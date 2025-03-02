#include <stdio.h>

int main()
{
    for (int c = 0; c != EOF; c = getchar()) {
        printf("%c", c);
    }

	return 0;
}
