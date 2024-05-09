#include <bits/pthread_types.h>
#include <pthread.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *music_welcome(void *arg) {
    char* command = "mpv --loop=inf --quiet --no-video --no-terminal 1.mp3";

    register long x0 asm("x0") = (long)command;

    asm volatile (
        "bl system\n"
        :
        : "r" (x0)
        : "memory", "cc"
    );
  //system("./asm");

    return NULL;
}

void *welcome_print(void *arg)
{
  //sleep(1);
  int *params = (int*) arg;
  int width = params[0];
  int height = params[1];
  system("clear");
  printf("\x1b[32m" );

  //printf("%d, %d", width, height);
  //sleep(5);

    //for (int i = 0; i < height/4; i++){printf("\n");}
    printf("\033[%dB", height/2);
    for (int i = 0; i < width/3; i++){printf(" ");}

  if (height <= 50)
  {
    sleep(3);
    system("clear");
    printf("Welcome to my game\n""\x1b[0m");
    sleep(2);
    system("clear");

  }
  else
  {
    printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗                       \n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝                       \n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗                         \n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝                         \n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗                       \n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝                       \n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("████████╗ ██████╗     ███╗   ███╗██╗   ██╗     ██████╗  █████╗ ███╗   ███╗███████╗██╗\n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("╚══██╔══╝██╔═══██╗    ████╗ ████║╚██╗ ██╔╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝██║\n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("   ██║   ██║   ██║    ██╔████╔██║ ╚████╔╝     ██║  ███╗███████║██╔████╔██║█████╗  ██║\n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("   ██║   ██║   ██║    ██║╚██╔╝██║  ╚██╔╝      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ╚═╝\n");
    for (int i = 0; i < height/3; i++){printf(" ");}
    printf("   ██║   ╚██████╔╝    ██║ ╚═╝ ██║   ██║       ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗██╗\n");
    for (int i = 0; i < height/3; i++){printf(" ");}
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
  //welcome_print(width, height);
  //pthread_create(&t2, NULL, welcome_print, NULL)t
  pthread_join(t1, NULL);
  //pthread_join(t2, NULL);
}
