#ifndef _DICT_H_
#define _DICT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"
#include <stdbool.h>

typedef struct dict_entry
{
	char* key;
	char* val;
} dict_entry;

typedef struct Dict
{
	dict_entry* entries;
	int len;
} Dict;


Dict* dict_new();
void dict_free(Dict* dict);
void dict_append(Dict* dict, char* key, char* val);
char* dict_get(Dict* dict, char* key);
void dict_get_keys(Dict* dict, char** out);
bool dict_exists(Dict* dict, char* key);

#endif
