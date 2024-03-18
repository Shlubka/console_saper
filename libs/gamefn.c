#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

// обозначение светов
#define Reset "\x1b[0m"//белый
#define ColRed "\x1b[31m"
#define ColCors "\x1b[32m"
//#define reset_curs printf("")


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
  //char cell;
  struct FlagCoords* next;
};
struct OpenCells
{
  int x;
  int y;
  char* cell;
  struct OpenCells* next;
};
enum Difficulty {
    EASY = 1,
    NORMAL = 2,
    HARD = 3,
    VERY_HARD = 4,
    IMPOSSIBLE = 5,
};

char* cellCheck(struct BombCoords* bc, struct FlagCoords* fc, struct OpenCells* oc, int xi, int yj)
{
  struct OpenCells* current_c = oc;
  struct FlagCoords* current_f = fc;
  while (current_c != NULL)
  {
    if (current_c->x == xi && current_c->y == yj)
    {
      //printf("@");
      //тут мнесто @ нужно вернуть содержимое яйчейки
      return current_c->cell;
    }
    current_c = current_c -> next;
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

void openCell(struct OpenCells* oc, struct BombCoords* bc, int cory, int corx)
{
  struct BombCoords* current_b = bc;
  struct OpenCells* current_c = oc;
  while (current_b != NULL)
  {
    if (current_b->x == corx && current_b->y == cory)
    {
      // Вместо печати сообщения можно вызвать функцию обработки проигрыша
      printf("You are losing this game\n");
      sleep(100);
      // Дополнительные действия при проигрыше
      return; // выход из функции
    }
    current_b = current_b->next;
  }
  while (current_c != NULL)
  {
    if (current_c->x == corx && current_c->y == cory)
    {
      // Вместо печати сообщения можно вызвать функцию обработки проигрыша
      printf("You are losing this game\n");
      // Дополнительные действия при проигрыше
      return; // выход из функции
    }
    current_b = current_b->next;
  }
}



int choseDifficulty()
{
  int diff = 0;
  while (diff != EASY && diff != NORMAL && diff != HARD)
  {
    system("clear");
    printf("Enter your difficulty:\n0 - custom (enter your percent)\n1 - easy (10%% bombs)\n2 - normal (30%% bombs)\n3 - hard (50%% bombs)\n4 - very hard (70%% bombs)\n5 - IMPOSSIBLE (90%% bombs)> ");
    scanf("%d", &diff);
  }
  return diff;
}

void drowField(struct FlagCoords** fc, struct OpenCells** oc, int row, int col, int corx, int cory, int diff, int num, int *x, int *y)
{
  printf("\033[0;0H");
  printf("X - coursour; ? - closed cell; F - your flag; # - free open cell\n");
  printf("Your difficult: ");
  if (diff == 1){printf("easy\n");}
  else if (diff == 2){printf("normal\n");}
  else if (diff == 3){printf("hard\n");}
  for (int n = 0; n < *y; n++)
  {
    printf("\n");
  }
  for (int n = 0; n < *x; n++)
  {
    printf(" ");
  }
  printf("╔═");
  for(int i = 0; i < row; i++){printf("══");}
  printf("╗\n");
  for(int j = 0; j < col; j++)
  {
    for (int n = 0; n < *x; n++)
    {
      printf(" ");
    }
    printf("║ ");
    for(int i = 0; i < row; i++)
    {
      char* sum = cellCheck(*fc, *oc, i, j);
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf(ColCors "X " Reset);}
      else{printf("%s ", sum);}
      fflush(stdout); // очищаем буфер вывода после каждой операции вывода
    }

    printf("║\n");
    fflush(stdout); // очищаем буфер вывода после каждой операции вывода
  }
  for (int n = 0; n < *x; n++)
  {
    printf(" ");
  }
  printf("╚═");
  for (int j = 0; j < row; j++){printf("══");}
  printf("╝\n");
  fflush(stdout); // очищаем буфер вывода после каждой операции вывода
  //printf("%d, %d, %d, %d, %d", corx, cory, row, col, num);
}

void addFlag(struct FlagCoords** fc, int cory, int corx)
{
  struct FlagCoords* current_flag = *fc;
  struct FlagCoords* prev_flag = NULL;

  //проверка, есть ли элемент в структуре, если есть, то удалить
  while (current_flag != NULL)
  {
    if (current_flag->x == corx && current_flag->y == cory)
    {
      if (prev_flag == NULL)
      {
        *fc = current_flag->next;
      }
      else
      {
        prev_flag->next = current_flag->next;
      }

      free(current_flag);
      return;
    }

    prev_flag = current_flag;
    current_flag = current_flag->next;
  }

  //добавление нового элемента
  struct FlagCoords* new_flag = (struct FlagCoords*)malloc(sizeof(struct FlagCoords));
  new_flag->x = corx;
  new_flag->y = cory;
  new_flag->next = *fc;
  *fc = new_flag;
}

int genCode(struct BombCoords** bc, int diff, int row, int col) {
    int totalCells = row * col;
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
        case VERY_HARD:
            threshold = 0.7;
            break;
        case IMPOSSIBLE:
            threshold = 0.9;
            break;
    }

    numBombs = totalCells * threshold;

    for (int i = 0; i < numBombs; i++) {
        int x = rand() % row;
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


int doureal ()
{
    char yn[4];
    disableRawMode();
    while (1) {
        printf("Do you really want to quit the game? (no/yes): ");
        scanf("%3s", yn);

        if (strcmp(yn, "no") == 0 || strcmp(yn, "No") == 0) {
            return 1;
        }

        if (strcmp(yn, "yes") == 0 || strcmp(yn, "Yes") == 0) {
            return 2;
        }

        printf("Please enter a valid response.\n\n");
    }
}

int confirmInput(int width, int height, const char* message, int defaultWidth, int defaultHeight) {
    char ok[10];
    while (1) {
        printf("%s", message);
        getchar();  // Clear newline character from previous input
        if (fgets(ok, sizeof ok, stdin) == NULL || strcmp(ok, "\n") == 0) {
            break;
        } else if (strcasecmp(ok, "yes\n") == 0 || strcasecmp(ok, "y\n") == 0 || strcasecmp(ok, "1\n") == 0) {
            return 1;
        } else if (strcasecmp(ok, "no\n") == 0 || strcasecmp(ok, "n\n") == 0 || strcasecmp(ok, "2\n") == 0) {
            return 0;
        } else {
            printf("Invalid input. Please enter 'yes' or 'no'.\n");
        }
    }
    return 0;
}
