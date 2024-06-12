#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Из файла, в котором находятся несколько строк текста убрать все переносы на новую строку и оставить 1 рядок.

int main()
{
    FILE *file = fopen("./test.txt", "r");
    fseek(file, 0, SEEK_SET);
    char c;
    char line[1024];
    int n = 0;

    while ((c = fgetc(file)) != EOF)
    {
        if (c != '\n')
        {
            line[n] = c;
            n++;
        }
    }

    line[n] = '\0';
    fclose(file);

    FILE *file_write = fopen("./test.txt", "w");
    fprintf(file_write, "%s", line);

    fclose(file_write);
    return 0;
}