#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main() {
    int sequence[SIZE], sequence_init[SIZE];
    
    printf("Enter 10 numbers: ");
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &sequence[i]);
        sequence_init[i] = sequence[i];
    }
    
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (sequence[j + 1] < sequence[j]) {
                int temp = 0;
                temp = sequence[j + 1];
                sequence[j + 1] = sequence[j];
                sequence[j] = temp;
            }
        }
    }
    
    printf("Original Array:");
    for (int i = 0; i < SIZE; i++) {
        printf(" %d", sequence_init[i]);
    }
    
    printf("\n");
    
    printf("Sorted Array(Ascending):");
    for (int i = 0; i < SIZE; i++) {
        printf(" %d", sequence[i]);
    }
    
    printf("\n");
    
    printf("Sorted Array(Descending):");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf(" %d", sequence[i]);
    }
    
    printf("\n");
        
    return EXIT_SUCCESS;
}
