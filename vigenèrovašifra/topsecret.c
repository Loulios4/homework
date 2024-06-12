#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "topsecret.h"

// Vigenèrova šifra

char *vigenere_encrypt(const char *key, const char *text)
{

    int text_len = strlen(text);
    int key_len = strlen(key);

    char *upper_key = calloc(text_len, sizeof(char));
    char *upper_text = calloc(text_len, sizeof(char));

    for (int i = 0; key[i] != '\0'; i++)
    {
        upper_key[i] = toupper(key[i]);
    }

    for (int i = 0; text[i] != '\0'; i++)
    {
        upper_text[i] = toupper(text[i]);
    }

    char *encrypted = calloc(text_len, sizeof(char));

    for (int i = 0, j = 0; i < text_len; i++)
    {
        if (upper_text[i] < 65 || upper_text[i] > 90)
        {
            encrypted[i] = upper_text[i];
        }
        else
        {
            encrypted[i] = ((upper_text[i] - 'A') + (upper_key[j % key_len] - 'A')) % 26 + 'A';
            j++;
        }
    }

    encrypted[text_len] = '\0';

    free(upper_key);
    free(upper_text);
    return encrypted;
}

char *vigenere_decrypt(const char *key, const char *text)
{
    int text_len = strlen(text);
    int key_len = strlen(key);

    char *decrypted = calloc(text_len, sizeof(char));
    char *upper_key = calloc(text_len, sizeof(char));

    for (int i = 0; key[i] != '\0'; i++)
    {
        upper_key[i] = toupper(key[i]);
    }

    for (int i = 0, j = 0; i < text_len; i++)
    {
        if (text[i] < 65 || text[i] > 90)
        {
            decrypted[i] = text[i];
        }
        else
        {
            decrypted[i] = ((text[i] - 'A') - (upper_key[j % key_len] - 'A') + 26) % 26 + 'A';
            j++;
        }
    }

    free(upper_key);
    return decrypted;
}
