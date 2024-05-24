#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>

// обозначение светов
#define Reset "\x1b[0m"//белый
#define ColRed "\x1b[31m"
#define ColCors "\x1b[32m"
#define ColNum "\x1b[33m"
//#define reset_curs printf("")

#define CUSTOM 0
#define EASY 1
#define NORMAL 2
#define HARD 3
#define VERY_HARD 4
#define IMPOSSIBLE 5

void dryFd(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int *y, int *x, int row, int col, int corx, int cory, int diff, int dbf, int *width);

float thcust()
{
  float th = 0;
  printf("Enter your custom persentage of bombs ~> ");
  scanf("%f", &th);
  th = th * 0.01;
  return th;
}

void loose(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int *y, int *x, int row, int col, int corx, int cory, int diff, int *height)
{
  system("clear");
  dryFd(START_GAME_FIELD, WORK_FIELD, FLAG_FIELD, y, x, row, col, corx, cory, diff, 1, height);
  printf(ColRed"\nGAME OVER\n" Reset);
  exit(0);
}

void open_cell(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int diff, int cory, int corx, int col, int row, int *height, int *x, int *y) {
  int count = 0;
  if (START_GAME_FIELD[corx][cory] == '*')
  {
    loose(START_GAME_FIELD, WORK_FIELD, FLAG_FIELD, y, x, row, col, corx, cory, diff, height);
    return;
  }

  for (int q = cory; q < row; q++)
  {
      for (int j = -1; j < 2; j++)
    {
    for (int i = -1; i < 2; i++)
      {
        if (START_GAME_FIELD[corx][q] == '*'){return;}
        else if (corx + i < col &&j + q < row && corx + i >= 0 && cory + j >= 0) //&& i != 0 && j != 0)
        {
          if (START_GAME_FIELD[corx + i][j + q] == '*'){count = count + 1;}
        }
      }
    }
  WORK_FIELD[corx][q] = count;
  count = 0;
  }
}

int choseDifficulty()
{
  int diff = 9;
  while (diff != CUSTOM && diff != EASY && diff != NORMAL && diff != HARD && diff != VERY_HARD && diff != IMPOSSIBLE)
  {
    system("clear");
    printf("Enter your difficulty:\n0 - custom (enter your percent)\n1 - easy (10%% bombs)\n2 - normal (30%% bombs)\n3 - hard (50%% bombs)\n4 - very hard (70%% bombs)\n5 - IMPOSSIBLE (90%% bombs)\n~> ");
    scanf("%d", &diff);
  }
  return diff;
}


void addFlag(char **FLAG_FIELD, int cory, int corx)
{
  if (FLAG_FIELD[corx][cory] != '1')
  {
    FLAG_FIELD[corx][cory] = '1';
  }
  else FLAG_FIELD[corx][cory] = '0';
}

void genCode(char **START_GAME_FIELD, int diff, int row, int col)
{
  int totalCells = row * col;
  int numBombs = 0;
  double threshold = 0.0;

  switch (diff) {
    case CUSTOM:
      threshold = thcust();
      break;
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

  //int tex = row - 1;
  //int tey = col - 1;
  //numBombs = totalCells * threshold;
  numBombs = totalCells * diff / 10;

  for (int i = 0; i < numBombs; )
  {
    int x = (rand() % row);
    int y = (rand() % col);
    //printf("%d, %d", x, y);
    if (x < 0 || x >= row || y < 0 || y >= col)
    {
      continue;
    }
    else
    {
      if (START_GAME_FIELD[x][y] != '*')
      {
        START_GAME_FIELD[x][y] = '*';
        i++;
      }
    }
  }
}


int doureal ()
{
  char yn[4];
  //disableRawMode();
  while (1)
  {
    printf("Do you really want to quit the game? (no/yes): ");
    scanf("%3s", yn);

    if (strcmp(yn, "no") == 0 || strcmp(yn, "No") == 0) 
    {
      return 1;
    }

    if (strcmp(yn, "yes") == 0 || strcmp(yn, "Yes") == 0)
    {
      return 2;
    }

    printf("Please enter a valid response.\n\n");
  }
}

int confirmInput(int width, int height, const char* message, int defaultWidth, int defaultHeight)
{
  char ok[10];
  while (1)
  {
    printf("%s", message);
    getchar();  // Clear newline character from previous input
    if (fgets(ok, sizeof ok, stdin) == NULL || strcmp(ok, "\n") == 0)
    {
      return 1;
    }
    else if (strcasecmp(ok, "yes\n") == 0 || strcasecmp(ok, "y\n") == 0 || strcasecmp(ok, "1\n") == 0)
    {
      return 1;
    }
    else if (strcasecmp(ok, "no\n") == 0 || strcasecmp(ok, "n\n") == 0 || strcasecmp(ok, "2\n") == 0)
    {
      return 0;
    }
    else
    {
      printf("Invalid input. Please enter 'yes' or 'no'.\n");
    }
  }
  return 0;
}



void dryFd(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int *y, int *x, int row, int col, int corx, int cory, int diff, int dbf, int *width)
{
  printf("\033[0;0H");
  printf("X - coursour; ? - closed cell; F - your flag; # - free open cell\n");
  printf("Your difficult: ");
  if (diff == 1){printf("easy\n");}
  else if (diff == 2){printf("normal\n");}
  else if (diff == 3){printf("hard\n");}
  else if (diff == 4){printf("very hard\n");}
  else if (diff == 5){printf("IMPOSSIBLE\n");}
  else if (diff == 0){printf("custom\n");}
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
   //printf("drow");
    printf("║ ");
    for(int i = 0; i < row; i++)
    {
      if(i == cory && j == corx){printf(ColCors "X " Reset);}
      else if (dbf == 1 && START_GAME_FIELD[j][i] == '*'){printf(ColRed"@ "Reset);}
      else if (WORK_FIELD[j][i] != 9){printf("%d ", WORK_FIELD[j][i]);}
      else if (FLAG_FIELD[i][j] == '1'){printf("F ");}
      else{printf("? ");}
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
  //printf("%d, %d, %d, %d, %d\n", corx, cory, row, col, num);
  int fdsfdbv = *width-1;
  printf("\033[%d;1H", fdsfdbv);
  printf("command: 1 - tern up music; 2 - tern down music; q - quit the game; w, a, s, d - move coursour; any key - open cells; r - redrow");
}

