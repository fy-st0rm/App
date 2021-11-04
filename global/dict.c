#include "dict.h"
#include <stdbool.h>

Dict* dict_new()
{
	Dict* dict = malloc(sizeof(Dict));
	dict->len = 0;
	return dict;
}

void dict_free(Dict* dict)
{
	free(dict->entries);
	free(dict);
}

void dict_append(Dict* dict, char* key, char* val)
{
	dict_entry* new_entry;
	if (dict->len == 0)
		new_entry = malloc(sizeof(dict_entry));
	else
	{
		new_entry = malloc(sizeof(dict_entry) * (dict->len + 1));
		for (int i = 0; i < dict->len; i++)
		{
			new_entry[i].key = dict->entries[i].key;
			new_entry[i].val = dict->entries[i].val;
		}
	}
	
	// Adding new element	
	new_entry[dict->len].key = malloc(sizeof(char) * strlen(key));
	new_entry[dict->len].val = malloc(sizeof(char) * strlen(val));
	
	strcpy(new_entry[dict->len].key, key);
	strcpy(new_entry[dict->len].val, val);

	free(dict->entries);
	dict->entries = new_entry;

	dict->len++;
}

char* dict_get(Dict* dict, char* key)
{
	for (int i = 0; i < dict->len; i++)
	{
		char* dict_key = dict->entries[i].key;
		if (strcmp(dict_key, key) == 0)
			return dict->entries[i].val;
	}
	return NULL;
}

void dict_get_keys(Dict* dict, char** out)
{
	for (int i = 0; i < dict->len; i++)
	{
		out[i] = dict->entries[i].key;
	}
}

bool dict_exists(Dict* dict, char* key)
{
	for (int i = 0; i < dict->len; i++)
	{
		if (strcmp(dict->entries[i].key, key) == 0)
			return true;
	}
	return false;
}
