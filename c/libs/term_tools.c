#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
//#include <string.h>

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
  //printf("%d, %d\n", size.ws_row, size.ws_col);
}

void indent(int *width, int *height, int *x, int *y, int col, int row)
{
   *x = (*width - (row * 2) - 3)/2;
   *y = (*height - col - 5)/2;
}


/*nt cli(int *fdb)
{
  //char msg; // increased the size to hold a meaningful string
  while (1) {
    printf("\n{cli} Enter command > ");
    scanf("%c", msg); // %255s to prevent buffer overflow
    if (msg, 'd' == 0) { // compare the input with "db"
      *fdb = 1;
    }
  }
  //free(&msg);
  return 0;
}*/

