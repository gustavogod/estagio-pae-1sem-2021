#ifndef __FILES_H__
#define __FILES_H__

/**
 * Recebe um file descriptor de um arquivo e retorna o tamanho em bytes do arquivo
 */
long fileLength(FILE *fd);
/**
 * Escreve no arquivo fd os dados da tabela tab encontrados na coluna da posição index
 */
void writeColumn(FILE *fd, table *tab, int index);

#endif