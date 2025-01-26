#include <stdio.h>
#include <stdlib.h>

#define BOIL 100
#define FREEZE 0

int main() {
    double value = 0.0;
    char symbol;
    int meter = 0;
    double celsius = 0.0;
    double boiling_drop = 0.0;
    
    printf("Enter temperature (end with F for Fahrenheit or C for Celsius): ");
    scanf("%lf %c" , &value , &symbol);
    
    printf("Enter altitude in meters: ");
    scanf("%d" , &meter);

    boiling_drop = BOIL - (meter / 300);
    
    if (symbol == 'F') {
        celsius = ((5 / 9) * (int)(value - 32));

        if (celsius >= boiling_drop) {
            printf("Water is Gas (Vapor) at %.2lf degrees Fahrenheit\n" , value);
        }

        else if (celsius >= FREEZE) {
            printf("Water is Solid (Ice) at %.2lf degrees Fahrenheit\n" , value);
        }

        else {
            printf("Water is Liquid at %.2lf degrees Fahrenheit\n" , value);
        }
    }

    else if (symbol == 'C') {
        if (value >= boiling_drop) {
            printf("Water is Gas (Vapor) at %.2lf degrees Celsius\n" , value);
            }

        else if (value <= FREEZE) {
            printf("Water is Solid (Ice) at %.2lf degrees Celsius\n" , value);
            }

        else {
            printf("Water is Liquid at %.2lf degrees Celsius\n" , value);
            }
    }

    else {
        printf("Please enter temperature unit as either C or F.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
