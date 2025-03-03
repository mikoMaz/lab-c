#include <stdio.h>

int main()
{
	int c = getchar();
	
	if (c == '0') {
        printf("0\n");
		return 0;
	}

	for (;;) {
		printf("1\n");
	}
}
