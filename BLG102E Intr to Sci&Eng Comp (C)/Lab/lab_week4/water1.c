#include <stdio.h>
#include <stdlib.h>
#define BOIL 100
#define FREEZE 0
#define BOIL_F 212
#define FREEZE_F 32

int main() {
    
    double value = 0.0;
    char symbol;
    
    printf("Enter temperature (end with F for Fahrenheit or C for Celsius): ");
    scanf("%lf %c" , &value , &symbol);
    
    if (symbol == 'F') {
        if (value < FREEZE_F) {
            printf("Water is Solid (Ice) at %.2lf degrees Fahrenheit\n" , value);
        }
        
        else if (value > BOIL_F) {
            printf("Water is Gas (Vapor) at %.2lf degrees Fahrenheit\n" , value);
        }
        
        else {
            printf("Water is Liquid at %.2lf degrees Fahrenheit\n" , value);
        }
    }
    
    else if (symbol == 'C') {
        if (value < FREEZE) {
            printf("Water is Solid (Ice) at %.2lf degrees Celsius\n" , value);
        }
        
        else if (value > BOIL) {
            printf("Water is Gas (Vapor) at %.2lf degrees Celsius\n" , value);
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
