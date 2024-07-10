#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <math.h>
#include <stdbool.h>
#include "hof.h"
#include <string.h>

int load(struct player list[])
{
    FILE *file;
    file = fopen(HOF_FILE, "r");

    if (file == NULL)
    {
        file = fopen(HOF_FILE, "w");
        if (file == NULL)
        {
            return -1;
        }

        fclose(file);

        return 0;
    }

    int ch;
    int count = 0;
    while (count < 10)
    {
        int name_index = 0;

        while ((ch = fgetc(file)) != EOF && ch != DELIMITER[0] && name_index < 29 && ch != '\n')
        {
            list[count].name[name_index++] = (char)ch;
        }
        list[count].name[name_index] = '\0';

        int score = 0;
        while ((ch = fgetc(file)) != '\n' && ch != EOF)
        {
            if (ch >= '0' && ch <= '9')
            {
                score = score * 10 + (ch - '0');
            }
        }
        list[count].score = score;

        if (name_index > 0)
        {
            count++;
        }

        if (ch == EOF)
        {
            break;
        }
    }

    fclose(file);
    return count;
}

bool save(const struct player list[], const int size)
{
    FILE *file;
    file = fopen(HOF_FILE, "w");

    if (file == NULL)
    {
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s", list[i].name);
        fprintf(file, "%s", DELIMITER);
        fprintf(file, "%d\n", list[i].score);
    }

    fclose(file);
    return 1;
}

bool add_player(struct player list[], int *size, const struct player player)
{
    bool swap;

    if (*size < 10)
    {
        strncpy(list[*size].name, player.name, 29);

        list[*size].score = player.score;

        for (int i = 0; i < *size; i++)
        {
            swap = false;
            for (int j = 0; j < *size - i; j++)
            {
                if (list[j].score < list[j + 1].score)
                {
                    int tmp_s = list[j].score;
                    list[j].score = list[j + 1].score;
                    list[j + 1].score = tmp_s;

                    char tmp_n[30];
                    strncpy(tmp_n, list[j].name, 29);

                    strncpy(list[j].name, list[j + 1].name, 29);

                    strncpy(list[j + 1].name, tmp_n, 29);

                    swap = true;
                }
            }

            if (!swap)
                break;
        }
        (*size)++;
        return 1;
    }
    else
    {
        for (int i = 0; i < *size - 1; i++)
        {
            swap = false;
            for (int j = 0; j < *size - 1 - i; j++)
            {
                if (list[j].score < list[j + 1].score)
                {
                    int tmp_s = list[j].score;
                    list[j].score = list[j + 1].score;
                    list[j + 1].score = tmp_s;

                    char tmp_n[30];
                    strncpy(tmp_n, list[j].name, 29);

                    strncpy(list[j].name, list[j + 1].name, 29);

                    strncpy(list[j + 1].name, tmp_n, 29);

                    swap = true;
                }
            }

            if (!swap)
                break;
        }

        if (player.score >= list[9].score)
        {
            strncpy(list[9].name, player.name, 29);

            list[9].score = player.score;

            for (int i = 0; i < *size - 1; i++)
            {
                swap = false;
                for (int j = 0; j < *size - 1 - i; j++)
                {
                    if (list[j].score < list[j + 1].score)
                    {
                        int tmp_s = list[j].score;
                        list[j].score = list[j + 1].score;
                        list[j + 1].score = tmp_s;

                        char tmp_n[30];
                        strncpy(tmp_n, list[j].name, 29);

                        strncpy(list[j].name, list[j + 1].name, 29);

                        strncpy(list[j + 1].name, tmp_n, 29);

                        swap = true;
                    }
                }

                if (!swap)
                    break;
            }
            return 1;
        }
        else
            return 0;
    }

    return 0;
}