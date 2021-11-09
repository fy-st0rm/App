#ifndef _APP_H_
#define _APP_H_

#include "config.h"
#include "Engine/engine.h"

typedef struct App
{
	Window* window;
	TTF_Font* font;
	SDL_Event event;

	SDL_Texture* help;

	int server;
	bool loop;
	int page;

	// Keys
	bool lctrl;

	// Widgets
	ListBox* sv_listbox;
	SDL_Rect sv_listbox_rect;

} App;


App* app_new(Window* window, TTF_Font* font, int server);
void app_run(App* app);
void app_close(App* app);

#endif
