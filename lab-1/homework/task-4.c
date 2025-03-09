#include <stdio.h>

int main()
{
    for (int c = 0; (c = getchar()) != EOF;)  {
        printf("%c", c);
    }

	return 0;
}
