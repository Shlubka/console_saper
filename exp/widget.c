#include <stdio.h>
#include <string.h>

void drawWidget(int x, int y, int width, int height, const char* text) {
    for (int i = 0; i < y; i++) {
        printf("\n");
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < x; j++) {
            printf(" ");
        }
        printf("|");
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("|\n");
    }

    for (int i = 0; i < x; i++) {
        printf(" ");
    }
    printf("|%s", text);
    for (int i = 0; i < width - 2 - strlen(text); i++) {
        printf(" ");
    }
    printf("|\n");

    for (int i = 0; i < x; i++) {
        printf(" ");
    }
    for (int j = 0; j < width; j++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    drawWidget(5, 5, 30, 10, "Пример виджета");

    return 0;
}
