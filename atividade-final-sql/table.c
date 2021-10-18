#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "myString.h"
#include "table.h"
#include "sqlCommands.h"

table *createTableFromFile(FILE *fd) {
    table *tab = malloc(sizeof(table) * 1);
    checkTableMalloc(tab);

    char line[BUFF_SIZE];
    fgets(line, BUFF_SIZE, fd);

    tab->nCol = strCount(line, "\t") + 1;
    tab->nLin = 10;
    tab->vals = malloc(sizeof(char **) * tab->nLin);
    checkLinesMalloc(tab, tab->vals);
    int nl = 0;
    while (1) {

        tab->vals[nl] = malloc(sizeof(char *) * tab->nCol);
        checkColumnsMalloc(tab, nl);

        char *token;
        const char delim[] = "\t";

        token = strtok(line, delim);
        int nc = 0;
        while(nc < tab->nCol) {
            tab->vals[nl][nc] = malloc(sizeof(char) * strlen(token));
            checkStringMalloc(tab, nl, nc);
            if(nc == tab->nCol - 1) { //Se estiver na última coluna da linha
                strncpy(tab->vals[nl][nc], token, strlen(token) - 1); //Assim não copia o \n do último caractere
            }
            else {
                strcpy(tab->vals[nl][nc], token);
            }
            //printf("%s\\#nc:%d#\n", tab->vals[nl][nc], nc);
            token = strtok(NULL, delim);
            nc++;
        }
        nl++;
        if(!fgets(line, BUFF_SIZE, fd)) { 
            break;
        }

        if(nl >= tab->nLin) {
            tab->nLin *= 2;
            tab->vals = realloc(tab->vals, sizeof(char **) * tab->nLin);
        }
    }
    tab->nLin = nl;
    return tab;
}

void checkTableMalloc(table *m) {
    if (m == NULL) {
        exit(-1);
    }
}

void checkLinesMalloc(table *m, char ***vals) {
    if (vals == NULL){
        free(m);
        exit(-1);
    }
}

void checkColumnsMalloc(table *m, int i) {
    if (m->vals[i] == NULL) {
        for (int k = 0; k < i; k++) {
            free(m->vals[k]);
        }
        free(m->vals);
        free(m);
        exit(-1);
    }
}

void checkStringMalloc(table *tab, int nl, int nc) {
    if(tab->vals[nl][nc] == NULL){
        for(int i = 0; i < nl; i++) {
            for(int j = 0; j < nc; j++) {
                free(tab->vals[i][j]);
            }
            free(tab->vals[i]);
        }
        free(tab->vals);
        free(tab);
        exit(-1);
    }
}



void destroyTable(table *m) {
    for (int i = 0; i < m->nLin; i++) {
        for (int j = 0; j < m->nCol; j++) {
            free(m->vals[i][j]);
        }
        free(m->vals[i]);
    }
    free(m->vals);
    free(m);
}

void printTable(table *m) {
    for (int i = 0; i < m->nLin; i++) {
        for (int j = 0; j < m->nCol; j++) {
            printf("%s\t", m->vals[i][j]);
        }
        printf("\n");
    }
}

int getColumnIndex(table *tab, char *columnName) {
    int cIndex = 0;
    while(memcmp(tab->vals[0][cIndex], columnName, strlen(columnName))) {
        cIndex++;
    }
    return cIndex;
}