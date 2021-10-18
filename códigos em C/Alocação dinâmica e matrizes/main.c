#include <stdio.h>

#include "matrix.h"

int main(int argc, char *argv[]){
    matrix *a = readMatrix(a);
    //matrix *b = readMatrix(b);
    matrix *r = createMatrix(a->nCol, a->nLin);
    //sumMatrix(r, a, b);
    transposeMatrix(r, a);
    printMatrix(a);
    printf("\n");
    printMatrix(r);
    destroyMatrix(r);
    destroyMatrix(a);
    //destroyMatrix(b);
}