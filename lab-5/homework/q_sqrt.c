#include <stdio.h>

typedef union {
    float f;
    long i;
} float_long_union;

float Q_rsqrt( float number )
{
    float_long_union u;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    u.f = y;
    u.i = 0x5f3759df - ( u.i >> 1 );
    y = u.f;
    y = y * ( threehalfs - ( x2 * y * y ) );

    return y;
}

int main() {
    float number;
    
    printf("Podaj liczbe dodatnia: ");
    scanf("%f", &number);
    
    float result = Q_rsqrt(number);
    printf("Odwrotnosc pierwiastka: %f\n", result);
    printf("Pierwiastek: %f\n", 1.0f / result);
    
    return 0;
}
