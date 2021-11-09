#include "config.h"
#include "Engine/engine.h"
#include "home.h"
#include "app.h"

int connect_sv();

int connect_sv()
{
	struct sockaddr_in sv_addr;

	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		fprintf(stderr, "Socket failed!\n");
		return -1;
	}

	sv_addr.sin_family = AF_INET;
	sv_addr.sin_port = htons(PORT);

	inet_pton(AF_INET, ip, &sv_addr.sin_addr);

	// Trying to connect to the server
	if (connect(server, (struct sockaddr*) &sv_addr, sizeof(sv_addr)) < 0)
	{
		fprintf(stderr, "Failed to connect!\n"); 
		return -1;	//TODO: display some error popup
	}
}

int main(int argc, char** argv)
{
	if (connect_sv() < 0)
		return -1;
	
	atexit(report_mem_leak);
	if (engine_init() < 0) return -1;
	
	Window* window = window_new("App", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);

	TTF_Font* font = TTF_OpenFont(font_path, font_size);
	if (!font) return -1;

	// Starting home page
	HomePage* home_page = home_page_new(window, font, server);
	bool passed = home_page_run(home_page);
	home_page_close(home_page);
	
	printf("Started app!\n");
	if (passed)
	{	
		// Starting the app
		App* app = app_new(window, font, server);
		printf("Running app!\n");
		app_run(app);
		app_close(app);
	}

	// Sending disconnect msg when quiting the app
	char msg[10] = {0};
	sprintf(msg, "%d %s %s", DISCONNECT, "a", "b");
	send(server, msg, strlen(msg), 0);

	window_destroy(window);
	engine_quit();
	return 0;
}


