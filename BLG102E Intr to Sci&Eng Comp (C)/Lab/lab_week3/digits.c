#include <stdio.h>

int main() {
    int right = 0;
    int middle = 0;
    int left = 0;
    int number = 0;

    printf("Enter a 3 digit number:");
    scanf("%d" , &number);

    right = number % 10;
    middle = (number / 10) % 10;
    left = (number / 100) % 10;

    printf("Digits of number %d are %d, %d, %d respectively\n" , number , left , middle , right);
    
    return 0;
}

    
