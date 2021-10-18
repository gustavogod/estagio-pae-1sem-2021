#ifndef __TABULEIRO_H__
#define __TABULEIRO_H__

/**
* Número de peças utilizadas no jogo
* Também equivale ao número de posições no tabuleiro
*/
#define numPecas 16
/**
* Os atributos das peças deve ter valor de 0 à 16
* Os atributos são verificados de acordo com o valor de cada um dos 4 bits 
* do valor binário do atributo
* 1º bit (da direita p esquerda): PREENCHIMENTO. 0 = sólida, 1 = oca
* 2º bit: FORMATO. 0 = circular, 1 = quadrada
* 3º bit: ALTURA. 0 = grande, 1 = pequena
* 4º bit: COR. 0 = branca, 1 = escura
*/
typedef struct {
    char idPeca;
    int atributos;
    int disponivel;
} peca;

typedef struct {
    char idPosicao;
    peca p;
} posicaoTabuleiro;

typedef struct {
    posicaoTabuleiro posicao[numPecas];
} tabuleiro;

#endif 