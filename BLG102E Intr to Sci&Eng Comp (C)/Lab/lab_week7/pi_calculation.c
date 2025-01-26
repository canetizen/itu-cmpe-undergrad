#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ITERATION 10000

double getRandomNumber(double lower_limit, double upper_limit) {
    double range, div, random_value;
    
    range = (upper_limit - lower_limit); 
    div = RAND_MAX / range;
    random_value = lower_limit + (rand() / div);
    
    return random_value;
}

double calculatePi(int max_iteration) {
    double counter1, counter2, x, y, lower = -1.0, higher = 1.0, pi;
    
    for (int i = 1; i < max_iteration; i++) {
        
        x = getRandomNumber(lower, higher);
        y = getRandomNumber(lower, higher);
    
        if (x * x + y * y <= 1) {
            counter1++;
            counter2++; 
        }
        
        else {
            counter2++;
        }
    }
    
    pi = 4.0 * (counter1 / counter2);
    
    return pi;    
}

int main() {
    double pi_value;

    srand(time(NULL));
    
    pi_value = calculatePi(ITERATION);
    
    printf("Mean Value of 100 Estimated Pi's = %.1lf..", pi_value);
    
    return EXIT_SUCCESS;
}
