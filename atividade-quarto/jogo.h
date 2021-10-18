#ifndef __JOGO_H__
#define __JOGO_H__

#include "tabuleiro.h"

// As palavras definidas a seguir representam o atributo definido pelo i-esimo bit
// do atributo das peças. Isto é, o valor definido corresponde ao i-esimo bit do valor binário do atributo da peça
#define PREENCHIMENTO 0
#define FORMATO 1
#define ALTURA 2
#define COR 3

// Define um valor para o atributo em comum entre as peças que definem que o jogo tem um vencedor
#define BRANCA 1
#define ESCURA 2
#define GRANDE 3
#define PEQUENA 4
#define CIRCULAR 5
#define QUADRADA 6
#define SOLIDA 7
#define OCA 8

int indexHexa(char );

void inicializarPecas(peca *);

void inicializarTabuleiro(tabuleiro *);

void imprimirTabuleiro(tabuleiro *);

void imprimirSequenciaVencedora(posicaoTabuleiro *);

void imprimirAtributoVencedor(int );

int proximaJogada(tabuleiro *, peca *);

/**
* Função para deslocar e isolar o i-esimo bit
* Com essa função, pode-se verificar o bit que representa algum atributo das peças
* Sempre retorna 1 ou 0.
*/
int isolaBit(int , int );

int somaBits(posicaoTabuleiro *, int );

/**
 * Recebe um vetor posicaoTabuleiro de 4 posições que corresponde a uma
 * linha, coluna ou diagonal do tabuleiro.
 * Por meio do vetor, verifica se já há algum vencedor.
 * Retorna o valor correspondente ao atributo vencedor (ex: oca, pequena, quadrada, etc).
 * Se NÃO houver vencedor, retorna 0.
 * Os valores dos atributos são definidos em jogo.h
 */
int verificaVencedor(posicaoTabuleiro *);

/* Formato das posições do tabuleiro
*   0    |   1   |   2    |   3
*   4    |   5   |   6    |   7
*   8    |   9   |   10(A)|  11(B)
*   12(C)|  13(D)|   14(E)|  15(F)
*/
/**
 * Verifica se já tem algum vencedor na partida
 * Se houver, Retorna o valor correspondente ao atributo vencedor (ex: oca, pequena, quadrada, etc). 
 * Se não, retorna 0
 */
int temVencedor(tabuleiro *, posicaoTabuleiro *);

void iniciarPartida(tabuleiro *, peca *);

#endif