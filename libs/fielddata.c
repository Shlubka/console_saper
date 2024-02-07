#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GenCode(int diff, struct bombbas *bb, int rov, int col)
{
  double dd = 0, resus;
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
  int bombscol = 0;
  srand(time(NULL));
  for(int i = 0; i < col; i++)
  {
    for(int i = 0; i < col; i++)
    {
      int r = rand() % 1;
      if (r == 1)
      {
        resus = bombscol / (rov*col);
        if (resus > dd)
        {
          //return bombbas;
          //return 1;
        }
      }
    }
  }
}

