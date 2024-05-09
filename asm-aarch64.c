#include <stdio.h>
#include <unistd.h>

int main() {
    char* command = "mpv --loop=inf --quiet --no-video --no-terminal 1.mp3";

    register long x0 asm("x0") = (long)command;

    asm volatile (
        "bl system\n"
        :
        : "r" (x0)
        : "memory", "cc"
    );

    return 0;
}

