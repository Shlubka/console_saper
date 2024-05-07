#include <stdio.h>

int main() {
    int result;
    int a = 5;
    int b = 10;

    asm volatile(
        "add %w0, %w1, %w2\n"
        : "=r" (result)
        : "r" (a), "r" (b)
    );

    printf("Result: %d\n", result);
    
    return 0;
}
