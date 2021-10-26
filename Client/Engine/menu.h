#ifndef _MENU_H_
#define _MENU_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Menu
{
	SDL_Rect rect;
	SDL_Color bg;
	SDL_Color border;

	SDL_Texture* texture;
} Menu;

Menu* menu_new(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color bg, SDL_Color border);
void menu_destroy(Menu* menu);
void menu_render_begin(Menu* menu, SDL_Renderer* renderer);
void menu_render_end(Menu* menu, SDL_Renderer* renderer);

#endif
