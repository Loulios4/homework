#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// В первом файле есть число (и только число, ничего лишнего), во втором файле есть второе число.
// Задача: создать третий файл и записать туда результат суммы 2 чисел. (не 1 цифра, а 1 число - то есть может быть 2, 3, 4-значное итд).

int main()
{
    FILE *file1 = fopen("./file1.txt", "r");
    FILE *file2 = fopen("./file2.txt", "r");

    int x = 0;
    int y = 0;
    char c;

    while ((c = fgetc(file1)) != EOF)
    {
        x = x * 10 + (c - '0');
    }

    while ((c = fgetc(file2)) != EOF)
    {
        y = y * 10 + (c - '0');
    }

    fclose(file1);
    fclose(file2);

    FILE *file3 = fopen("./file3.txt", "w");
    fprintf(file3, "%d", (x + y));

    fclose(file3);

    return 0;
}