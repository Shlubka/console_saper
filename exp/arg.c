#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void printd(int num_args, ...) {
    va_list args;
    va_start(args, num_args);

    int max_length = 0;
    for (int i = 0; i < num_args; i++) {
        const char *arg = va_arg(args, const char *);
        int arg_length = strlen(arg);
        if (arg_length > max_length) {
            max_length = arg_length;
        }
    }

    va_end(args);

    va_start(args, num_args);
    printf("╔═");
    for (int i = 0; i < max_length; i++) {
        printf("══");
    }
    printf("╗\n");

    for (int i = 0; i < num_args; i++) {
        printf("║ ");
        const char *arg = va_arg(args, const char *);
        printf("Argument %d: %-*s", i + 1, max_length, arg);
        printf(" ║\n");
        fflush(stdout);
    }

    va_end(args);

    printf("╚═");
    for (int j = 0; j < max_length; j++) {
        printf("══");
    }
    printf("╝\n");
}

int main() {
    printd(3, "Hello", "World", "Chatbot");

    return 0;
}
