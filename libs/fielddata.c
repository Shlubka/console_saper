#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GenCode(int diff, struct bombbas*** bb, int rov, int col)
{
  double dd = 0;
  int bombscol = 0;
  double resus = bombscol / (rov*col);
  switch (diff) 
  {
    case 1:
      dd = 0.1;
      break;
    case 2:
      dd = 0.3;
      break;
    case 3:
      dd = 0.5;
      break;
  }
  srand(time(NULL));
  for(int i = 0; i < col; i++)
  {
    for(int j = 0; j < col; j++)
    {
      int r = rand() % 2;
      if (r == 1)
      {
        if (resus > dd)
        {
          struct 
          //добавление координат новой бомбы
        }
      }
    }
  }
}

