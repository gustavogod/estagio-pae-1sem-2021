#ifndef __TABLE_H__
#define __TABLE_H__

#include <stdio.h>

typedef struct {
    int nLin;
    int nCol;
    char ***vals;
} table;

table *createTableFromFile(FILE *fd);

void checkTableMalloc(table *m);

void checkLinesMalloc(table *m, char ***vals);

void checkColumnsMalloc(table *m, int i);

void destroyTable(table *m);

void printTable(table *m);

void checkStringMalloc(table *tab, int nl, int nc);
/**
 * Recebe uma tabela e o nome de uma coluna
 * Retorna o valor do index da coluna na respectiva tabela
 */
int getColumnIndex(table *tab, char *columnName);

#endif