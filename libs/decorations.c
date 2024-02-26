#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void welcome(int *width, int *height)
{
  system("clear");
  //printf("%d, %d", *width, *height);
  for (int i = 0; i < *width; i++){printf("\n");}
  for (int i = 0; i < *height/2; i++){printf(" ");}
  printf("Welcome to my game\n");
  sleep(3);
  system("clear");
}
