#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, a, b, seed;
    printf("n, a, b, seed: ");
    scanf("%d %d %d %d", &n, &a, &b, &seed);

    int *nums = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        srand(seed);
        nums[i] = rand() % (b - a) + a;
    }
    free(nums);
    nums = NULL;

    for (int i = 0; i < n; i++) {
        printf("%d", nums[i]);
        if (i > 0) {
            printf(" ");
        }
        printf("\n");
    }

    return 0;
}
