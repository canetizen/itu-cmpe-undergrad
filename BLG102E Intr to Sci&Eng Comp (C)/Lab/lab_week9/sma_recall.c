#include <stdlib.h>
#include <stdio.h>

#define SIZE 30
#define MA_SIZE 5

void calculateCumulativeAverage(double exchange_rate[], double cumulative_average[]) {
    for (int i = 0; i < SIZE; i++) {
        double total;
        total += exchange_rate[i];
        cumulative_average[i] = total / (i + 1);
    }
}

void calculateMovingAverage(double exchange_rate[], double moving_average[]) {
    for (int i = MA_SIZE - 1; i < SIZE; i++) {
        double total = 0;
        for (int j = i; j > i - MA_SIZE; j--) {
            total += exchange_rate[j];
        }
        moving_average[i] = total / MA_SIZE;
    }
}

void printAverages(double exchange_rate[], double cumulative_average[], double moving_average[]) {
    printf(" Current  |  Cum. Avg. | S. M. Avg.\n");
    printf("----------|------------|-----------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%8.3lf  | %8.3lf   | %8.3lf\n", exchange_rate[i], cumulative_average[i], moving_average[i]);
    }
}

int main() {
    double exchange_rate[SIZE] = { 3.74, 3.75, 3.80, 3.78, 3.78, 3.78, 3.79, 3.78, 3.78, 3.80, 
                                   3.79, 3.80, 3.80, 3.80, 3.80, 3.80, 3.79, 3.79, 3.82, 3.81, 
                                   3.82, 3.81, 3.84, 3.86, 3.87, 3.89, 3.91, 3.91, 3.91, 3.93 };
    double cumulative_average[SIZE];
    double moving_average[SIZE];
    
    calculateCumulativeAverage(exchange_rate, cumulative_average);
    calculateMovingAverage(exchange_rate, moving_average);
    printAverages(exchange_rate, cumulative_average, moving_average);
    
    return EXIT_SUCCESS;
}
