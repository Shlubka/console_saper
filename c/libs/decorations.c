//#include <bits/pthread_types.h>
#include <pthread.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *music_welcome(void *arg) {
  system("./asm-86");
    return NULL;
}

void *welcome_print(void *arg)
{
  int *params = (int*) arg;
  int width = params[0];
  int height = params[1];
  system("clear");
  printf("\x1b[32m" );

  int gg = (height-11)/2;
  int gg2 = (width -85)/2;
  printf("\033[%dB", gg);
  for (int i = 0; i < gg2; i++){printf(" ");}

  if (height <= 30)
  {

    //sleep(3);
    system("clear");
    int i = 0;
    gg2 = (width-18)/2;
    while (i < gg2) {
    printf(" ");
    i++;
    }
    printf("Welcome to my game\n""\x1b[0m");
    sleep(4);
    system("clear");

  }
  else
  {
    printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗                       \n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝                       \n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗                         \n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝                         \n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗                       \n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝                       \n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("████████╗ ██████╗     ███╗   ███╗██╗   ██╗     ██████╗  █████╗ ███╗   ███╗███████╗██╗\n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("╚══██╔══╝██╔═══██╗    ████╗ ████║╚██╗ ██╔╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝██║\n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("   ██║   ██║   ██║    ██╔████╔██║ ╚████╔╝     ██║  ███╗███████║██╔████╔██║█████╗  ██║\n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("   ██║   ██║   ██║    ██║╚██╔╝██║  ╚██╔╝      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ╚═╝\n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("   ██║   ╚██████╔╝    ██║ ╚═╝ ██║   ██║       ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗██╗\n");
    for (int i = 0; i < gg2; i++){printf(" ");}
    printf("   ╚═╝    ╚═════╝     ╚═╝     ╚═╝   ╚═╝        ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚═╝\n""\x1b[0m");
    sleep(5);
    system("clear");
  }
  return NULL;
}

void welcome(int *width, int *height){
  pthread_t t1, t2;
  int params[2] = {*width, *height};

  pthread_create(&t1, NULL, music_welcome, NULL);
  pthread_create(&t1, NULL, welcome_print, (void*)params);
  pthread_join(t1, NULL);
}
