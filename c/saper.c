#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "libs/term_tools.h"
#include "libs/decorations.c"
#include "libs/gamefn.h"

// обозначение светов
#define Reset "\x1b[0m"//белый
#define ColRed "\x1b[31m"
#define ColCors "\x1b[32m"
#define ColNum "\x1b[33m"
#define ColAnn "\x1b[36m"
//#define reset_curs printf("")



int main(int argc, char *argv[])
{
  //int seed = time(NULL);
  srand(time(NULL));
  int row, col, corx = 0, cory = 0, diff, x = 0, y = 0, width, height, dor, dbf = 0, gcf = 1, bn, wincounter = 0;
  char move;
  term_size(&height, &width);
  indent(&width, &height, &x, &y, col, row);
  //welcome(&width, &height);

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-db") == 0) {dbf = 1;}
    if (strcmp(argv[i], "-d") == 0)
    {
      row = 30;
      col = 30;
      diff = 2;

      goto deffolt_parametrs;
    }
  }

  printf("Enter the field dimensions (format: 30x30) ~> ");
  scanf("%dx%d", &row ,&col);
  /*printf("Enter num of rows ~> ");
  scanf("%d", &col);
  printf("Enter num of col ~> ");
  scanf("%d", &row);*/
  if (row > height || col > width)
  {
    if (confirmInput(width, height, "The size of your field is larger than the size of the terminal. Are you sure? (Yes/no) ~> ", width / 4, height / 2) == 0)
    {
        row = height / 4;
        col = width / 4;
    }
  } else if (row < 30 && col < 30)
  {
    if (confirmInput(width, height, "The size of your field is less than 30x30. Are you sure? (Yes/no) > ", 30, 30) == 0)
    {
        row = 30;
        col = 30;
    }
  }

  diff = choseDifficulty();
  //allocation memmory to fields
deffolt_parametrs: diff = diff;
  char **START_GAME_FIELD = (char **)malloc(col * sizeof(char *));
  for (int i = 0; i < col; i++)
  {
    START_GAME_FIELD[i] = (char *)malloc(row * sizeof(char));
  }

  for (int i = 0; i < col; i++)
  {
    for (int j = 0; j < row; j++)
    {
      START_GAME_FIELD[i][j] = '9';
    }
  }

  char **WORK_FIELD = (char **)malloc(col * sizeof(char *));
  for (int i = 0; i < col; i++)
  {
    WORK_FIELD[i] = (char *)malloc(row * sizeof(char));
  }
  char **FLAG_FIELD = (char **)malloc(row * sizeof(char *));
  for (int i = 0; i < row; i++)
  {
    FLAG_FIELD[i] = (char *)malloc(col * sizeof(char));
  }

  for (int i = 0; i < col; i++)
  {
    for (int j = 0; j < row; j++)
    {
      START_GAME_FIELD[i][j] = 9;
      WORK_FIELD[i][j] = 9;
      FLAG_FIELD[j][i] = 9;
    }
  }

  enableRawMode();
  system("clear");

  while(1)
  {
    indent(&width, &height, &x, &y, col, row);
    dryFd(START_GAME_FIELD, WORK_FIELD, FLAG_FIELD, &y, &x, row, col, corx, cory, diff, dbf, &height);

    scanf("%c", &move);
    switch(move)
    {
    case 'w':
    case 'k':
        corx--;
        if (corx < 0){corx = col-1;}
        break;
    case 's':
    case 'j':
        corx++;
        if (corx > col - 1){corx= 0;}
        break;
    case 'a':
    case 'h':
        cory--;
        if (cory < 0){cory = row-1;}
        break;
    case 'd':
    case 'l':
        cory++;
        if (cory > row - 1){cory= 0;}
        break;
    case 'r':
        system("clear");
        term_size(&height, &width);
        break;
    case 'q':
        system("clear");
        disableRawMode();
        dor = doureal();
        if (dor == 2)
        {
          printf("%d\n", dor);
          //printf("\033[0;0H");
          system("killall mpv; clear; cowsay spasiba za igru!!");
          printf("\n");
          return 0;
        }
        else if (dor == 1)
        {
          enableRawMode();
          break;
        }
        break;
    case 'f':
        addFlag(FLAG_FIELD, corx, cory);
        break;
    case '`':
        //printf("\npisun\n");
        clc__console__(&dbf);
        break;
    case '0':
      system("mpv --loop=inf --quiet --no-video --no-terminal libs/0.mp3");
      break;
    case '2':
      system("killall mpv;clear");
      break;
    case 'c':
    case 'n':
      if (gcf){bn = genCode(START_GAME_FIELD, diff, col, row, corx, cory); gcf =0;}
      if (START_GAME_FIELD[corx][cory] == '*')
      {
        EndGame(START_GAME_FIELD, WORK_FIELD, FLAG_FIELD, &y, &x, row, col, corx, cory, diff, &height, ColRed"\nGAME OVER\n" Reset);
        return 0;
      }
      disableRawMode();
      open_cell(START_GAME_FIELD, WORK_FIELD, cory, corx, col, row, bn, &wincounter, diff);
      enableRawMode();
      break;
  }
}
  system("killall mpv");
}

