#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "defines.h"

int main(int argc, char *argv[]){
    int nLin;
    scanf("%d", &nLin);
    int nCol;
    scanf("%d", &nCol);

    map *m = createMap(nLin, nCol);

    int lin, col;
    int obstacle;
    while (1) {
        int s;
        scanf("%d", &lin);
        scanf("%d", &col);
        scanf("%d", &obstacle);
        writeMap(m, lin, col, obstacle);
        if (feof(stdin)){
            break;
        }
    }

    //printMap(m);

    int out = runRobot(m);

    printf("%d\n", out);
    
    destroyMap(m);
}