#include <stdio.h>

int main () {
    double f;
    printf("Write a temperature value in Fahrenheit: ");
    scanf("%lf", &f);

    double c = (5.0 / 9.0) * (f - 32.0);
    printf("Temperature in Celsius: %.1lf\n", c);
    
    return 0;
}
