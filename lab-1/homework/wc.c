#include <stdio.h>

int main()
{
	int c;
	int lineCounter = 1;
	int characterCounter = 0;

	while ((c = getchar()) != EOF) {
		
		characterCounter++;
		
		if (c == '\n')
			lineCounter++;
	}

	printf("\nNumber of lines: %d\n", lineCounter);
    printf("Number of characters: %d\n", characterCounter);
	return 0;
}
