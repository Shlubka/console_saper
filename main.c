#include <stdio.h>
#include <stdlib.h>

int diviup(int num) //Нахер импортировать, когда можно выебнуться и написать свое?))))
{
  int res;
  if (num % 2 == 0)
  {
    res = ((num - 1)/2)+1;
  }
  else{res = num/2;}

  return res;
}

void drowField(int rov, int col, int corx, int cory)
{
  system("cls || clear");
  for(int i = col; i > -1; i--)
  {
    for(int j = rov; j > -1; j--)
    {
      if(i == cory && j == corx){printf("X");}
      else{printf("#");}
    }
    printf("\n");
  }
}

int main(void)
{
  int rov, col, corx = 0, cory = 0;
  char move;
  printf("Введите масштаб поля(3x7)> ");
  scanf("%dx%d", &rov ,&col);
  rov--;
  col--;
  corx = diviup(col);
  cory = diviup(rov);

  while(1)
  {
    drowField(rov, col, corx, cory);
    scanf("\n%c", &move);

    switch(move) //Определение следующего хода
    { 
    case 'w':
        cory++;
        break;
    case 'a':
        corx++;
        break;
    case 's':
        cory--;
        break;
    case 'd':
        corx--;
        break;
    case 'e':
        return 0;
    default:
        break;
    }
  }
}
