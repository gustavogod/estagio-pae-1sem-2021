#include <stdio.h>

int main (void){
    int k;
    float a;

    scanf("%d", &k);
    scanf("%f", &a);

    float pi;
    float ni;
    float dividendo = 0.0;
    float somaPesos = 0.0;
    float x = 0.0;

    for (int i = 0; i < k; i++){
        scanf("%f", &pi);
        scanf("%f", &ni);

        dividendo += pi / (ni + a);
        somaPesos += pi;
    }

    x = dividendo / somaPesos;
    
    float n = 1 / x - a;

    printf("%.1f\n", n);
}