#include <stdio.h>

#include "table.h"


long fileLength(FILE *fd) {
    fseek(fd, 0L, SEEK_END);
    return ftell(fd);    
}

void writeColumn(FILE *fd, table *tab, int index) {
    // i = 1, pois a primeira linha tem os cabeçalhos da tabela
    for(int i = 1; i < tab->nLin; i++) { // Percorre as linhas de progs p acessar a coluna Siglas
        // ir gravando os dados de Sigla no arquivo
        fprintf(fd, "%s\t", tab->vals[i][index]);
    }    
}