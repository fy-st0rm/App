#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long int generate_key(int val);
void encrypt(long int key, char* input, char* output, int len);
void decrypt(long int key, char* input, char* output, int len);

#endif
