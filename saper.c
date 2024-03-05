#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "libs/term_tools.h"
#include "libs/decorations.c"
#include "libs/gamefn.h"

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
  char cell;
  struct OpenCells* next;
};


//void clear_term(int *height);


int main(void)
{
  int dor;
  srand(time(NULL));
  struct BombCoords *bombCoords = NULL;
  struct FlagCoords *flagCoords = NULL;
  int row, col, corx = 0, cory = 0, diff, x, y, width, height;
  char move;
  term_size(&height, &width);
  indent(&width, &height, &x, &y, col, row);
  welcome(&y, &x);
  //clear_term(&x);
  printf("Enter the field dimensions (format: 30x30) > ");
  scanf("%dx%d", &row ,&col);
  if (row > height || col > width) 
  {
    if (confirmInput(width, height, "The size of your field is larger than the size of the terminal. Are you sure? (Yes/no) > ", width / 4, height / 2) == 0) 
    {
        // Reset row and col to default values
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
  /*col = col - 1;
  row = row - 1;*/

  diff = choseDifficulty();
  int num = genCode(&bombCoords, diff, row, col);

  enableRawMode();
  system("clear");
  while(1)
  {
    indent(&width, &height, &x, &y, col, row);
    //clear_term(&x);
    drowField(&flagCoords, &bombCoords, row, col, corx, cory, diff, num, &x, &y);
    //printf("%d, %d;  %d, %d", width, height, row, col);
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
        dor = doureal();
        if (dor == 2)
        {
          printf("%d\n", dor);
          return 0;
        }
        else if (dor == 1)
        {
          enableRawMode();
          break;
        }
    case 'f':
        addFlag(&flagCoords, corx, cory);
        break;
    default:
        system("clear");
        printf("Incorect input\n");
        sleep(1);
        break;
    }
  }
}

