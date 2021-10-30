#ifndef _NOTIFY_H_
#define _NOTIFY_H_


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"

typedef struct Notify
{
	SDL_Texture* texture;
	int time;
	Uint32 tick;
	SDL_Color fg, bg;
	SDL_Rect rect;
} Notify;

static Notify** notifications;
static int notifications_len = 0;

void notify_add(Notify* notify);
void notify_remove(int index);
void notify_send(Window* window, TTF_Font* font, char* text, int time, SDL_Color fg, SDL_Color bg);
void notify_draw(Window* window);

#endif
