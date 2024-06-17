#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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

unsigned char *bit_encrypt(const char *text)
{
    int text_len = strlen(text);
    unsigned char *result = calloc(text_len + 1, sizeof(char));
    int i = 0;
    for (i = 0; i < text_len; i++)
    {
        int bits[8];
        int charDec = (int)text[i];

        for (int j = 0; j < 8; j++)
        {
            bits[j] = 0;
            if (charDec - pow(2, 7 - j) >= 0)
            {
                charDec -= pow(2, 7 - j);
                bits[j] = 1;
            }
        }

        for (int j = 0; j < 4; j += 2)
        {
            int tmp = bits[j + 1];
            bits[j + 1] = bits[j];
            bits[j] = tmp;
        }

        for (int j = 4; j < 8; j++)
        {
            if (bits[j] != bits[j - 4])
            {
                bits[j] = 1;
            }
            else
            {
                bits[j] = 0;
            }
        }

        charDec = 0;
        for (int j = 0; j < 8; j++)
        {
            if (bits[j])
            {
                charDec += pow(2, 7 - j);
            }
        }
        result[i] = (char)charDec;
    }

    result[i + 1] = '\0';

    return result;
}

char *bit_decrypt(const unsigned char *text)
{
    int text_len = 0;

    while (text[text_len] != '\0')
    {
        text_len++;
    }

    char *result = calloc(text_len + 1, sizeof(char));

    int i = 0;
    for (i = 0; i < text_len; i++)
    {
        int bits[8];
        int charEnc = (int)text[i];

        for (int j = 0; j < 8; j++)
        {
            bits[j] = 0;
            if (charEnc - pow(2, 7 - j) >= 0)
            {
                charEnc -= pow(2, 7 - j);
                bits[j] = 1;
            }
        }

        for (int j = 4; j < 8; j++)
        {
            if (bits[j] != bits[j - 4])
            {
                bits[j] = 1;
            }
            else
            {
                bits[j] = 0;
            }
        }

        for (int j = 0; j < 4; j += 2)
        {
            int tmp = bits[j + 1];
            bits[j + 1] = bits[j];
            bits[j] = tmp;
        }

        for (int j = 0; j < 8; j++)
        {
            if (bits[j])
            {
                charEnc += pow(2, 7 - j);
            }
        }
        result[i] = (char)charEnc;
    }
    result[i + 1] = '\0';
    return result;
}
