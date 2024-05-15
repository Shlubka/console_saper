#include <stdlib.h>

int main() {
    char cmd[] = "mpv 1.mp3";

    asm (
        "mov %0, %%rdi;"
        "call system;"
        : /* no output operands */
        : "m" (cmd) /* input operand */
        : "rdi" /* clobbered register */
    );

    return 0;
}

