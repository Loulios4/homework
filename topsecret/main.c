#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "topsecret.h"
#include <math.h>

int main()
{
    char *encrypted;

    char *decrypted;

    encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");

    printf("%s\n", encrypted);
    free(encrypted);

    decrypted = vigenere_decrypt("CoMPuTeR", "JSXAI PSINR!");

    printf("%s\n", decrypted);
    free(decrypted);

    unsigned char *encrypted2;

    encrypted2 = bit_encrypt("Hello world!");
    for (int i = 0; i < 12; i++)
    {
        printf("%x ", encrypted2[i]);
    }
    printf("\n");

    unsigned char *decrypted2;

    decrypted2 = (unsigned char *)bit_decrypt(encrypted2);

    printf("Decrypted text: %s\n", decrypted2);

    free(decrypted2);
    free(encrypted2);

    return 0;
}