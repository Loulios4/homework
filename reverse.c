#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Reverse

char *reverse(const char *text)
{
    if (text == NULL)
    {
        return NULL;
    }

    int text_len = strlen(text);
    char *reversed = calloc(text_len, sizeof(char));

    for (int i = 0; i < text_len; i++)
    {
        reversed[i] = toupper(text[text_len - i - 1]);
    }

    return reversed;
}

int main()
{
    char *reversed = reverse("Hello world!");
    printf("%s\n", reversed);

    return 0;
}