#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>


// обозначение светов
#define Reset "\x1b[0m"
#define ColRed "\x1b[31m"
#define ColGre "\x1b[32m"

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

int doureal();
void enableRawMode();
int choseDifficulty();
void drowField(struct FlagCoords** fc, struct BombCoords** bc, int rov, int col, int corx, int cory, int diff, int num);
void addFlag(struct FlagCoords** bc, int cory, int corx);
int genCode(struct BombCoords** bc, int diff, int rov, int col);
char* cellCheck(struct FlagCoords* fc, struct BombCoords* bc, int xi, int yj);



int main(void)
{
  int dor;
  srand(time(NULL));
  struct BombCoords *bombCoords = NULL;
  struct FlagCoords *flagCoords = NULL;
  int rov, col, corx = 0, cory = 0, diff, c;
  char move;
  printf("Введите масштаб поля(3x7)> ");
  scanf("%dx%d", &rov ,&col);
  /*col = col - 1;
  rov = rov - 1;*/

  diff = choseDifficulty();
  int num = genCode(&bombCoords, diff, rov, col);

  enableRawMode();
  while(1)
  {
  drowField(&flagCoords, &bombCoords, rov, col, corx, cory, diff, num);
    scanf("\n%c", &move);

    switch(move) //Определение следующего хода 
    {
    case 'w':
        corx--;
        if (corx < 0){corx = col-1;}
        break;
    case 's':
        corx++;
        if (corx > col - 1){corx= 0;}
        break;
    case 'a':
        cory--;
        if (cory < 0){cory = rov-1;}
        break;
    case 'd':
        cory++;
        if (cory > rov - 1){cory= 0;}
        break;
    case 'e':
        system("clear");
        dor = doureal(); 
        printf("By!!");
        return 0;
    case 'q':
        system("clear");
        dor = doureal();
        printf("By!!");
        return 0;
    case 'f':
        addFlag(&flagCoords, corx, cory);
        break; default:
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

void drowField(struct FlagCoords** fc, struct BombCoords** bc, int rov, int col, int corx, int cory, int diff, int num)
{
  system("clear");
  printf("X - coursour; ? - closed cell; F - your flag; # - free open cell\n");
  printf("Your difficult: ");
  if (diff == 1){printf("easy\n");}
  else if (diff == 2){printf("normal\n");}
  else if (diff == 3){printf("hard\n");}
  printf("\n╔");
  for(int i = 0; i < rov; i++){printf("═");}
  printf("╗\n");
  for(int j = 0; j < col; j++)
  {
    printf("║");
    for(int i = 0; i < rov; i++)
    {
      char* sum = cellCheck(*fc, *bc, i, j);
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf(ColGre "X" Reset);}
      else{printf("%s", sum);}
    }

    printf("║\n");
  }
  printf("╚");
  for (int j = 0; j < rov; j++){printf("═");}
  printf("╝\n");
  printf("%d, %d, %d, %d, %d", corx, cory, rov, col, num);

}

void addFlag(struct FlagCoords** fc, int cory, int corx)
{
  struct FlagCoords* new_flag = (struct FlagCoords*)malloc(sizeof(struct FlagCoords));
  new_flag->x = corx;
  new_flag->y = cory;
  new_flag->next = *fc;
  *fc = new_flag;
}

int genCode(struct BombCoords** bc, int diff, int rov, int col) {
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
    return numBombs;
}


char* cellCheck(struct FlagCoords* fc, struct BombCoords* bc, int xi, int yj)
{
  struct BombCoords* current_b = bc;
  struct FlagCoords* current_f = fc;
  while (current_b != NULL)
  {
    if (current_b->x == xi && current_b->y == yj)
    {
      //printf("@");
      return ColRed "@" Reset;
    }
    current_b = current_b -> next;
  }
  while (current_f != NULL)
  {
    if (current_f->x == xi && current_f->y == yj)
    {
      return "F";
    }
    current_f = current_f->next;
  }
  return "?";
}

int doureal() {

    char yn[4];

    while (1) {
        printf("Do you really want to quit the game? (No(1)/yes(2)): ");
        scanf("%3s", yn);

        if (strcmp(yn, "no") == 0 || strcmp(yn, "1") == 0 || strcmp(yn, "No") == 0 || strcmp(yn, "1") == 0) {
            return 1; // Возвращаем 1
        }

        if (strcmp(yn, "yes") == 0 || strcmp(yn, "2") == 0 || strcmp(yn, "Yes") == 0) {
            return 2;
        }

        printf("Please enter a valid response.\n\n");
    }
    enableRawMode();
}

void enableRawMode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
