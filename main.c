#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "libs/fielddata.c"


struct BombCoords
{
  int x;
  int y;
  struct BombCoords* next;
};

int choseDifficulty();
void drowField(int rov, int col, int corx, int cory, int diff);
void addFlag(int cory, int corx);
void genCode(struct BombCoords** bb, int diff, int rov, int col);


int main(void)
{
  struct BombCoords *bombCoords = NULL;
  int rov, col, corx = 0, cory = 0, diff;
  char move;
  printf("Введите масштаб поля(3x7)> ");
  scanf("%dx%d", &rov ,&col);
  corx = 0;
  cory = 0;

  diff = choseDifficulty();


  while(1)
  {
    drowField(rov, col, corx, cory, diff);
    scanf("\n%c", &move);

    switch(move) //Определение следующего хода
    {
    case 'w':
        cory--;
        break;
    case 'a':
        corx--;
        break;
    case 's':
        cory++;
        break;
    case 'd':
        corx++;
        break;
    case 'e':
        system("cls || clear");
        printf("By!!");
        return 0;
    case 'f':
        addFlag(corx, cory);
        break;
    default:
        break;
    }
  }
}




int choseDifficulty()
{
  int diff = 0;
  while (diff != 1 && diff != 2 && diff != 3) {
    system("cls || clear");
    printf("Enter your difficulty:\n1 - easy (10%% bombs)\n2 - normal (30%% bombs)\n3 - hard (50%% bombs)\n> ");
    scanf("%d", &diff);
  }
  return diff;
}

void drowField(int rov, int col, int corx, int cory, int diff)
{
  system("cls || clear");
  printf("X - coursour; # - closed cell; F - your flag\n");
  printf("Your difficult: ");
  if (diff == 1){printf("easy\n");}
  else if (diff == 2){printf("normal\n");}
  else if (diff == 3){printf("hard\n");}
  for(int i = 0; i < col; i++)
  {
    for(int j = 0; j < rov; j++)
    {
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf("X");}
      else{printf("#");}
    }
    printf("\n");
  }
}

void addFlag(int cory, int corx)
{
  int x = cory + corx;
  //пока хз как но нужно сделать сохранение шлагов в массив и в функции отрисовки нужно сравнивать с этим массивом
}

/*void genCode(struct BombCoords** bb, int diff, int rov, int col)
{
  double dd = 0;
  int bombscol = 0;
  double resus = bombscol / (rov*col);
  switch (diff) 
  {
    case 1:
      dd = 0.1;
      break;
    case 2:
      dd = 0.3;
      break;
    case 3:
      dd = 0.5;
      break;
  }
  srand(time(NULL));
  for(int i = 0; i < col; i++)
  {
    for(int j = 0; j < col; j++)
    {
      int r = rand() % 2;
      if (r == 1)
      {
        if (resus > dd)
        {
          struct BombCoords* new_bomb = (struct BombCoords*)malloc(sizeof(struct BombCoords));
          bombscol++;
          //добавление координат новой бомбы
        }
      }
    }
  }
}*/

void genCode(struct BombCoords** bb, int diff, int rov, int col) {
    int bombscol = 0;
    double resus = (double)bombscol / (rov * col);
    double dd = 0;

    switch (diff) {
        case 1:
            dd = 0.1;
            break;
        case 2:
            dd = 0.3;
            break;
        case 3:
            dd = 0.5;
            break;
    }

    srand(time(NULL));

    for (int i = 0; i < rov; i++) {
        for (int j = 0; j < col; j++) {
            int r = rand() % 2;
            if (r == 1) {
                bombscol++;
                resus = (double)bombscol / (rov * col);
                if (resus > dd) {
                    struct BombCoords* new_bomb = (struct BombCoords*)malloc(sizeof(struct BombCoords));
                    if (new_bomb != NULL) {
                        new_bomb->x = i;
                        new_bomb->y = j;
                        // Ваша логика добавления новой бомбы
                    }
                }
            }
        }
    }
}
