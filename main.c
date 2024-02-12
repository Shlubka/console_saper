#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "libs/fielddata.c"

enum Difficulty {
    EASY = 1,
    NORMAL = 2,
    HARD = 3
};

struct BombCoords
{
  int x;
  int y;
  struct BombCoords* next;
};

struct FlagCoords
{
  int x;
  int y;
  struct FlagCoords* next;
};

int choseDifficulty();
void drowField(struct FlagCoords** fc, struct BombCoords** bc, int rov, int col, int corx, int cory, int diff);
void addFlag(struct FlagCoords** bc, int cory, int corx);
void genCode(struct BombCoords** bc, int diff, int rov, int col);
char cellCheck(struct FlagCoords* fc, struct BombCoords* bc, int xi, int yj);


int main(void)
{
  srand(time(NULL));
  struct BombCoords *bombCoords = NULL;
  struct FlagCoords *flagCoords = NULL;
  int rov, col, corx = 0, cory = 0, diff, c;
  char move;
  printf("Введите масштаб поля(3x7)> ");
  scanf("%dx%d", &rov ,&col);
  corx = 0;
  cory = 0;

  diff = choseDifficulty();
  genCode(&bombCoords, diff, rov, col);

  while(1)
  {
  drowField(&flagCoords, &bombCoords, rov, col, corx, cory, diff);
  /*system("cls || clear");
  printf("X - coursour; # - closed cell; F - your flag\n");
  printf("Your difficult: ");
  if (diff == 1){printf("easy\n\n");}
  else if (diff == 2){printf("normal\n\n");}
  else if (diff == 3){printf("hard\n\n");}
  for(int i = 0; i < col; i++)
  {
    for(int j = 0; j < rov; j++)
    {
      char pr = cellCheck(bombCoords, i, j);
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf("X");}
      else{printf("%c", pr);}
    }
    printf("\n");
  }*/
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
    case 'q':
        system("cls || clear");
        printf("By!!");
        return 0;
    case 'f':
        addFlag(&flagCoords, corx, cory);
        break;
    default:
        break;
    }
  }
}

int choseDifficulty()
{
  int diff = 0;
  while (diff != EASY && diff != NORMAL && diff != HARD) 
  {
    system("cls || clear");
    printf("Enter your difficulty:\n1 - easy (10%% bombs)\n2 - normal (30%% bombs)\n3 - hard (50%% bombs)\n> ");
    scanf("%d", &diff);
  }
  return diff;
}

void drowField(struct FlagCoords** fc, struct BombCoords** bc, int rov, int col, int corx, int cory, int diff)
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
      char sum = cellCheck(*fc, *bc, i, j);
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf("X");}
      else{printf("%c", sum);}
    }
    printf("\n");
  }
}

void addFlag(struct FlagCoords** fc, int cory, int corx)
{
  struct FlagCoords* new_flag = (struct FlagCoords*)malloc(sizeof(struct FlagCoords));
  new_flag->x = corx;
  new_flag->y = cory;
  new_flag->next = *fc;
  *fc = new_flag;
}

void genCode(struct BombCoords** bc, int diff, int rov, int col) {
    int totalCells = rov * col;
    int numBombs = 0;
    double threshold = 0.0;

    switch (diff) {
        case EASY:
            threshold = 0.1;
            break;
        case NORMAL:
            threshold = 0.3;
            break;
        case HARD:
            threshold = 0.5;
            break;
    }

    numBombs = totalCells * threshold;

    for (int i = 0; i < numBombs; i++) {
        int x = rand() % rov;
        int y = rand() % col;

        struct BombCoords* new_bomb = (struct BombCoords*)malloc(sizeof(struct BombCoords));
        if (new_bomb != NULL) {
            new_bomb->x = x;
            new_bomb->y = y;
            new_bomb->next = *bc;
            *bc = new_bomb;
        }
    }
}


char cellCheck(struct FlagCoords* fc, struct BombCoords* bc, int xi, int yj)
{
  struct BombCoords* current_b = bc;
  struct FlagCoords* current_f = fc;
  while (current_b != NULL)
  {
    if (current_b->x == xi && current_b->y == yj)
    {
      //printf("@");
      return '@';
    }
    current_b = current_b -> next;
  }
  while (current_f != NULL)
  {
    if (current_f->x == xi && current_f->y == yj)
    {
      return 'F';
    }
    current_f = current_f->next;
  }
  return '?';
}

