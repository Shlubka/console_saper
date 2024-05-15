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
#define ColNum "\x1b[33m"
//#define reset_curs printf("")

#define CUSTOM 0
#define EASY 1
#define NORMAL 2
#define HARD 3
#define VERY_HARD 4
#define IMPOSSIBLE 5




float thcust(){
  float th = 0;
  printf("Enter your custom persentage of bombs > ");
  scanf("%f", &th);
  th = th * 0.01;
  return th;
}


void create_new_open_cell(char **START_GAME_FIELD, char **WORK_FIELD, int x, int y) {

    int f_num = 0;
    int tempx, tempy;

    for (int i = -1; i <= 1; i++)
    {
        tempx = x + i;
        for (int j = -1; j <= 1; j++)
        {
            tempy = y + j;
            if (START_GAME_FIELD[tempy][tempy] == 1)
            {
              f_num += 1;
            }
        }
    }



    switch (f_num) {
      case 1:
        WORK_FIELD[x][y] = '1';
        break;
      case 2:
        WORK_FIELD[x][y] = '2';
        break;
      case 3:
        WORK_FIELD[x][y] = '3';
        break;
      case 4:
        WORK_FIELD[x][y] = '4';
        break;
      case 5:
        WORK_FIELD[x][y] = '5';
        break;
      case 6:
        WORK_FIELD[x][y] = '6';
        break;
      case 7:
        WORK_FIELD[x][y] = '7';
        break;
      case 8:
        WORK_FIELD[x][y] = '8';
        break;
      case 0:
        WORK_FIELD[x][y] = '#';
        break;
      default:
        WORK_FIELD[x][y] = '*';
        break;
    }
}


void open_cell(char **START_GAME_FIELD, char **WORK_FIELD, int cory, int corx, int col, int row) {
  int tempx, tempy;
  int found = 0; // Флаг для указания на наличие элемента

  for (int j = 0; j < col; j++) {
    tempy = cory + j;
    for (int i = 0; i < row; i++) {
      tempx = corx + i;

          if (START_GAME_FIELD[tempx][tempy] == 1)
          {
            found = 1;
            break; // Нашли элемент, прерываем цикл
          }
        }

        if (found) {
          break; // Прерываем внешний цикл
        }
    }

   for (int j = 0; tempy > 0; j++) {
    tempy = cory - j;
    for (int i = 0; tempx > 0; i++) {
      tempx = corx + i;
          if (START_GAME_FIELD[tempx][tempy] == 1)
          {
            found = 1;
            break; // Нашли элемент, прерываем цикл
          }
        }

        if (found) {
          break; // Прерываем внешний цикл
        }
    }
}


int choseDifficulty()
{
  int diff = 9;
  while (diff != CUSTOM && diff != EASY && diff != NORMAL && diff != HARD && diff != VERY_HARD && diff != IMPOSSIBLE)
  {
    system("clear");
    printf("Enter your difficulty:\n0 - custom (enter your percent)\n1 - easy (10%% bombs)\n2 - normal (30%% bombs)\n3 - hard (50%% bombs)\n4 - very hard (70%% bombs)\n5 - IMPOSSIBLE (90%% bombs)\n> ");
    scanf("%d", &diff);
  }
  return diff;
}


void addFlag(char **FLAG_FIELD, int cory, int corx)
{
  if (FLAG_FIELD[corx][cory] == 0)
  {
    FLAG_FIELD[corx][cory] = '1';
  }
  else FLAG_FIELD[corx][cory] = '0';

}

int genCode(char **START_GAME_FIELD, int diff, int row, int col) {
    if (START_GAME_FIELD == NULL) {
        return -1; // Return an error code
    }

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

    numBombs = totalCells * threshold;

    for (int i = 0; i < numBombs; ) {
        int x = rand() % row;
        int y = rand() % col;

        if (START_GAME_FIELD[x][y] != '*') {
            START_GAME_FIELD[x][y] = '*';
            i++;
        }
    }

    return numBombs;
}




int doureal ()
{
    char yn[4];
    //disableRawMode();
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
            return 1;
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


