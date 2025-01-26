#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ITERATION 10000000

int main() {
    int selected_door, prize_door, strat_1 = 0, strat_2 = 0;   //strat_1 : do not change, strat_2 : do change
    double win_strat_1, win_strat_2;

    srand(time(NULL));

    for (int i = 1; i <= ITERATION; i++) {
        prize_door = rand() % 3 + 1;
        selected_door = rand() % 3 + 1;
        
        if (selected_door == prize_door) {
            strat_1++;
        }

        else if (selected_door != prize_door) {
            strat_2++;
        }
    }

    win_strat_1 = (double) strat_1 / (double) ITERATION;
    win_strat_2 = (double) strat_2 / (double) ITERATION;

    printf("win ratio for strategy 1: %.3lf\n", win_strat_1);
    printf("win ratio for strategy 2: %.3lf\n", win_strat_2);

    return EXIT_SUCCESS;
}
