#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/* typedef struct {
    int nLin;
    int nCol;
    float **vals;
} matrix; */

matrix *createMatrix(int nl, int nc) {
    matrix *m = malloc(sizeof(matrix) * 1);
    checkMatrixMalloc(m);
    m->nLin = nl;
    m->nCol = nc;
    m->vals = malloc(sizeof(float *) * nl);
    checkLinesMalloc(m, m->vals);
    for (int i = 0; i < nl; i++){
        m->vals[i] = malloc(sizeof(float) * nc);
        checkColumnsMalloc(m, i);
        for (int j = 0; j < nc; j++) {
            m->vals[i][j] = 0.0;
        }
    }
    return m;
}

void checkMatrixMalloc(matrix *m) {
    if (m == NULL) {
        exit(-1);
    }
}

void checkLinesMalloc(matrix *m, float **vals) {
    if (vals == NULL){
        free(m);
        exit(-1);
    }
}

void checkColumnsMalloc(matrix *m, int i) {
    if (m->vals[i] == NULL) {
        for (int k = 0; k < i; k++) {
            free(m->vals[k]);
        }
        free(m->vals);
        free(m);
        exit(-1);
    }
}

void destroyMatrix(matrix *m) {
    for (int i = 0; i < m->nLin; i++) {
        free(m->vals[i]);
    }
    free(m->vals);
    free(m);
}

void printMatrix(matrix *m) {
    for (int i = 0; i < m->nLin; i++) {
        for (int j = 0; j < m->nCol; j++) {
            printf("%0.2f ", m->vals[i][j]);
        }
        printf("\n");
    }
}

matrix *readMatrix() {
    int nl;
    int nc;
    scanf("%d", &nl);
    scanf("%d", &nc);
    matrix *m = createMatrix(nl, nc);
    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            scanf("%f", &m->vals[i][j]);
        }
    }
    return m;
}

void sumMatrix(matrix *r, matrix *a, matrix *b){
    // Check dimensions 
    if (a->nLin == b->nLin &&
        a->nCol == b->nCol &&
        r->nLin == a->nLin &&
        r->nCol == a->nCol) {
            for (int i = 0; i < a->nLin; i++) {
                for (int j = 0; j < a->nCol; j++) {
                    r->vals[i][j] = a->vals[i][j] + b->vals[i][j];
                }
            }
        }
}

void multiplyScalarMatrix(matrix *r, matrix *a, float f) {
    if (r->nLin == a->nLin && 
        r->nCol == a->nCol) {
            for (int i = 0; i < a->nLin; i++) {
                for (int j = 0; j < a->nCol; j++) {
                    r->vals[i][j] = a->vals[i][j] * f;
                }
            }
        }
}

void multiplyMatrix(matrix *r, matrix *a, matrix *b) {
    // Check dimensions 
    if (a->nCol == b->nLin &&
        r->nLin == a->nLin &&
        r->nCol == b->nCol) {
            for (int i = 0; i < r->nLin; i++) {
                for (int j = 0; j < r->nCol; j++) {
                    r->vals[i][j] = 0;
                    for (int k = 0; k < a->nCol; k++) {
                        r->vals[i][j] += a->vals[i][k] * b->vals[k][j];
                    }
                }
            }
        }    
}

void transposeMatrix(matrix *r, matrix *a) {
    for (int i = 0; i < r->nLin; i++) {
        for (int j = 0; j < r->nCol; j++) {
            r->vals[i][j] = a->vals[j][i];
        }
    }
}