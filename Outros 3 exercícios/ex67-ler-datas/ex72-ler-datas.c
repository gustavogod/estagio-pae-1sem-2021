#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dates.h"

int main(int argc, char *argv[]){
    int n;
    scanf("%d ", &n);
    dates *dateList;
    dateList = readDates(n);
    printDates(dateList, n);
    free(dateList);
}