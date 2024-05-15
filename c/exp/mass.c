#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gen_code(int fild[10][10], int diff){

  for(int i = 0; i < diff; i++){
    int x = rand()%10;
    int y = rand()%10;
    if (fild[x][y] == i){continue;}
    else (fild[x][y] = i);
  }
}

int main(){
  srand(time(NULL));
  int field[10][10];

  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      field[i][j] = 0;
    }
  }

  gen_code(field, 30);

  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      if (field[i][j] != 0){printf("1 ");}
      else {printf("0 ");}
    }
    printf("\n");
  }
}
