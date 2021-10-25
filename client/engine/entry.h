#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

typedef struct Entry
{
	int x, y, w, h;				// Dimension
	SDL_Texture* texture;		// Surface

	int cur_x, cur_y;			// Cursor position
	SDL_Color fg, bg, border;	// Colors

	char* input;				// Input buffer
} Entry;


Entry* entry_new(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color fg, SDL_Color bg, SDL_Color border);
void entry_render(Entry* entry, SDL_Renderer* renderer, TTF_Font* font);
void entry_destroy(Entry* entry);

#endif
