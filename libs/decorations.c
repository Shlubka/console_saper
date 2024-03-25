#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void welcome(int *width, int *height)
{
  //system("clear");
  //printf("%d, %d", *width, *height);
  //printf("Welcome to my game\n");
  printf("\x1b[32m" );

    for (int i = 0; i < *width/2; i++){printf("\n");}
    for (int i = 0; i < *height/2; i++){printf(" ");}

  if (*height <= 75)
  {
    printf("Welcome to my game\n""\x1b[0m");
    sleep(5);
    system("clear");
    //printf("\n");

  }
  else
  {
    printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗                       \n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝                       \n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗                         \n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝                         \n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗                       \n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝                       \n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("████████╗ ██████╗     ███╗   ███╗██╗   ██╗     ██████╗  █████╗ ███╗   ███╗███████╗██╗\n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("╚══██╔══╝██╔═══██╗    ████╗ ████║╚██╗ ██╔╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝██║\n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("   ██║   ██║   ██║    ██╔████╔██║ ╚████╔╝     ██║  ███╗███████║██╔████╔██║█████╗  ██║\n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("   ██║   ██║   ██║    ██║╚██╔╝██║  ╚██╔╝      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ╚═╝\n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("   ██║   ╚██████╔╝    ██║ ╚═╝ ██║   ██║       ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗██╗\n");
    for (int i = 0; i < *height/2; i++){printf(" ");}
    printf("   ╚═╝    ╚═════╝     ╚═╝     ╚═╝   ╚═╝        ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚═╝\n""\x1b[0m");
    sleep(5);
    system("clear");
  }
}
