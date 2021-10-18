#ifndef __MAP_H__
#define __MAP_H__

#include "defines.h"

typedef struct {
    int nLin;
    int nCol;
    int **vals;
} map;

typedef struct {
   int pLin;
   int pCol; 
} position;


map *createMap(int , int );

void checkMapMalloc(map *);

void checkLinesMalloc(map *, int **);

void checkColumnsMalloc(map *, int );

void destroyMap(map *);

void printMap(map *);

void writeMap(map *, int , int , int );

/**
 * Imprime o custo do caminho percorrido
 * Retorna 1 se chegar no destino
 * Retorna 0 se não chegar
 */
int runRobot(map *);

/**
 * Verifica se o robô pode se movimentar a partir da sua posição
 * Se puder, então a posição é atualizada e retorna o custo do movimento
 * Se movimentar e chegar no destino, retorna DESTINO
 * Se não puder movimentar, retorna -1
 */
int checkAround(map *, position *);

#endif