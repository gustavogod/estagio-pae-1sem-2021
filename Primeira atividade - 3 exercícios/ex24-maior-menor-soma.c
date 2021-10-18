#include <stdio.h>

int main(void) {
  int n, maior;
  scanf("%d", &n);
  scanf("%d", &maior);

  int menor = maior;
  int soma = maior;

  for (int i=0; i < n-1; i++){
    int num;
    scanf("%d", &num);
    if (num > maior){
      maior = num;
    }
    else if (num < menor){
      menor = num;
    }

    soma += num;
  }

  printf("%d\n", maior);
  printf("%d\n", menor);
  printf("%d\n", soma);
  return 0;
}