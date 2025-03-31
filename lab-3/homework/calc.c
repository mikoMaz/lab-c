#include <stdio.h>
#include <math.h>

int main()
{
    for (;;) {
	    printf("Dodawanie [+]\nMnozenie [*]\nPotegowanie [^]\nLocarytm [l]\n");
        int choice = getchar();

        double a, b, result;

        switch (choice) {
            case '+':
                printf("Podaj dwie liczby: ");
                scanf("%lf %lf", &a, &b);
                result = a + b;
                printf("Wynik dodawania: %.2f\n\n", result);
                break;
            case '*':
                printf("Podaj dwie liczby: ");
                scanf("%lf %lf", &a, &b);
                result = a * b;
                printf("Wynik mnożenia: %.2f\n\n", result);
                break;
            case '^':
                printf("Podaj podstawę i wykładnik: ");
                scanf("%lf %lf", &a, &b);
                result = pow(a, b);
                printf("Wynik potęgowania: %.2f\n\n", result);
                break;
            case 'l':
                printf("Podaj liczby: ");
                scanf("%lf %lf", &a, &b);
                if (a > 0 && b > 0 && b != 1) {
                result = log(a) / log(b);
                printf("Wynik logarytmu: %.2f\n\n", result);
                } else {
                    printf("Error!\n");
                    return 1;
                }
                break;
            default:
                continue;
        }
    }
    return 0;
}
