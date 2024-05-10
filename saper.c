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


void dryFd(int *y, int *x, int row, int col, int corx, int cory, int diff)
{
  /*int diff = 0;
  //printf("enter funck");
  printf("\033[0;0H");
  printf("X - coursour; ? - closed cell; F - your flag; # - free open cell\n");
  printf("Your difficult: ");
  if (diff == 1){printf("easy\n");}
  else if (diff == 2){printf("normal\n");}
  else if (diff == 3){printf("hard\n");}
  else if (diff == 4){printf("very hard\n");}
  else if (diff == 5){printf("IMPOSSIBLE\n");}
  else if (diff == 0){printf("custom\n");}

  for (int n = 0;n < *y; n++){printf("\n");}
  for (int n = 0;n < *x; n++){printf(" ");}
  printf("╔═");
  for(int i = 0; i < row; i++){printf("══");}
  printf("╗\n");


  for (int j = 0; j < col; j++){
    for (int i = 0; i < *x; i++){
      printf(" ");
    }
    printf("║ ");

    for (int k = 0; k < row; k++)
    {
      if(i == cory && j == corx){printf(ColCors "X " Reset);}
      //else{printf("%s ", sum);}
      printf("  ");
    }

    printf("║\n");
  }


  for (int n = 0; n < *x; n++)
  {
    printf(" ");
  }
  printf("╚═");
  for (int j = 0; j < row; j++){printf("══");}
  printf("╝\n");*/

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
      //char* sum = cellCheck(START_GAME_FIELD,WORK_FIELD, FLAG_FIELD, i, j);
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf(ColCors "X " Reset);}
      else{printf("  ");}
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
  printf("command: 1 - tern up music; 2 - tern down music; q - quit the game; w, a, s, d - move coursour; any key - open cells; r - redrow");

}


int main(void)
{
  srand(time(NULL));
  int row, col, corx = 0, cory = 0, diff, x, y, width, height, dor;
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
  //allocation memmory to fields

  diff = genCode(START_GAME_FIELD, diff, row, col); //ok

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
    dryFd(&y, &x, row, col, corx, cory, diff);
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
    case '`':
        printf("pisun");
        //sleep(2);
        //cli_command();
        break;
    case '1':
      system("mpv --loop=inf --quiet --no-video --no-terminal libs/1.mp3");
      break;
    case '2':
      system("killall mpv;clear");
      break;
    default:
        //open_cell(&bombCoords, &opencells, corx, cory, col, row);
        //openCell(opencells, bombCoords, cory, corx);
        //system("clear");
        //printf("Incorect input\n");
        //sleep(1);
        break;
  }
}
  system("killall mpv");
}



