#include "encrypt.h"


long int generate_key(int val)
{
	// Generating 5 digit random number
	if (!val)
		srand(time(NULL));

	long int lower = 1000000000;
	long int upper = 9999999999;
	long int number = (rand() % (upper - lower + 1)) + lower;
	return number;
}

void encrypt(long int key, char* input, char* output, int len)
{
	int final_key = 0;
	long int temp_key = key;
	
	for (int i = 0; i < 10; i++)
	{
		int last_dig = temp_key % 10;
		temp_key /= 10;
		final_key += last_dig;
	}

	for (int i = 0; i < len; i++)
	{
		output[i] = input[i] + final_key;
	}
	output[len] = '\0';
}

void decrypt(long int key, char* input, char* output, int len)
{
	int final_key = 0;
	long int temp_key = key;

	for (int i = 0; i < 10; i++)
	{
		int last_dig = temp_key % 10;
		temp_key /= 10;
		final_key += last_dig;
	}
	
	for (int i = 0; i < len; i++)
	{
		output[i] = input[i] - final_key;
	}
	output[len] = '\0';
}

