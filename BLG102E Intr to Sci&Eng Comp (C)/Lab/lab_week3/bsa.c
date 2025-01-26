#include <stdio.h>
#include <math.h>

int main() {
    double height = 0.0;
    double weight = 0.0;
    double bsa = 0.0;
    
    printf("Input height(cm) and weight(g):");
    scanf("%lf %lf" , &height , &weight);
    
    bsa = 0.0003207 * pow(height , 0.3) * pow(weight , (0.7285 - (0.0188 * log10(weight))));
    
    printf("BSA: %.2lf\n" , bsa);
    
    return 0;
}
