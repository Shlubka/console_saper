#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#define MAX_SCORES 10
#define MAX_NAME_LEN 50

void print_leaderboard() {
    FILE *file;
    char line[100];

    file = fopen("scores.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    // Read and print lines from the file
    while (fgets(line, sizeof(line), file) != NULL) {
      if(strcmp(line, "\n") == 0){continue;}
        printf("%s", line);
    }

    fclose(file);
}

void enableRawMode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void term_size(int *height, int *width)//функция для посчета доины размеров терминала
{
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  *height = size.ws_row; // высота
  *width = size.ws_col; // ширина
}

void indent(int *width, int *height, int *x, int *y, int col, int row)
{
   *x = (*width - (row * 2) - 3)/2;
   *y = (*height - col - 5)/2;
}


void clc__console__(int *dbf)
{
  disableRawMode();
  char command[10];
  printf("\n{clc} Enter command $ ");
  scanf("%s", command);

  if (strcmp(command, "drowb") == 0)
  {
    *dbf = 1;
  }
  if (strcmp(command, "ndrowb") == 0)
  {
    *dbf = 0;
  }
  if (strcmp(command, "lead") == 0)
  {
  system("clear");
  print_leaderboard();
  scanf("%s", command);
  }

  system("clear");
  enableRawMode();
}
