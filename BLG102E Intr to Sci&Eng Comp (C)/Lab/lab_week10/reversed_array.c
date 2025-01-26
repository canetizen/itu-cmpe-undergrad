#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void swap(int *first, int *second) {
    int temp = *second;
    *second = *first;
    *first = temp;
}

void random_fill_array(int *arr) {
    int random_num;
    int selected[ARRAY_SIZE] = {0};
    for (int i = 0; i < ARRAY_SIZE; i++){
    do{
      random_num = rand() % ARRAY_SIZE;
     } while (selected[random_num] == 1);
    selected[random_num] = 1;
    arr[i] = random_num;
    }
}

int main() {
    int my_array[ARRAY_SIZE];
    srand(0); // to be suitable for test file.
    random_fill_array(my_array);
    printf("ORIGINAL ARRAY: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%-5d", my_array[i]);
    }
    printf("\n");
    for (int i = 0; i < ARRAY_SIZE / 2; i++) {
        swap(&my_array[i], &my_array[ARRAY_SIZE - 1 - i]);
    }
    printf("REVERSE ARRAY: ");
    printf(" ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%-5d", my_array[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
