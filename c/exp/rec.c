#include <stdio.h>

int main()
{
  char BOMB[5][5];
  BOMB[2][4] = '*';
  BOMB[1][0] ='*';
  BOMB[3][2] ='*';
  BOMB[1][2] ='*';
  BOMB[4][3] ='*';
  BOMB[1][4] ='*';
  BOMB[4][4] ='*';
  BOMB[3][4] ='*';
  BOMB[2][1] ='*';

  for(int i = 0; i<5;i++)
  {
    for(int j=0;j<5;j++)
    {
      if (BOMB[i][j] == '*')
      {
      printf("%c ", BOMB[i][j]);
      }
      else printf("# ");
    }
    printf("\n");
  }
}
