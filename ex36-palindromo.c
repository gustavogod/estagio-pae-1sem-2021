#include <stdio.h>

int inverterNumero(int a){
    int nInverso = 0;

    nInverso = nInverso*10 + a%10;

    while (a / 10 > 0){
        a /= 10;
        nInverso = nInverso*10 + a%10;
    } 

    return nInverso;
}

int main(void){
    int n;
    scanf("%d", &n);

    int nInvertido = inverterNumero(n);
    
    if (n == nInvertido){
        printf("S\n");
    }
    else {
        printf("N\n");
    }

}