#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для генерации белого шума
double whiteNoise()
{
    return ((double)rand() / RAND_MAX) * 2 - 1; // Генерируем случайное число в диапазоне [-1, 1]
}

int main()
{
    // Устанавливаем seed для генератора случайных чисел
    srand(time(NULL));

    // Генерируем и выводим 10 значений белого шума
    for (int i = 0; i < 10; i++){
      for (int j = 0; j < 10; j++)
    {
        //printf("%f\n", whiteNoise());
    printf("\u25A0");
    }printf("\n");}
}

