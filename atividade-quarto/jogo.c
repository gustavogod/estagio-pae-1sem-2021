#include <stdio.h>

#include "tabuleiro.h"
#include "jogo.h"

char hexa[numPecas] = "0123456789ABCDEF";

int pecasDisponiveis = numPecas;

int indexHexa(char c){
    int i = 0;
    while (c != hexa[i] && hexa[i] != '\0'){
        i++;
    }
    return i;
}

void inicializarPecas(peca *pecas){
    for (int i = 0; i < numPecas; i++){
        pecas[i].idPeca = hexa[i];
        pecas[i].atributos = i;
        pecas[i].disponivel = 1;
    }
}

void inicializarTabuleiro(tabuleiro *tab){
    for (int i = 0; i < numPecas; i++){
        tab->posicao[i].idPosicao = '\0';
    }
}

void imprimirTabuleiro(tabuleiro *tab){
    for (int i = 0; i < numPecas; i++){
        if(!tab->posicao[i].idPosicao){
            printf("-");
        }
        else {
            printf("%c", tab->posicao[i].p.idPeca);
        }
        if (!((i + 1) % 4)){
            printf("\n");
        }
    }
}    

void imprimirSequenciaVencedora(posicaoTabuleiro *posicoesVencedor){
    for (int i = 0; i < 4; i++){
        printf("%c", posicoesVencedor[i].idPosicao);
    }
    printf("\n");
}

void imprimirAtributoVencedor(int alguemGanhou){
    switch (alguemGanhou) {
        case BRANCA:
            printf("branca");
        break;
        case ESCURA:
            printf("escura");
        break; 
        case GRANDE:
            printf("grande");
        break;
        case PEQUENA:
            printf("pequena");
        break;          
        case CIRCULAR:
            printf("circular");
        break;
        case QUADRADA:
            printf("quadrada");
        break;                 
        case SOLIDA:
            printf("solida");
        break;
        case OCA:
            printf("oca");
        break;                                                    
    }
    printf("\n");
}

int proximaJogada(tabuleiro *tab, peca *pecas){
    char pecaEscolhida;
    scanf(" %c", &pecaEscolhida);
    char pecaColocada;
    scanf(" %c", &pecaColocada);

    int index = indexHexa(pecaEscolhida);

    pecas[index].disponivel = 0;
    peca pAux = pecas[index];

    index = indexHexa(pecaColocada);

    tab->posicao[index].p = pAux;
    tab->posicao[index].idPosicao = hexa[index];

    return --pecasDisponiveis;
}

int isolaBit(int num, int i){
    return (num & (1 << i)) >> i;
}

int somaBits(posicaoTabuleiro *posicoes, int i){
    int soma = 0;
    for(int j = 0; j < 4; j++){
        soma += isolaBit(posicoes[j].p.atributos, i);
    }
    return soma;
}

int verificaVencedor(posicaoTabuleiro *posicoes){
    int iAtributo = 3;
    int alguemGanhou = 0;
    int soma = 0;
    //Percorre cada atributo das peças, definido pelo i-esimo bit
    //Começa do bit da esqueda até o bit da direita
    while (iAtributo >= 0 && !alguemGanhou){
        soma = somaBits(posicoes, iAtributo);
        if (soma == 4){
            alguemGanhou = 1;
        }
        else if (soma == 0){
            alguemGanhou = 1;
        }
        iAtributo--;
    }

    if (alguemGanhou){
        iAtributo++;
        if (iAtributo == COR){
            if (soma == 0){
                return BRANCA;
            }
            return ESCURA;
        }        
        if (iAtributo == ALTURA){
            if (soma == 0){
                return GRANDE;
            }
            return PEQUENA;
        }   
        if (iAtributo == FORMATO){
            if (soma == 0){
                return CIRCULAR;
            }
            return QUADRADA;
        }             
        if (iAtributo == PREENCHIMENTO){
            if (soma == 0){
                return SOLIDA;
            }
            return OCA;
        }
    }
    return 0;
}

int temVencedor(tabuleiro *tab, posicaoTabuleiro *posicoesVencedor){
    int alguemGanhou = 0;
    // Verificar linhas
    for (int i = 0; i < numPecas; i+=4){
        int j = 0;
        int linhaValida = 1; // Isto é, se todas as posições da linha tiverem alguma peça
        while (j < 4 && linhaValida){
            if (tab->posicao[i+j].idPosicao){
                posicoesVencedor[j] = tab->posicao[i+j];
            }
            else {
                linhaValida = 0;
            }
            j++;
        }
        if (linhaValida){
            alguemGanhou = verificaVencedor(posicoesVencedor);
        } 
        if (alguemGanhou){
            return alguemGanhou;
        } 
    }
    // Verifica colunas
    for (int i = 0; i < 4; i++){
        int colunaValida = 1;
        int j = 0;
        int k = 0;
        while (k < 4 && colunaValida){
            if (tab->posicao[i+j].idPosicao){
                posicoesVencedor[k] = tab->posicao[i+j];
            }
            else {
                colunaValida = 0;
            }
            k++;
            j += 4;
        }
        if (colunaValida){
            alguemGanhou = verificaVencedor(posicoesVencedor);
        }
        if (alguemGanhou){
            return alguemGanhou;
        }
    }
    // Primeira diagonal
    // Tem que melhorar esse código 
    if (tab->posicao[0].idPosicao != '\0' && 
        tab->posicao[5].idPosicao != '\0' && 
        tab->posicao[10].idPosicao != '\0' && 
        tab->posicao[15].idPosicao != '\0') {

        posicoesVencedor[0] = tab->posicao[0];
        posicoesVencedor[1] = tab->posicao[5];
        posicoesVencedor[2] = tab->posicao[10];
        posicoesVencedor[3] = tab->posicao[15];

        alguemGanhou = verificaVencedor(posicoesVencedor);

        if (alguemGanhou){
            return alguemGanhou;
        }
    }
    // Segunda diagonal        
    if (tab->posicao[3].idPosicao && tab->posicao[6].idPosicao && tab->posicao[9].idPosicao && tab->posicao[12].idPosicao){
        posicoesVencedor[0] = tab->posicao[3];
        posicoesVencedor[1] = tab->posicao[6];
        posicoesVencedor[2] = tab->posicao[9];
        posicoesVencedor[3] = tab->posicao[12];

        alguemGanhou = verificaVencedor(posicoesVencedor);

        if (alguemGanhou){
            return alguemGanhou;
        }        
    }
    
    return 0;
}

void iniciarPartida(tabuleiro *tab, peca *pecas){
    int alguemGanhou = 0;
    int jogador = 1;
    posicaoTabuleiro posicoesVencedor[4];
    while (pecasDisponiveis && !alguemGanhou){
        if (jogador == 1){
            proximaJogada(tab, pecas);
            jogador++;
        }
        else if (jogador == 2) {
            proximaJogada(tab, pecas);
            jogador--;
        }
        alguemGanhou = temVencedor(tab, posicoesVencedor);
    }

    if (alguemGanhou){
        imprimirTabuleiro(tab);
        printf("%d\n", jogador);
        imprimirSequenciaVencedora(posicoesVencedor);
        imprimirAtributoVencedor(alguemGanhou);
    }
    else {
        imprimirTabuleiro(tab);
        printf("%d\n", alguemGanhou);
    }
}

