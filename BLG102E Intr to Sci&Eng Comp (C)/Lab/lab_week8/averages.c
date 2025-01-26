#include <stdio.h>

#define SIZE 10
#define WINDOW 3

int main() {
    double sequence[SIZE], cum_avg[SIZE], sm_avg[SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        printf("Enter a number: ");
        scanf("%lf", &sequence[i]);
    }
    
    for (int i = 0; i < SIZE; i++) {
        double total;
                
        total += sequence[i];
        cum_avg[i] = total / (i + 1);
    }

    for (int i = 2; i < SIZE; i++) {
        double total = 0;

        for (int j = i; j > i - WINDOW; j--) {

            total += sequence[j];
        }
        
        sm_avg[i] = total / WINDOW;
    }
    
    printf(" Current  |  Cum. Avg. | S. M. Avg.\n");
    printf("----------|------------|-----------\n");
    
    for (int i = 0; i < SIZE; i++) {
        printf("%8.3lf  | %8.3lf   | %8.3lf\n", sequence[i], cum_avg[i], sm_avg[i]);
    }
    
    return 0;
}
