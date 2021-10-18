#include <stdio.h>

int main(void) {
  int n, c, m;
  scanf("%d", &n);
  scanf("%d", &c);
  scanf("%d", &m);

  int total = n / c;
  int emb = total;

  while(emb >= m){
    int chocExtra = emb / m;
    int sobra = emb % m;
    emb = chocExtra + sobra;
    total += chocExtra;
  }

  printf("%d\n", total);
  return 0;
}