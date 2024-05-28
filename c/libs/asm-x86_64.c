#include <stdlib.h>

int main() {
    char* cmd = "mpv --loop=inf --quiet --no-video --no-terminal 1.mp3";
    int result;

    asm volatile (
        "mov %1, %%rdi\n\t" // Переместить адрес cmd в rdi (1-й аргумент для system)
        "call *%2\n\t"      // Вызвать функцию system
        "mov %%eax, %0"     // Сохранить результат (возвращаемое значение system) в result
        : "=r" (result)     // Операнд вывода
        : "r" (cmd), "r" (system) // Операнды ввода
        : "rdi", "rax"      // Модифицируемые регистры
    );

    if (result != 0) {
        return 1;
    }

    return 0;
}

