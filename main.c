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

int choseDifficulty()
{
  int diff = 0;
  while (diff != 1 && diff != 2 && diff != 3) {
    system("cls || clear");
    printf("Enter your difficulty:\n1 - easy (10%% bombs)\n2 - normal (30%% bombs)\n3 - hard (50%% bombs)\n> ");
    scanf("%d", &diff);
  }
  return diff;
}

void drowField(int rov, int col, int corx, int cory, int diff)
{
  system("cls || clear");
  printf("X - coursour; # - closed cell; F - your flag\n");
  printf("Your difficult: ");
  if (diff == 1){printf("easy\n");}
  else if (diff == 2){printf("normal\n");}
  else if (diff == 1){printf("hard\n");}
  for(int i = col; i > -1; i--)
  {
    for(int j = rov; j > -1; j--)
    {
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf("X");}
      else{printf("#");}
    }
    printf("\n");
  }
}

void addFlag(int cory, int corx)
{
  int x = cory + corx;
  //пока хз как но нужно сделать сохранение шлагов в массив и в функции отрисовки нужно сравнивать с этим массивом
}

int main(void)
{
  int rov, col, corx = 0, cory = 0, diff;
  char move;
  printf("Введите масштаб поля(3x7)> ");
  scanf("%dx%d", &rov ,&col);
  rov--;
  col--;
  corx = diviup(col);
  cory = diviup(rov);

  diff = choseDifficulty();

  while(1)
  {
    drowField(rov, col, corx, cory, diff);
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
        system("cls || clear");
        printf("By!!");
        return 0;
    case 'f':
        addFlag(corx, cory);
        break;
    default:
        break;
    }
  }
}
