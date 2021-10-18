#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef struct {
    int nLin;
    int nCol;
    float **vals;
} matrix;

matrix *createMatrix(int , int );

void checkMatrixMalloc(matrix *);

void checkLinesMalloc(matrix *, float **);

void checkColumnsMalloc(matrix *, int );

void destroyMatrix(matrix *);

void printMatrix(matrix *);

matrix *readMatrix();

void sumMatrix(matrix *, matrix *, matrix *);

void multiplyScalarMatrix(matrix *, matrix *, float );

void multiplyMatrix(matrix *, matrix *, matrix *);

void transposeMatrix(matrix *, matrix *);

#endif