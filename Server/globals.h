#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "tokens.h"

// Std's includes
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

// Socket includes
#include <sys/socket.h>
#include <netinet/in.h>

#include "leak_detector_c.h"
#include "dict.h"

// Port in which the server will be hosted on
#define PORT 8080

#define BUFFER_SIZE 1024
#define DELAY		0.1

// Global vars
static int server_fd;
static struct sockaddr_in address;
static int opt = 1;

// Clients data
static char* clients_file = "clients.txt";
static Dict* clients_list = NULL;

static void load_clients_info()
{
	FILE* file;
	if (clients_list == NULL)
		clients_list = dict_new();
	else
	{
		dict_free(clients_list);
		clients_list = dict_new();
	}

	file = fopen(clients_file, "r");
	if (file == NULL) 
	{
		fprintf(stderr, "Failed to read file!\n");
		return;
	}

	char buffer[201];
	while (fgets(buffer, 201, file) != NULL)
	{
		char* username = strtok(buffer, " ");
		char* password = strtok(NULL, " ");
		password = strtok(password, "\n");
		dict_append(clients_list, username, password);
	}
	fclose(file);
}

void save_clients_info()
{
	FILE* file;
	file = fopen(clients_file, "w");
	if (file == NULL)
	{
		fprintf(stderr, "Failed to read file!\n");
		return;
	}

	char* keys[clients_list->len];
	dict_get_keys(clients_list, keys);

	for (int i = 0; i < clients_list->len; i++)
	{
		char* val = dict_get(clients_list, keys[i]);
		fputs(keys[i], file);
		fputs(" ", file);
		fputs(val, file);
		fputs("\n", file);
	}
	fclose(file);
}

#endif
