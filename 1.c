#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Підрахувати кількість строк в файлі.

int main()
{
    FILE *file = fopen("./test.txt", "r");

    char line[1024];
    int i = 0;
    while ((fgets(line, 1024, file)) != NULL)
    {
        i++;
    }
    printf("Line count: %d\n", i);

    fclose(file);

    return 0;
}