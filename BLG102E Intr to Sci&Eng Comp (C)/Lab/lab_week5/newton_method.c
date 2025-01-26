
/* This program finds only greater root of given equation */ 

#include <stdio.h>
#include <stdlib.h>

double y_calc(double a, double b, double c, double x) {
    double calculated = a * x * x + b * x + c;
    return calculated;
}  

int main() {
    double a, b, c, e = 0.001, y, y1, y2, m, x, y_final, initial_guess = 10.0;

    scanf("%lf %lf %lf", &a, &b, &c);

    for (x = initial_guess; x ; x = x - e) {
        y1 = y_calc(a, b, c, (x - e));
        y2 = y_calc(a, b, c, (x + e));

        m = (y2 - y1) / (2 * e);

        y = y_calc(a, b, c, x);

        x = x - (y / m);

        y_final = y_calc(a, b, c, x);

        if (y_final < e && y > -e) {
            printf("Root: %.2lf\n", x);
            break;
        }
    }
    return EXIT_SUCCESS;
}
