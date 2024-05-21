#include <stdio.h>
#include <string.h>

int main() {
    char command[] = "ponysay spasibo za igrwwwwuuuuuuuu!!!!" ;
    asm (
        "movq $0, %%rax\n\t" // syscall number for system() in x86_64 Linux
        "movq %1, %%rdi\n\t"
        "syscall\n\t"
        :
        : "r" (command), "m" (*command)
        : "%rax", "%rdi", "memory"
    );
    return 0;
}

