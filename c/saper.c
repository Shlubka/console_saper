#include <stdio.h>
#include <stdlib.h>
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
//#define reset_curs printf("")


void genbombs(){}

int main()
{
  srand(time(NULL));
  int row, col, corx = 0, cory = 0, diff, x, y, width, height, dor, fdb;
  char move;
  term_size(&height, &width);
  indent(&width, &height, &x, &y, col, row);
  //welcome(&width, &height);
  printf("Enter the field dimensions (format: 30x30) > ");
  scanf("%dx%d", &row ,&col);
  if (row > height || col > width)
  {
    if (confirmInput(width, height, "The size of your field is larger than the size of the terminal. Are you sure? (Yes/no) > ", width / 4, height / 2) == 0) 
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
  char **START_GAME_FIELD = (char **)malloc(x * sizeof(char *));
  for (int i = 0; i < x; i++)
  {
    START_GAME_FIELD[i] = (char *)malloc(y * sizeof(char));
  }
  char **WORK_FIELD = (char **)malloc(x * sizeof(char *));
  for (int i = 0; i < x; i++)
  {
    WORK_FIELD[i] = (char *)malloc(y * sizeof(char));
  }
  char **FLAG_FIELD = (char **)malloc(x * sizeof(char *));
  for (int i = 0; i < x; i++)
  {
    FLAG_FIELD[i] = (char *)malloc(y * sizeof(char));
  }

  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      START_GAME_FIELD[i][j] = 9;
      WORK_FIELD[i][j] = 9;
      FLAG_FIELD[i][j] = 9;
    }
  }

  //нужно заполнить массив, посмотреть, что будет
  //пока предположу, что система чистит выделенное местo
  //allocation memmory to fields

  //diff = genCode(START_GAME_FIELD, diff, row, col);
  //genCode(START_GAME_FIELD, diff, col, row);
  genCode(START_GAME_FIELD, diff, row, col);
  printf("ok");

  //#############################################
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      printf("%c ", START_GAME_FIELD[i][j]);
    }
  }


  /*for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      printf("%c ", FLAG_FIELD[i][j]);
    }
  }*/

  //#############################################
  //system("clear");
  enableRawMode();
  system("clear");
  //printf("ok");
  //sleep(1); //этого нельзя
  while(1)
  {
    //dryFd();
    //printf("ok");;
    indent(&width, &height, &x, &y, col, row);
    //drowField(START_GAME_FIELD, WORK_FIELD, FLAG_FIELD, row, col, corx, cory, diff, &x, &y);
    dryFd(START_GAME_FIELD, WORK_FIELD, FLAG_FIELD, &y, &x, row, col, corx, cory, diff);
    scanf("\n%c", &move);

    switch(move)
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
        if (cory < 0){cory = row-1;}
        break;
    case 'd':
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
          system("killall mpv; clear");
          printf("spasiba za igru!!\n");
          return 0;
        }
        else if (dor == 1)
        {
          enableRawMode();
          break;
        }
    case 'f':
        addFlag(FLAG_FIELD, corx, cory);
        break;
    //case '`':
        //printf("\npisun\n");
        //sleep(2);
        //break;
    case '1':
      system("mpv --loop=inf --quiet --no-video --no-terminal libs/1.mp3");
      break;
    case '2':
      system("killall mpv;clear");
      break;
    default:
        open_cell(START_GAME_FIELD, WORK_FIELD, cory, corx, col, row);
        break;
  }
}
  system("killall mpv");
}

