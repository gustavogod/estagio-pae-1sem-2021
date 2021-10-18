#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "defines.h"

/* typedef struct {
    int nLin;
    int nCol;
    int **vals;
} map; */

map *createMap(int nl, int nc) {
    map *m = malloc(sizeof(map) * 1);
    checkMapMalloc(m);
    m->nLin = nl;
    m->nCol = nc;
    m->vals = malloc(sizeof(int *) * nl);
    checkLinesMalloc(m, m->vals);
    for (int i = 0; i < nl; i++){
        m->vals[i] = malloc(sizeof(int) * nc);
        checkColumnsMalloc(m, i);
        for (int j = 0; j < nc; j++) {
            m->vals[i][j] = 1;
        }
    }
    m->vals[nl - 1][0] = INICIO; //Marca o início do caminho
    m->vals[0][nc - 1] = DESTINO; //Marca o fim do caminho
    return m;
}

void checkMapMalloc(map *m) {
    if (m == NULL) {
        exit(-1);
    }
}

void checkLinesMalloc(map *m, int **vals) {
    if (vals == NULL){
        free(m);
        exit(-1);
    }
}

void checkColumnsMalloc(map *m, int i) {
    if (m->vals[i] == NULL) {
        for (int k = 0; k < i; k++) {
            free(m->vals[k]);
        }
        free(m->vals);
        free(m);
        exit(-1);
    }
}

void destroyMap(map *m) {
    for (int i = 0; i < m->nLin; i++) {
        free(m->vals[i]);
    }
    free(m->vals);
    free(m);
}

void printMap(map *m) {
    for (int i = 0; i < m->nLin; i++) {
        for (int j = 0; j < m->nCol; j++) {
            printf("%d ", m->vals[i][j]);
        }
        printf("\n");
    }
}

int runRobot(map *m){
    position pRobot;

    pRobot.pLin = m->nLin - 1; // set initial position
    pRobot.pCol = 0; // set initial position

    int count = 0;
    int nextMove;
    while (1){
        nextMove = checkAround(m, &pRobot);
        if (nextMove == -1 || nextMove == DESTINO){
            break;
        }
        count += nextMove;
    }

    printf("%d\n", count); // imprime o custo do caminho
    
    if (nextMove == DESTINO){
        return 1;
    }
    return 0;
}

int checkAround(map *m, position *pRobot) {
    int lin = pRobot->pLin;
    int col = pRobot->pCol;

    int costNorth; // custo p andar p cima
    int costEast; // custo p andar p frente

    if (lin == 0){ // Só pode ter custo p ir p frente
        costEast = m->vals[lin][col + 1];
    }
    else if (col == m->nCol - 1){ // Só pode ter custo p ir p cima
        costNorth = m->vals[lin - 1][col];
    }
    else {
        costEast = m->vals[lin][col + 1];
        costNorth = m->vals[lin - 1][col];
    }

    int cost = -1;

    if ((lin == 0 && costEast == DESFILADEIRO) || // Está na primeira linha e não pode p frente OU
        col == m->nCol - 1 && costNorth == DESFILADEIRO) { // está na última coluna e não pode ir p cima
            return cost;
    }
    else if (lin == 0 && costEast != DESFILADEIRO){ // está na primeira linha e pode ir p frente
        cost = costEast;
        pRobot->pCol++; // atualiza posição do robô
        //printf(" Para o leste, custo %d\n", cost);
    }
    else if (col == m->nCol - 1 && costNorth != DESFILADEIRO){ // está na última coluna e pode ir p cima
        cost = costNorth;
        pRobot->pLin--;
        //printf(" Para o norte, custo %d\n", cost);
    }
    else {
        // ver se pode ir p frente ou p cima
        if (costNorth != costEast){
            if (costNorth < costEast){ // vai p cima 
                cost = costNorth;
                pRobot->pLin--;
                //printf(" Para o norte, custo %d\n", cost);
            }
            else { // vai p frente
                cost = costEast;
                pRobot->pCol++;
                //printf(" Para o leste, custo %d\n", cost);
            }
        }
        else if (costEast != DESFILADEIRO){ // Vai p frente. E sabe-se que costNorth != DESFILADEIRO
            cost = costEast;
            pRobot->pCol++;
            //printf(" Para o leste, custo %d\n", cost);
        }
        // Se norte e leste forem desfiladeiros, vai direto p return -1
    }
    return cost;
}