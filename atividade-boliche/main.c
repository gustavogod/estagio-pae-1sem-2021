#include <stdio.h>

#define FRAMES 10 

int jogar(int jogadas[], int bolasJogadas){
  for (int frame = 0; frame < FRAMES; frame++){
    int strike = 0;
    int spare = 0;
    int pontosPorFrame;
    int derrubou;

    scanf("%d", &derrubou);
    jogadas[bolasJogadas] = derrubou;
    bolasJogadas++;

    if (derrubou == 10){
      strike = 1;
    }
    else {
      pontosPorFrame = derrubou;
      scanf("%d", &derrubou);
      pontosPorFrame += derrubou;
      jogadas[bolasJogadas] = derrubou;
      bolasJogadas++;
      if (pontosPorFrame == 10){
        spare = 1;
      }
    }

    if (frame == 9 && strike == 1){
      scanf("%d", &derrubou);
      jogadas[bolasJogadas] = derrubou;
      bolasJogadas++;
      scanf("%d", &derrubou);
      jogadas[bolasJogadas] = derrubou;
      bolasJogadas++;      
    }
    if (frame == 9 && spare == 1){
      scanf("%d", &derrubou);
      jogadas[bolasJogadas] = derrubou;
      bolasJogadas++;       
    }
  }
  return bolasJogadas;
}

void imprimirJogadas(int jogadas[], int tam){
  int j = 0;
  //printf("\n");
  for (int i = 0; i < FRAMES - 1; i++) {
    if (jogadas[j] == 10){
      printf("X _ | ");
      j++;
    }
    else {
      printf("%d ", jogadas[j]);
      j++;
      if ((jogadas[j-1] + jogadas[j]) == 10){
        printf("/ | ");
      }
      else {
        printf("%d | ", jogadas[j]);
      }
      j++;
    }
  }

  // Tratar do último frame
  while (j < tam){
    if (jogadas[j] == 10){
      printf("X ");
      j++;
    }
    else {
      printf("%d ", jogadas[j]);
      j++;
      if ((jogadas[j-1] + jogadas[j]) == 10){
        printf("/ ");
      }
      else if (j < tam) {
        printf("%d ", jogadas[j]);
      }
      j++;
    }    
  }
  printf("\n");
}

void calcularPontosPorFrame(int jogadas[], int tam, int pontosPorFrame[]){
  int j = 0;
  for (int i = 0; i < FRAMES; i++){
    if (jogadas[j] == 10){
      pontosPorFrame[i] = jogadas[j] + jogadas[j+1] + jogadas[j+2];
      j++;
    }
    else {
      if ((jogadas[j] + jogadas[j+1]) == 10){
        pontosPorFrame[i] = jogadas[j] + jogadas[j+1] + jogadas[j+2];
      }
      else {
        pontosPorFrame[i] = jogadas[j] + jogadas[j+1];
      }
      j += 2;
    }
  }
}

int calcularPontos(int jogadas[], int tam){
  int pontosPorFrame[FRAMES];

  calcularPontosPorFrame(jogadas, tam, pontosPorFrame);

  int totalPontos = 0;
  for(int i = 0; i < FRAMES; i++){
    totalPontos += pontosPorFrame[i];
  }
  return totalPontos;
}

int main(void) {
  int pontoPorJogada[100];
  int bolasJogadas = 0;

  bolasJogadas = jogar(pontoPorJogada, bolasJogadas);

  imprimirJogadas(pontoPorJogada, bolasJogadas);
  
  int pontosTotal = calcularPontos(pontoPorJogada, bolasJogadas);

  printf("%d", pontosTotal);
  return 0;
}