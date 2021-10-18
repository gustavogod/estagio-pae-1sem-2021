#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sqlCommands.h"
#include "myString.h"
#include "table.h"
#include "file.h"
#include "utils.h"

#define PASSEIAQUI printf("PASSEI AQUI - %s:%d\n", __FILE__, __LINE__);

int main(int argv, char *argc[]) {
    char sqlCommand[BUFF_SIZE];
    fgets(sqlCommand, BUFF_SIZE, stdin);

    selectSql *sel; // Armazenar os comandos select
    sel = allocateSelect(sqlCommand);
    //printf("N Selects: %d\n", nSel);
    
    fromSql *from; // Armazenar os comandos do from
    from = allocateFrom(sqlCommand);
    //printf("N Froms: %d\n", nFrom);

    whereSql *where;
    int hasWhere = getSubStringPosition(sqlCommand, " where ");
    if(hasWhere > -1){
        where = allocateWhere(sqlCommand);
    }
    
    FILE *fdDocentes;
    FILE *fdProgs;
    FILE *fdTrabalhos;
    fdDocentes = fopen(PATH_DOCENTES, "r");
    fdProgs = fopen(PATH_PROGS, "r");
    fdTrabalhos = fopen(PATH_TRABALHOS, "r");

    table *tableDocentes = createTableFromFile(fdDocentes);
    table *tableProgs = createTableFromFile(fdProgs);
    table *tableTrabalhos = createTableFromFile(fdTrabalhos);
    //printTable(tableTrabalhos);


    FILE *fdOut; 
    fdOut = fopen("./out.txt", "w"); // Onde as saídas vão ser escritas

    // Código já resolve tudo quando tem apenas SELECT e FROM
    int i = 0;
    while(i < sel->nSel) {
        char sDoc[] = "Docentes";
        char sProgs[] = "Progs";
        char sTrab[] = "Trabalhos";
        int columnIndex;
        // ifs para verificar de qual arquivo é pra buscar a coluna
        if(!memcmp(sel[i].column.fileName, sDoc, strlen(sDoc))) { // memcmp() Retorna 0 se as duas strings forem iguais
            columnIndex = getColumnIndex(tableDocentes, sel[i].column.columnName); // Retorna o index da coluna correspondente do select
            writeColumn(fdOut, tableDocentes, columnIndex);
        }
        else if(!memcmp(sel[i].column.fileName, sProgs, strlen(sProgs))) {
            columnIndex = getColumnIndex(tableProgs, sel[i].column.columnName);
            writeColumn(fdOut, tableProgs, columnIndex);
        }
        else if(!memcmp(sel[i].column.fileName, sTrab, strlen(sTrab))){
            columnIndex = getColumnIndex(tableTrabalhos, sel[i].column.columnName);
            writeColumn(fdOut, tableTrabalhos, columnIndex);
        }
        fprintf(fdOut, "\n");
        i++;
    }

    //table *tableOut = createTableFromFile(fdOut);
    //printTable(tableOut);

    //fazer função para organizar arquivo de saída

    //começar a implementar as condições do where

    free(sel);
    free(from);
    if(hasWhere > -1){
        freeWhere(where);
    }
    fclose(fdDocentes);
    fclose(fdProgs);
    fclose(fdTrabalhos);
    fclose(fdOut);
    destroyTable(tableDocentes);
    destroyTable(tableProgs);
    destroyTable(tableTrabalhos);
}