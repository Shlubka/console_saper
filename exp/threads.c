#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* root(){
  printf("hiiiiii\n");
  sleep(5);
  printf("kjhgf\n");
}

int main(){
  pthread_t t1, t2;

  pthread_create(&t1, NULL, &root, NULL);
  pthread_create(&t2, NULL, &root, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
