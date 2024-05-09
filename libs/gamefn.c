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



/*enum Difficulty {
    CUSTOM = 0,
    EASY = 1,
    NORMAL = 2,
    HARD = 3,
    VERY_HARD = 4,
    IMPOSSIBLE = 5,
};*/

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
        //new_cell->cell = ColNum"2"Reset;
        break;
      case 3:
        WORK_FIELD[x][y] = '3';
        //new_cell->cell = ColNum"3"Reset;
        break;
      case 4:
        WORK_FIELD[x][y] = '4';
        //new_cell->cell = ColNum"4"Reset;
        break;
      case 5:
        WORK_FIELD[x][y] = '5';
        //new_cell->cell = ColNum"5"Reset;
        break;
      case 6:
        WORK_FIELD[x][y] = '6';
        //new_cell->cell = ColNum"6"Reset;
        break;
      case 7:
        WORK_FIELD[x][y] = '7';
        //new_cell->cell = ColNum"7"Reset;
        break;
      case 8:
        WORK_FIELD[x][y] = '8';
        //new_cell->cell = ColNum"8"Reset;
        break;
      case 0:
        WORK_FIELD[x][y] = '#';
        //new_cell->cell = "#";
        break;
      default:
        WORK_FIELD[x][y] = '*';
        //new_cell->cell = "*";
        break;
    } 
    //new_cell->next = *oc;
    //*oc = new_cell;
}


void open_cell(/*struct BombCoords** bc, struct OpenCells** oc*/char **START_GAME_FIELD, char **WORK_FIELD, int cory, int corx, int col, int row) {
  int tempx, tempy;
  //struct BombCoords* current_b = *bc;
  int found = 0; // Флаг для указания на наличие элемента

  for (int j = 0; j < col; j++) {
    tempy = cory + j;
    for (int i = 0; i < row; i++) {
      tempx = corx + i;

        //while (current_b != NULL) {
          //if (current_b->x == tempx && current_b->y == tempy) {
          if (START_GAME_FIELD[tempx][tempy] == 1)
          {
            found = 1;
            break; // Нашли элемент, прерываем цикл
          }
          //current_b = current_b->next;
        }

        if (found) {
          break; // Прерываем внешний цикл
        }

        //create_new_open_cell(bc, oc, tempx, tempy);
        //current_b = *bc; // Возвращаем указатель обратно в начало списка
    }
  //}

   for (int j = 0; tempy > 0; j++) {
    tempy = cory - j;
    for (int i = 0; tempx > 0; i++) {
      tempx = corx + i;

        //while (current_b != NULL) {
          //if (current_b->x == tempx && current_b->y == tempy) {
          if (START_GAME_FIELD[tempx][tempy] == 1)
          {
            found = 1;
            break; // Нашли элемент, прерываем цикл
          }
          //current_b = current_b->next;
        }

        if (found) {
          break; // Прерываем внешний цикл
        }

        //create_new_open_cell(bc, oc, tempx, tempy);
        //current_b = *bc; // Возвращаем указатель обратно в начало списка
    }
}



char* cellCheck(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int xi, int yj)
{
  if (START_GAME_FIELD[xi][yj] == 1)
  {
    return ColRed"@"Reset;
  }

  if (WORK_FIELD[xi][yj] == 1)
  {
    return &WORK_FIELD[xi][yj];
  }

  if (FLAG_FIELD[xi][yj] == 1)
  {
    return "F";
  }

  return "?";

  for (int i = 0;;){}

}

/*int choseDifficulty()
{
  int diff = 9; //НЕ МЕНЯТЬ БЛЯЬ\ТЬ!!!!!!!!!!!!!1
  //int diff = 0;
  //while (diff != CUSTOM && diff != EASY && diff != NORMAL && diff != HARD && diff != VERY_HARD && diff != IMPOSSIBLE)
  while (diff != 0 && diff != 1 && diff != 2 && diff != 3 && diff != 4 && diff != 5)
  {
    system("clear");
    printf("Enter your difficulty:\n0 - custom (enter your percent)\n1 - easy (10%% bombs)\n2 - normal (30%% bombs)\n3 - hard (50%% bombs)\n4 - very hard (70%% bombs)\n5 - IMPOSSIBLE (90%% bombs)\n> ");
  printf("ok");
    scanf("%d", &diff);
  }
  return diff;
}*/


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

//void drowField(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int row, int col, int corx, int cory, int diff, int *x, int *y)
//{
//  printf("\033[0;0H");
//  printf("X - coursour; ? - closed cell; F - your flag; # - free open cell\n");
//  printf("Your difficult: ");
//  if (diff == 1){printf("easy\n");}
//  else if (diff == 2){printf("normal\n");}
//  else if (diff == 3){printf("hard\n");}
//  /else if (diff == 4){printf("very hard\n");}
  //else if (diff == 5){printf("IMPOSSIBLE\n");}
//  else if (diff == 0){printf("custom\n");}
  /*for (int n = 0; n < *y; n++)
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
    printf("║ ");
    for(int i = 0; i < row; i++)
    {
      char* sum = cellCheck(START_GAME_FIELD,WORK_FIELD, FLAG_FIELD, i, j);
      //if координата открыта и рядом нет бомб, то нарисовать ·
      if(i == cory && j == corx){printf(ColCors "X " Reset);}
      else{printf("%s ", sum);}
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
  fflush(stdout); // очищаем буфер вывода после каждой операции вывода**/
  //printf("%d, %d, %d, %d, %d\n", corx, cory, row, col, num);
  //printf("command: 1 - tern up music; 2 - tern down music; q - quit the game; w, a, s, d - move coursour; any key - open cells; r - redrow");
//}

void addFlag(char **FLAG_FIELD, int cory, int corx)
{
  //struct FlagCoords* current_flag = *fc;
  //struct FlagCoords* prev_flag = NULL;

  //проверка, есть ли элемент в структуре, если есть, то удалить
  /*while (current_flag != NULL)
  {
    if (current_flag->x == corx && current_flag->y == cory)
    {
      if (prev_flag == NULL)
      {
        *fc = current_flag->next;
      }
      else
      {
        prev_flag->next = current_flag->next;
      }

      free(current_flag);
      return;
    }

    prev_flag = current_flag;
    current_flag = current_flag->next;
  }

  //добавление нового элемента
  struct FlagCoords* new_flag = (struct FlagCoords*)malloc(sizeof(struct FlagCoords));
  new_flag->x = corx;
  new_flag->y = cory;
  new_flag->next = *fc;
  *fc = new_flag;*/
  if (FLAG_FIELD[corx][cory] == 0)
  {
    FLAG_FIELD[corx][cory] = '1';
  }
  else FLAG_FIELD[corx][cory] = '0';

}

void genCode(char **START_GAME_FIELD, int diff, int row, int col) {
    /*row = row -1;
    col = col -1;*/
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
    numBombs = numBombs;
    //переделать в while
    int x = rand() % row;
    int y = rand() % col;
    int i = 0;
    for (int i = 0; i < numBombs; i++) {
        int x = rand() % row;
        int y = rand() % col;

        if (START_GAME_FIELD[x][y] == i)
        {
          i = i -1;
          continue;
        }
        else {START_GAME_FIELD[x][y] = i;}

}
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


