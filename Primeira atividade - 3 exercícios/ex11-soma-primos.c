#include <stdio.h>

int main(void) {
  int n;
  scanf("%d", &n);
  
  int soma = 0;

  for (int i = 2; i < n+1; i++){
    int ehPrimo = 1;
    int aux = 2;
	
	if (i > 2 && i%2 == 0) 
		ehPrimo = 0;
    while (aux <= i/2 && ehPrimo != 0){
      if (i % aux == 0)
        ehPrimo = 0;
      aux++;
    }

    if (ehPrimo)
      soma += i;
  }

  printf("%d\n", soma);
  return 0;
}