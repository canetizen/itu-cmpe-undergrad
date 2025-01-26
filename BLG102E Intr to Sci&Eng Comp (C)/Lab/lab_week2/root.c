#include <stdio.h>
#include <math.h>

int main() {
    double a = 0.0, b = 0.0, c = 0.0;
    printf("Enter the coefficients: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    double dis = (b * b) - (4.0 * a * c);
    printf("Discriminant of this equation: %.1lf\n", dis);

    double root1 = ((-b) + sqrt(dis)) / (2 * a);
    printf("First root of this equation: %.1lf\n", root1);

    double root2 = ((-b) - sqrt(dis)) / (2 * a);
    printf("Second root of this equation: %.1lf\n", root2);

    return 0;

}
