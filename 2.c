#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Зміст першого файлу скопіювати в другий файл, перший файл залишити порожнім (видалити зміст).

int main()
{
    FILE *file1 = fopen("./file1.txt", "r");
    FILE *file2 = fopen("./file2.txt", "w");

    char line[1024];
    while ((fgets(line, 1024, file1)) != NULL)
    {
        fprintf(file2, "%s", line);
    }

    fclose(file1);
    fclose(file2);

    FILE *filer = fopen("./file1.txt", "w");
    fclose(filer);

    return 0;
}