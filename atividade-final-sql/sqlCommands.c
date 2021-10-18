#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sqlCommands.h"
#include "myString.h"

void recordSelect(selectSql *slct, const int p, char *selectCommand) {
    const char *delim = ".";
    char *token;
    char *rest;
    token = strtok_r(selectCommand, delim, &rest); // Retorna o nome do arquivo
    strcpy(slct[p].column.fileName, token); // Grava o nome do arquivo em slct
    token = strtok_r(NULL, delim, &rest); // Retorna o nome da coluna
    strcpy(slct[p].column.columnName, token); // Grava o nome da coluna
}

void recordWhere(whereSql *where, const int p, char *whereCommand) {
    const char *delim = "=";
    char *token;
    char *rest;
    token = strtok_r(whereCommand, delim, &rest);
    char firtsTerm[BUFF_SIZE];
    strcpy(firtsTerm, token); // Grava o primeiro termo do where
    removeSpaces(firtsTerm);

    const char *delim2 = ".";
    char *token2;
    char *rest2;
    token2 = strtok_r(firtsTerm, delim2, &rest2);
    strcpy(where[p].firstTerm.fileName, token2); //Grava o nome do arquivo do primeiro termo
    token2 = strtok_r(NULL, delim2, &rest2);
    strcpy(where[p].firstTerm.columnName, token2); //Grava o nome da coluna do primeiro termo

    token = strtok_r(NULL, delim, &rest); // Pega o segundo termo do where
    char secondTerm[BUFF_SIZE];
    strcpy(secondTerm, token); // Grava o segundo termo do where em secondTerm
    if(strCount(secondTerm, "\"")) { // Se tiver aspas, segundo termo é uma string constante
        char temp[BUFF_SIZE], temp2[BUFF_SIZE];
        // Atribui à temp a string sem a primeira aspas
        getSubString(temp, secondTerm, getSubStringPosition(secondTerm, "\"") + 1, strlen(secondTerm));
        // Atribui à temp2 a string sem a segunda aspas
        getSubString(temp2, temp, 0, getSubStringPosition(temp, "\"") -  1);

        where[p].secondTermStr = malloc(sizeof(char) * strlen(temp2));
        if(where[p].secondTermStr == NULL) {
            exit(-1);
        }
        strcpy(where[p].secondTermStr, temp2);
    }
    else { // Se não, segundo termo é do tipo column
        removeSpaces(secondTerm);
        const char *delim3 = ".";
        char *token3;
        char *rest3;
        token3 = strtok_r(secondTerm, delim3, &rest3);
        strcpy(where[p].secondTerm.fileName, token3); //Grava o nome do arquivo do segundo termo
        token3 = strtok_r(NULL, delim3, &rest3);
        strcpy(where[p].secondTerm.columnName, token3); //Grava o nome da coluna do segundo termo    
        where[p].secondTermStr = NULL; // Para fins de verificação    
    }
}

selectSql *allocateSelect(char *sqlCommand) {
    //Extrair dados do select
    selectSql *sel;
    char tempSelect[BUFF_SIZE];
    char fr[] = " from ";
    int pFrom = getSubStringPosition(sqlCommand, fr); // Posição onde o comando do select termina
    getSubString(tempSelect, sqlCommand, 7, pFrom); //Posição 7 é onde começa a descrição do select
    removeSpaces(tempSelect);

    
    int nSelects = strCount(tempSelect, ",") + 1; // Quantidade de comandos select
    
    sel = malloc(sizeof(selectSql) * nSelects);
    sel->nSel = nSelects;
    if(nSelects == 1) { // Se tiver apenas um select, então armazena na posição 0
        recordSelect(sel, 0, tempSelect);
    }
    else { // Se tem vírgula, então tem mais de um select
        const char *delim = ",";
        char *token;
        char *rest;
        int i = 0;

        token = strtok_r(tempSelect, delim, &rest);

        while(token != NULL) {
            char temp[BUFF_SIZE];
            strcpy(temp, token);
            recordSelect(sel, i, temp);
            token = strtok_r(NULL, delim, &rest);  
            i++;         
        }
    }
    for (int i = 0; i < nSelects; i++) {
        printf("Selecionar arquivo #%s#, coluna #%s#\n", sel[i].column.fileName, sel[i].column.columnName);
    }
    return sel;    
}

