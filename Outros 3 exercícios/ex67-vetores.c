#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int *arr;
} array;

void checkMalloc(int *);
void readArray(array *);
void mergeArrays(const array *, const array *, array *);
void printArray(array const *);

int main(int argc, int *argv[]) {
    array arr1;
    scanf("%d", &arr1.size);
    arr1.arr = malloc(sizeof(int) * arr1.size);
    checkMalloc(arr1.arr);
    readArray(&arr1);

    array arr2;
    scanf("%d", &arr2.size);
    arr2.arr = malloc(sizeof(int) * arr2.size);
    checkMalloc(arr2.arr);
    readArray(&arr2);

    array arr3;
    arr3.size = arr1.size + arr2.size;
    arr3.arr = malloc(sizeof(int) * arr3.size);
    checkMalloc(arr3.arr);

    mergeArrays(&arr1, &arr2, &arr3);
    printArray(&arr3);

    free(arr1.arr);
    free(arr2.arr);
    free(arr3.arr);
}

void checkMalloc(int *p) {
    if(p == NULL){
        free(p);
        exit(-1);
    }
}

void readArray(array *arr){
    for(int i = 0; i < arr->size; i++){
        scanf("%d", &arr->arr[i]);
    }
}

void mergeArrays(const array *arr1, const array *arr2, array *arr3) {
    int j = 0;
    int k = 0;
    for (int i = 0; i < arr3->size; i++) {
        if (j < arr1->size && k < arr2->size){
            if (arr1->arr[j] < arr2->arr[k]){
                arr3->arr[i] = arr1->arr[j];
                j++;
            }
            else {
                arr3->arr[i] = arr2->arr[k];
                k++;
            }
        }
        else if (j < arr1->size){
            arr3->arr[i] = arr1->arr[j];
            j++;
        }
        else {
            arr3->arr[i] = arr2->arr[k];
            k++;
        }
    }
}

void printArray(array const *arr){
    for (int i = 0; i < arr->size; i++){
        printf("%d ", arr->arr[i]);
    }
    printf("\n");
}