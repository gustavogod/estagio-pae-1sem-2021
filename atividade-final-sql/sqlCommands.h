#ifndef __SQLCOMMANDS_H__
#define __SQLCOMMANDS_H__

#include "utils.h"

typedef struct {
    char fileName[FILE_NAME_SIZE];
    char columnName[COLUNM_NAME_SIZE];
} column;

typedef struct {
    column column;
    int nSel;
} selectSql;

typedef struct {
    char fileName[FILE_NAME_SIZE];
    int nFrom;
} fromSql;

typedef struct {
    column firstTerm; // aloca o termo da esquerda da comparação
    char *secondTermStr; // segundo termo da comparação, se for uma string constante
    column secondTerm; // segundo termo da comparação, se for a columa de outra tabela
    int nWheres;
} whereSql;

/**
 * Grava na posicao p do vetor slct os dados de um único comando select descrito em selectCommand 
 */
void recordSelect(selectSql *slct, const int p, char *selectCommand);
/**
 * Grava na posicao p do vetor where os dados de um único comando where descrito em whereCommand 
 */
void recordWhere(whereSql *where, const int p, char *whereCommand);
/**
 * Retorna um vetor de selectSql com os comandos selects gravados
 */
selectSql *allocateSelect(char *sqlCommand);
/**
 * Retorna um vetor de fromSql com os comandos from gravados
 */
fromSql *allocateFrom(char *sqlCommand);
/**
 * Retorna um vetor de whereSql com os comandos where gravados
 */
whereSql *allocateWhere(char *sqlCommand);

void freeWhere(whereSql *where);

#endif