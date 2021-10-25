// Std's includes
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

// Socket includes
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

// Global vars
static int server_fd;
static struct sockaddr_in address;
static int opt = 1;


int create_server();
void handle_client(int conn);

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

void handle_client(int conn)
{
	char* welcome = "Connected!\n";
	char buffer[1024] = {0};

	send(conn, welcome, strlen(welcome), 0); 
	while (1)
	{
		int val = read(conn, buffer, sizeof(buffer));
		printf("Client %d: %d %s\n", conn, val, buffer);
		break;
	}
}

int main(int argc, char** argv)
{
	printf("SERVER: %d\n", server_fd);
	if (create_server() < 0)
		return -1;

	pthread_t thread;
	int conn;
	int addrlen = sizeof(address);
	
	while (1)
	{
		// Listening for the clients
		listen(server_fd, 1);

		if ((conn = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0)
			fprintf(stderr, "Accept error!");
		int err = pthread_create(&thread, NULL, handle_client, conn);
		if (err)
			fprintf(stderr, "Error in threading!");
	}
	return 0;
}

