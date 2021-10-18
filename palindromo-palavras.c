#include <stdio.h>

int main(int agrc, char *argv[]) {

  int quantity_of_numbers1;
  scanf("%d", &quantity_of_numbers1);
  int vector1[quantity_of_numbers1];
  
  for(int i = 0; i < quantity_of_numbers1; i++){
    scanf("%d", &vector1[i]);
  }

  int quantity_of_numbers2;
  scanf("%d", &quantity_of_numbers2);
  int vector2[quantity_of_numbers2];
  int quantity_of_numbers3 = quantity_of_numbers1 + quantity_of_numbers2;
  int vector3[quantity_of_numbers3];

  for(int i = 0; i < quantity_of_numbers2; i++){
    scanf("%d", &vector2[i]);
  }

  int j = 0;
  int k = 0;
  for(int i = 0; i < quantity_of_numbers3; i++){

    if (j < quantity_of_numbers1 && 
        k < quantity_of_numbers2) { // Então j e k ainda não ultrapassaram o tamanho dos vatores

        if (vector1[j] <= vector2[k]){    
            vector3[i] = vector1[j];
            j++;        
        }
        else {
            vector3[i] = vector2[k];
            k++;
        }
    }
    else if (j < quantity_of_numbers1){ 
        vector3[i] = vector1[j];
        j++;
    }
    else {
        vector3[i] = vector2[k];
        k++;
    }

    printf("%d ", vector3[i]);
  }
}  