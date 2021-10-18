#include <stdio.h>

int main() {

  int plays[21]= {0};
  int i = 0;
  while(i < 21){

    scanf("%d",&plays[i]);

    if(i < 18){
      if(plays[i] == 10){
        plays[i + 1] = -1;
        i+=2;
      } 
      else{
        i++;
      }
    }
    else{

        if(plays[i] == 10){
          scanf("%d",&plays[i + 1]);
          scanf("%d",&plays[i + 2]);
          break;

      } 
      else{
          scanf("%d",&plays[i + 1]);
          if(plays[i] + plays[i + 1] == 10){
            scanf("%d",&plays[i + 2]);
            i = 21;
          } 
          else{
            plays[i + 2] = 0;
            i = 21;
          }
        }

    }

  }


  int p = 0;
  while(p < 21){

    if(p < 18){

      if(plays[p] == 10){
        printf("X _ | ");
        p+=2;
      } 
      else if(plays[p] + plays[p + 1] == 10){
        printf("%d / | ",plays[p]);
        p+=2;
      } 
      else{
        printf("%d %d | ",plays[p],plays[p + 1]);
        p+=2;
      }



    } 
    else{

      if(plays[p] == 10){
        printf("X ");
        p++;
      }
      else if(plays[p] + plays[p + 1] == 10){
        printf("%d / ",plays[p]);
        p+=2;
      }
      else if(p == 20){
        printf("%d ",plays[p]);
        p++;
      }
      else{
        printf("%d %d",plays[p],plays[p + 1]);
        p= 21;
      }
    }
  }

  printf("\n");


  int ponts = 0;
  int bonus = 0;

  int q = 0;
  while(q < 21){
    if(q < 18){

      if(plays[q] == 10){

        ponts += 10;
        if(plays[q + 2] == 10 && q != 16){
          bonus += plays[q + 2];
          bonus += plays[q + 4];
        } 
        else{
          bonus += plays[q + 2];
          bonus += plays[q + 3];
        }

      }
      else if(plays[q] + plays[q + 1] == 10){

        ponts += 10;
        bonus += plays[q + 2];

      } 
      else{

        ponts += plays[q] + plays[q + 1];

      }

      q+=2;

    } 
    else{
      if(plays[q] == 10){
        ponts += 10;
        ponts += plays[q + 1] +  plays[q + 2];
        q = 21;
    } 
    else if(plays[q] + plays[q + 1] == 10){
    ponts += 10 + plays[q + 2];
    q = 21;
    } 
    else{
    ponts+= plays[q] + plays[q + 1];
    q = 21;
    }

}
  }

  ponts = ponts + bonus;
  printf("%d",ponts);

  return 0;
}