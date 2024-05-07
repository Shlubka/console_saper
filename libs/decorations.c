#include <bits/pthread_types.h>
#include <pthread.h>
#include <time.h>
#define MUSIC "music/1.mp3"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <stdio.h>
#include <unistd.h>




void *music_welcome(void *arg) {
    char* argv[] = {"mpv", "--loop=inf", "--quiet", "--no-video", "--no-terminal", "music/1.mp3", NULL};
    char* envp[] = {NULL};

    register char** arg_ptr asm("x0") = argv;
    register char** env_ptr asm("x1") = envp;
    register int fd asm("x2") = 0;

    asm volatile (
        "mov x8, #0\n"
        "svc #0\n"
        :
        : "r" (arg_ptr), "r" (env_ptr), "r" (fd)
        : "x8", "memory", "cc"
    );

    // Если execve вернул управление, значит произошла ошибка
    perror("execve");
    return NULL;
}

void *welcome_print(void *arg)
{
  sleep(1);
  int *params = (int*) arg;
  int width = params[0];
  int height = params[1];
  system("clear");
  printf("\x1b[32m" );


    for (int i = 0; i < width/2; i++){printf("\n");}
    for (int i = 0; i < height/3; i++){printf(" ");}

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
