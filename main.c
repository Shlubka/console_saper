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
//void print_bombs_data(struct BombCoords* bc);
int bombCheck(struct BombCoords* bc, int xi, int yj);


int main(void)
{
  srand(time(NULL));
  struct BombCoords *bombCoords = NULL;
  int rov, col, corx = 0, cory = 0, diff, c;
  char move;
  printf("Введите масштаб поля(3x7)> ");
  scanf("%dx%d", &rov ,&col);
  corx = 0;
  cory = 0;

  diff = choseDifficulty();
  genCode(&bombCoords, diff, rov, col);
  //print_bombs_data(bombCoords);
  //scanf("%d", &c);

  while(1)
  {
  //  drowField(rov, col, corx, cory, diff);
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
      char pr = bombCheck(bombCoords, i, j);
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf("X");}
      else{printf("%c", pr);}
    }
    printf("\n");
  }
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

/*void drowField(int rov, int col, int corx, int cory, int diff)
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
      bombCheck(&bombCoords, i, j);
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf("X");}
      else{printf("#");}
    }
    printf("\n");
  }
}*/

void addFlag(int cory, int corx)
{
  int x = cory + corx;
  //пока хз как но нужно сделать сохранение шлагов в массив и в функции отрисовки нужно сравнивать с этим массивом
}

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

    for (int i = 0; i < rov; i++) {
        for (int j = 0; j < col; j++) {
            int r = rand() % 2;
            if (r == 1) {
                bombscol++;
                resus = (double)bombscol / (rov * col);
                if (resus < dd) {
                    struct BombCoords* new_bomb = (struct BombCoords*)malloc(sizeof(struct BombCoords));
                    if (new_bomb != NULL) {
                        new_bomb->x = i;
                        new_bomb->y = j;
                        new_bomb->next = *bb; // Link the new bomb to the beginning of the
                        *bb = new_bomb;
                    }
                }
            }
        }
    }
}

/*void print_bombs_data(struct BombCoords* bc)
{
  struct BombCoords* current = bc;
  while (current != NULL)
  {
    printf("x = %d, y = %d\n", current->x, current->y);
    current = current -> next;
  }
}*/

int bombCheck(struct BombCoords* bc, int xi, int yj)
{
  struct BombCoords* current = bc;
  while (current != NULL)
  {
    if (current->x == xi && current->y == yj)
    {
      //printf("@");
      return '@';
    }
    current = current -> next;
  }
  return '#';
}
