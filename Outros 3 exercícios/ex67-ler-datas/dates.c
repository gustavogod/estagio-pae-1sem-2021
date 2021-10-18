#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dates.h"

#define PASSEIAQUI printf("%s:%d\n", __FILE__, __LINE__);

void checkDateMalloc(dates *p) {
    if(p == NULL){
        free(p);
        exit(-1);
    }
}

dates *readDates(int const n) {
    dates *d = malloc(sizeof(dates) * n);
    checkDateMalloc(d);
    dates temp;
    char inputDate[11];
    char *token;
    const char delim[2] = "/";
    for(int i = 0; i < n; i++) {
        //scanf("%s", inputDate);
        fgets(inputDate, 11, stdin);
        scanf("\n"); // consumir \n do buffer p não dar segmentation fault
        token = strtok(inputDate, delim);
        temp.day = atoi(token);
        token = strtok(NULL, delim);

        temp.month = atoi(token);
        token = strtok(NULL, delim);
        

        temp.year = atoi(token);

        temp.isValid = dateIsValid(temp);
        d[i] = temp;
    }
    return d;
}

int dateIsValid(dates const date) {
    if (date.year < 1) {
        return 0;
    }
    if (date.day < 1 || date.day > 31) {
        return 0;
    }
    if (date.month < 1 || date.month > 12) {
        return 0;
    }
    if ((date.month == ABR ||
        date.month == JUN ||
        date.month == SET ||
        date.month == NOV) &&
        date.day == 31) {
            return 0;
        }
    if (date.month == FEV && date.day > 29) {
        return 0;
    }
    // Ver se é ano bisexto
    int isLeapYear = date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0);
    if (!isLeapYear && date.month == FEV && date.day > 28) {
        return 0;
    }

    return 1;
}

void printDates(dates const *dates, int const n) {
    char months[12][10] = {
        "janeiro", "fevereiro", "marco", "abril", "maio", "junho",
        "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"
        };

    for(int i = 0; i < n; i++){
        if(!dates[i].isValid){
            printf("DATA INVALIDA\n");
        }
        else {
            printf("%02d de %s de %04d\n", dates[i].day, months[dates[i].month - 1], dates[i].year);
        }
    }
}