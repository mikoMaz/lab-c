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
                printf("Podaj liczbę: ");
                scanf("%lf", &a);
                if (a > 0) {
                    result = log(a);
                    printf("Logarytm naturalny z %.2f: %.2f\n\n", a, result);
                } else {
                    printf("Logarytm jest zdefiniowany tylko dla liczb dodatnich.\n\n");
                }
                break;
            default:
                continue;
        }
    }
}
