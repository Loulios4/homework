#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char *vigenere_encrypt(const char *key, const char *text);

char *vigenere_decrypt(const char *key, const char *text);

unsigned char *bit_encrypt(const char *text);

char *bit_decrypt(const unsigned char *text);