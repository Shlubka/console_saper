#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *print_numbers(void *arg) {
    for (int i = 0;; i++) {
        printf("\033[5;0H"); // Переместить курсор на пятое положение в строке
        printf("%d\n", i);
        sleep(3);
    }
    return NULL;
}

void *user_input(void *arg) {
    int num;
    //printf("\033[3;0H"); // Переместить курсор на третье положение в строке
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("\033[4;0H"); // Переместить курсор на четвертое положение в строке
    printf("Number entered: %d\n", num);
    sleep(3); // Добавим задержку перед завершением потока
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, print_numbers, NULL);
    pthread_create(&t2, NULL, user_input, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
