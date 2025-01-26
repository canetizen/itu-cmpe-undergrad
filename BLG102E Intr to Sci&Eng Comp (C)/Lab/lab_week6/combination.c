#include <stdio.h>
#include <stdlib.h>

int combination(int n, int r) {
    
    int n_fact = 1, r_fact = 1, difference, comb;

    difference = n - r;

    if (difference == 0 || difference == n) {
        comb = 1;
        return comb;
    }

    else {
        for (int i = n; i > difference; i--) { // EX: C(9, 3) = 9*8*7 / 3! 
            n_fact *= i;
        }

        for (int i = 1; i <= r; i++) {
            r_fact *= i;
        }

        comb = n_fact / r_fact;

        return comb;
    }
}
    
int main() {
    
    int n, r, result;

    printf("Enter n and r: ");
    scanf("%d %d", &n, &r);

    result = combination(n, r);

    printf("%d\n" , result);

    return EXIT_SUCCESS;
}
