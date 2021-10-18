#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "myString.h"
#include "sqlCommands.h"
#include "utils.h"

int getSubStringPosition(const char *str, const char *subStr) {
    int i = 0;
    int pos = 0;
    while(i < strlen(str)){
        int j = 0;
        if(str[i] == subStr[0]){
            pos = i;
            while(subStr[j] == str[i] && j < strlen(subStr) && i < strlen(str)) {
                i++;
                j++;
            }
        }
        // Se percorreu subStr inteira, então subStr está contida em str
        if(j == strlen(subStr)) {
            return pos;
        }
        i++;
    }
    return -1;
}

void getSubString(char *newStr, const char *str, int pStart, int pEnd) {
    //int const size = pEnd - pStart + 1;
    int j = 0;
    for(int i = pStart; i <= pEnd; i++) {
        newStr[j] = str[i];
        j++;
    }
    newStr[j] = '\0';
}

int strCount(const char *str, const char *subStr) {
    int count = 0;
    int i = 0;
    int pos = 0;
    while(i < strlen(str)){
        int j = 0;
        if(str[i] == subStr[0]){
            pos = i;
            while(subStr[j] == str[i] && j < strlen(subStr) && i < strlen(str)) {
                i++;
                j++;
            }
        }
        // Se percorreu subStr inteira, então subStr está contida em str
        if(j == strlen(subStr)) {
            count++;
        }
        i++;
    }
    return count;
}

void strReplace(char *str, const char *strFind, const char *strReplace) {
    char strAux[BUFF_SIZE];
    strcpy(strAux, str);
    
    char temp[BUFF_SIZE] = ""; 

    int nFinds = strCount(str, strFind);
    for(int i = 0; i < nFinds; i++) { //Repete a quantidade de vezes que strFind está contido em str
        int begin = getSubStringPosition(strAux, strFind); //Posição onde strFind começa em str
        char temp2[BUFF_SIZE];
        getSubString(temp2, strAux, 0, begin - 1); //temp2 sub-string de str, da posição 0 até a posição anterior à strFind
        strcat(temp, temp2);
        strcat(temp, strReplace); // strFind substituido por strReplace e armazenado em temp
        if((begin + strlen(strFind)) < strlen(strAux)) { // Verifica se strFind não está no fim da string
            char temp3[BUFF_SIZE];
            getSubString(temp3, strAux, begin + strlen(strFind), strlen(strAux) - 1); //Temp3 recebe o resto de strAux, da posição adiante de strFind
            strcpy(strAux, temp3);
            if(i == nFinds - 1) { // Se for a última iteração do laço
                strcat(temp, strAux);
            }
        }
    }
    if(nFinds){
        strcpy(str, temp);
    }
}

void removeSpaces(char *str) {
    char *temp = malloc(sizeof(char) * strlen(str));
    if (temp == NULL) {
        exit(-1);
    }
    int j = 0;
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] != ' ' && str[i] != '\n') {
            temp[j] = str[i];
            j++;
        }
    }
    for(int i = 0; i < j; i++) {
        str[i] = temp[i];
    }
    str[j] = '\0';
    free(temp);
}