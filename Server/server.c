#include "globals.h"


int create_server();
void handle_client(int conn);
char* handle_login(int conn);

void send_status(int conn, int status);

int create_server()
{
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		fprintf(stderr, "Socket failed!\n");
		return -1;
	}
	
	// To reuse the address
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		fprintf(stderr, "Sockopt failed!\n");
		return -1;
	}

	// Creating address
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	// Binding
	if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0)
	{
		fprintf(stderr, "Failed to bind sv!\n");
		return -1;
	}
	return 0;
}

void send_status(int conn, int status)
{
	char msg[1];
	sprintf(msg, "%d", status);
	sleep(DELAY);
	send(conn, msg, sizeof(msg), 0);
}

char* handle_login(int conn)
{
	char buffer[BUFFER_SIZE] = {0};
	bool loop = true;
	while (loop)
	{
		int val;
		if ((val = read(conn, buffer, sizeof(buffer))) > 0)
		{
			char* token = strtok(buffer, " ");
			char* username = strtok(NULL, " ");
			char* password = strtok(NULL, " ");
			
			if (atoi(token) == LOGIN)		// When data is from login
			{
				if (dict_exists(clients_list, username))
					if (strcmp(dict_get(clients_list, username), password) == 0)
					{
						send_status(conn, PASS);
						loop = false;
						return username;
					}
				send_status(conn, FAIL);
			}
			else if (atoi(token) == SIGNUP)	// When data is from singup
			{
				if (!dict_exists(clients_list, username))
				{
					dict_append(clients_list, username, password);
					save_clients_info();
					
					send_status(conn, PASS);
					loop = false;
					return username;
				}
				send_status(conn, FAIL);
			}
			else if (atoi(token) == DISCONNECT)
				return "";
		}
	}
}

void handle_client(int conn)
{
	char buffer[BUFFER_SIZE] = {0};
	char* username = malloc(sizeof(char) * 100);
	strcpy(username, handle_login(conn));
	
	bool connected;	
	if (strlen(username) > 0)
	{
		connected = true;
		printf("Connected: %s\n", username);
	}
	
	// TODO: create a infinite lister to the client
	
	printf("Disconnected: %d\n", conn);
	close(conn);	
	//free(username);
}

int main(int argc, char** argv)
{
	if (create_server() < 0)
		return -1;
	
	// Loading clients data
	load_clients_info();

	printf("Server started...\n");
	
	pthread_t thread;
	int conn;
	int addrlen = sizeof(address);
	
	while (1)
	{
		// Listening for the clients
		listen(server_fd, 0);

		if ((conn = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0)
			fprintf(stderr, "Accept error!");
		int err = pthread_create(&thread, NULL, handle_client, conn);
		if (err)
			fprintf(stderr, "Error in threading!");
	}
	return 0;
}

