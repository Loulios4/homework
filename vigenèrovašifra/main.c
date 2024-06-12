#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "topsecret.h"

int main()
{
    char *encrypted;

    char *decrypted;

    encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");

    printf("%s\n", encrypted);

    decrypted = vigenere_decrypt("CoMPuTeR", "JSXAI PSINR!");

    printf("%s\n", decrypted);

    return 0;
}