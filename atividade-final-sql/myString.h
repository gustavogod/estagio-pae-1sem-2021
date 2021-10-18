#ifndef __MYSTRING_H__
#define __MYSTRING_H__

/**
 * Se subStr está contida em str, então retorna a posição do primeiro caractere de subStr em str
 * Se subStr não está contida em str, retorna -1
 */
int getSubStringPosition(const char *str, const char *subStr);
/**
 * Atribui à newStr uma sub-string de str, da posição pStart até pEnd
 */
void getSubString(char *newStr, const char *str, int pStart, int pEnd);
/**
 * Retorna a quantidade de ocorrências da string subStr na string str
 */
int strCount(const char *str, const char *subStr);
/**
 * Substitui todas as ocorrências de strFind encontradas em str por strReplace
*/
void strReplace(char *str, const char *strFind, const char *strReplace);
/**
 * Remove espaços em branco e quebras de linha da string str
 */
void removeSpaces(char *str);

#endif