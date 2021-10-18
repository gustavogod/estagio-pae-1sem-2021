#include <stdio.h>

#include "jogo.h"
#include "tabuleiro.h"

// branca, escura
// grande, pequena
// circular, quadrada
// solida, oca

// caracteristicas verificadas: linha, coluna diagonal

// vencedor: 1 ou 2. ninguém ganhou, saída 0

int main(int argc, int *argv[]){
    tabuleiro tab;
    peca pecas[numPecas];
    inicializarPecas(pecas);
    inicializarTabuleiro(&tab);
    iniciarPartida(&tab, pecas);
}