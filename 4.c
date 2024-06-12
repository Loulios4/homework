#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Определить, какая строка является самой длинной в заданном файле.

int main()
{
    FILE *file = fopen("./file1.txt", "r");

    int max = 0;
    char line[1024];
    int counterl = 0;
    char c;

    while ((fgets(line, 1024, file) != NULL))
    {
        counterl++;
    }

    fseek(file, 0, SEEK_SET);

    int counter = 0;
    int linec = 0;
    for (int i = 0; i < counterl; i++)
    {
        counter = 0;
        while ((c = fgetc(file)) != '\n' && c != EOF)
        {
            counter++;
        }
        if (counter > max)
        {
            max = counter;
            linec = i + 1;
        }
    }

    printf("%d\n", linec);

    fclose(file);
    return 0;
}