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
#define ColQe "\x1b[36m"
//#define reset_curs printf("")

#define CUSTOM 0
#define EASY 1
#define NORMAL 2
#define HARD 3
#define VERY_HARD 4
#define IMPOSSIBLE 5

void dryFd(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int *y, int *x, int row, int col, int corx, int cory, int diff, int dbf, int *width);


void EndGame(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int *y, int *x, int row, int col, int corx, int cory, int diff, int *height, char* msg)
{
  system("clear");
  dryFd(START_GAME_FIELD, WORK_FIELD, FLAG_FIELD, y, x, row, col, corx, cory, diff, 1, height);
  printf("%s", msg);
  exit(0);
}


void open_cell(char **START_GAME_FIELD, char **WORK_FIELD, int cory, int corx, int col, int row, int bn, int *wincounter)
{
  int aw = 0;
  int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
  int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};

  if (cory < 0 || corx > col || corx < 0 || cory > row || START_GAME_FIELD[corx][cory] == '*')
  {
    return;
  }

//вправо вниз
  for (int tcrx = corx; tcrx < col; tcrx++)
  {
    for (int tcry = cory; tcry < row; tcry++)
    {
      int count = 0;
      if (START_GAME_FIELD[tcrx][tcry]=='*')
      {
        break;;
      }
      for (int i = 0; i < 8; i++)
      {
        int tx = tcrx + dx[i];
        int ty = tcry + dy[i];

        if (tx >= 0 && tx < col && ty >= 0 && ty < row && START_GAME_FIELD[tx][ty] == '*')
        {
          count++;
        }
      }
       if (WORK_FIELD[tcrx][tcry] == 9)
      {
        (*wincounter)++;
        WORK_FIELD[tcrx][tcry] = count;
      }
     if (tcrx+1 < col && START_GAME_FIELD[tcrx+1][cory] == '*'){aw = 1; break;}
    }
    if (aw){aw = 0; break;}
  }

//влево вниз
  for (int tcrx = corx; tcrx < col; tcrx++)
  {
    for (int tcry = cory; tcry > 0; tcry--)
    {
      int count = 0;
      if (START_GAME_FIELD[tcrx][tcry]=='*')
      {
        break;
      }
      for (int i = 0; i < 8; i++)
      {
        int tx = tcrx + dx[i];
        int ty = tcry + dy[i];

        if (tx >= 0 && tx < col && ty >= 0 && ty < row && START_GAME_FIELD[tx][ty] == '*')
        {
          count++;
        }
      }
      if (WORK_FIELD[tcrx][tcry] == 9)
      {
        (*wincounter)++;
        WORK_FIELD[tcrx][tcry] = count;
      }
      if (tcrx+1 < col && START_GAME_FIELD[tcrx+1][cory] == '*'){aw = 1; break;}
    }
    if (aw){aw = 0; break;}
  }

//вправо вверх
  for (int tcrx = corx; tcrx > 0; tcrx--)
  {
    for (int tcry = cory; tcry < row; tcry++)
    {
      int count = 0;
      if (START_GAME_FIELD[tcrx][tcry]=='*')
      {
        break;;
      }
      for (int i = 0; i < 8; i++)
      {
        int tx = tcrx + dx[i];
        int ty = tcry + dy[i];

        if (tx >= 0 && tx < col && ty >= 0 && ty < row && START_GAME_FIELD[tx][ty] == '*')
        {
          count++;
        }
      }
      if (WORK_FIELD[tcrx][tcry] == 9)
      {
        (*wincounter)++;
        WORK_FIELD[tcrx][tcry] = count;
      }
      if (tcrx+1 < col && START_GAME_FIELD[tcrx-1][tcry] == '*'){aw = 1; break;}////////////////
    }
    if (aw){aw = 0; break;}
  }

//влево вверх
  for (int tcrx = corx; tcrx > 0; tcrx--)
  {
    for (int tcry = cory; tcry > 0; tcry--)
    {
      int count = 0;
      if (START_GAME_FIELD[tcrx][tcry]=='*')
      {
        break;;
      }
      for (int i = 0; i < 8; i++)
      {
        int tx = tcrx + dx[i];
        int ty = tcry + dy[i];

        if (tx >= 0 && tx < col && ty >= 0 && ty < row && START_GAME_FIELD[tx][ty] == '*')
        {
          count++;
        }
      }
      if (WORK_FIELD[tcrx][tcry] == 9)
      {
        (*wincounter)++;
        WORK_FIELD[tcrx][tcry] = count;
      }
      if (tcrx+1 < col && START_GAME_FIELD[tcrx-1][tcry] == '*'){aw = 1; break;}/////////////////////
    }
    if (aw){aw = 0; break;}
  }

  if (bn <= *wincounter)
  {
    system("clear");
    printf("You've Won!!!!\nYour score: %d\n", *wincounter);
    system("cowsay POBEDAAA, horosh!!");
    //EndGame(START_GAME_FIELD, WORK_FIELD, FLAG_FIELD, int *y, int *x, int row, int col, int corx, int cory, int diff, int *height, char *msg);
    exit(0);
  }
}




int choseDifficulty()
{
  int diff = 9;
  while (diff != CUSTOM && diff != EASY && diff != NORMAL && diff != HARD && diff != VERY_HARD && diff != IMPOSSIBLE)
  {
    system("clear");
    printf("1 - easy (10%% bombs)\n2 - normal (30%% bombs)\n3 - hard (50%% bombs)\n~> ");
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

int genCode(char **START_GAME_FIELD, int diff, int row, int col, int corx, int cory)
{
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
  }

  numBombs = totalCells * threshold;

  for (int i = 0; i < numBombs; )
  {
    int x = (rand() % row);
    int y = (rand() % col);
    if (x < 0 || x >= row || y < 0 || y >= col)
    {
      continue;
    }
    else
    {
      if (START_GAME_FIELD[x][y] != '*' && x != corx && y != cory)
      {
        START_GAME_FIELD[x][y] = '*';
        i++;
      }
    }
  }
  return totalCells - numBombs;
}


int doureal ()
{
  char yn[4];
  while (1)
  {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
    printf("║ ");
    for(int i = 0; i < row; i++)
    {
      if(i == cory && j == corx){printf(ColCors "X " Reset);}
      else if (dbf == 1 && START_GAME_FIELD[j][i] == '*'){printf(ColRed"@ "Reset);}
      else if (WORK_FIELD[j][i] != 9){printf(ColNum "%d " Reset, WORK_FIELD[j][i]);}
      else if (FLAG_FIELD[i][j] == '1'){printf("F ");}
      else{printf(ColQe"? "Reset);}
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
  int fdsfdbv = *width-1;
  printf("\033[%d;1H", fdsfdbv);
  printf("command: 1 - tern up music; 2 - tern down music; q - quit the game; w, a, s, d - move coursour; any key - open cells; r - redrow");
}

