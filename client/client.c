// std's
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Networking based
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080


int main(int argc, char** argv)
{
	int server = 0;
	struct sockaddr_in sv_addr;

	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		fprintf(stderr, "Socket failed!");
		return -1;
	}

	sv_addr.sin_family = AF_INET;
	sv_addr.sin_port = htons(PORT);

	inet_pton(AF_INET, "127.0.0.1", &sv_addr.sin_addr);

	// Trying to connect to the server
	if (connect(server, (struct sockaddr*) &sv_addr, sizeof(sv_addr)) < 0)
	{
		fprintf(stderr, "Failed to connect!"); 
		return -1;	//TODO: display some error popup
	}

	char buffer[1024] = {0};
	read(server, buffer, sizeof(buffer));
	printf("Server: %s\n", buffer);

	char* msg = "Helo!";
	send(server, msg, strlen(msg), 0);

	return 0;
}