fromSql *allocateFrom(char *sqlCommand) {
    fromSql *from;
    char tempFrom[BUFF_SIZE];
    char fr[] = " from ";
    char whr[] = " where ";
    int pInitFrom = getSubStringPosition(sqlCommand, fr) + strlen(fr); //Posição onde os comandos do from começam
    int pWhere = getSubStringPosition(sqlCommand, whr); //Posição onde o comando from termina
    if(pWhere == -1) { // Não tem comando where
        getSubString(tempFrom, sqlCommand, pInitFrom, strlen(sqlCommand) - 1);
    }
    else {
        getSubString(tempFrom, sqlCommand, pInitFrom, pWhere);
    }
    removeSpaces(tempFrom);

    int nFroms = strCount(tempFrom, ",") + 1; //Quantidade de comandos from
    from = malloc(sizeof(fromSql) * nFroms);
    from->nFrom = nFroms;

    if(from->nFrom == 1) {
        strcpy(from[0].fileName, tempFrom);
    }
    else {
        const char *delim = ",";
        char *token;
        char *rest;
        int i = 0;

        token = strtok_r(tempFrom, delim, &rest);

        while(token != NULL) {
            strcpy(from[i].fileName, token);
            token = strtok_r(NULL, delim, &rest);
            i++;
        }
    }

    for (int i = 0; i < from->nFrom; i++) {
        printf("Utiliza tabela %s\n", from[i].fileName);
    }

    return from;
}

whereSql *allocateWhere(char *sqlCommand){
    //Extrair dados do where
    whereSql *where;
    char tempWhere[BUFF_SIZE];
    char wr[] = " where ";
    int pInitWhere = getSubStringPosition(sqlCommand, wr) + strlen(wr); //Posição onde os comandos do where começam
    getSubString(tempWhere, sqlCommand, pInitWhere, strlen(sqlCommand) - 3); // Atribui a tempWhere toda a parte que descreve o comando where
    // O -3 é p não pegar o \n da última posição

    //Dessa vez os espaços e quebras de linha não são removidos nessa função, mas dentro do recordWhere()
    
    int nWheres = strCount(tempWhere, "and") + 1; // Quantidade de comandos where
    where = malloc(sizeof(whereSql) * nWheres);
    where->nWheres = nWheres;
    if(where->nWheres == 1) { // Se tiver apenas um where, então armazena na posição 0
        recordWhere(where, 0, tempWhere);
    }
    else { // Se tem vírgula, então tem mais de um select
        strReplace(tempWhere, " and ", "&"); // Substitui os operadores and por &

        //printf("COMANDO WHERE: #%s#\n", tempWhere);

        const char *delim = "&";
        char *token;
        char *rest;
        int i = 0;

        token = strtok_r(tempWhere, delim, &rest);

        while(token != NULL) {
            char temp[BUFF_SIZE];
            strcpy(temp, token);
            recordWhere(where, i, temp);
            token = strtok_r(NULL, delim, &rest);  
            i++;         
        }
    }
    for (int i = 0; i < where->nWheres; i++) {
        printf("Quando coluna #%s# do arquivo #%s#", where[i].firstTerm.columnName, where[i].firstTerm.fileName);
        if(where[i].secondTermStr) {
            printf(" for igual à #\"%s\"#\n", where[i].secondTermStr);
        }
        else {
            printf(" for igual à coluna #%s# do arquivo #%s#\n", where[i].secondTerm.columnName, where[i].secondTerm.fileName);
        }
    }
    return where;        
}

void freeWhere(whereSql *where) {
    for(int i = 0; i < where->nWheres; i++) {
        if(where[i].secondTermStr) {
            free(where[i].secondTermStr);
        }
    }
    free(where);
}