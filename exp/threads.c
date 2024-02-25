#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *input_thread(void *arg) {
    char input[100];
    
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    
    // Удаляем символ новой строки из введенной строки
    input[strcspn(input, "\n")] = 0;
    
    printf("You entered: %s\n", input);

    pthread_exit(NULL); // Завершаем поток
}

void *timer_thread(void *arg) {
    int seconds = 0;
    
    while (1) {
        printf("Time elapsed: %d seconds\n", seconds);
        sleep(1);
        seconds++;
    }

    pthread_exit(NULL); // Завершаем поток
}

int main() {
    pthread_t input_tid, timer_tid;

    // Создаем поток для ввода строки
    if (pthread_create(&input_tid, NULL, input_thread, NULL) != 0) {
        fprintf(stderr, "Error creating input thread\n");
        return 1;
    }

    // Создаем поток для таймера
    if (pthread_create(&timer_tid, NULL, timer_thread, NULL) != 0) {
        fprintf(stderr, "Error creating timer thread\n");
        return 1;
    }

    // Ожидание завершения потоков
    pthread_join(input_tid, NULL);
    pthread_join(timer_tid, NULL);

    return 0;
}

