#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

typedef struct Entry
{
	SDL_Rect rect;
	SDL_Texture* texture;				// Surface
	
	SDL_Rect cursor;
	SDL_Color fg, bg, border;			// Colors

	char* input;						// Input buffer
	int max_input;						// Max input size

	int input_pos;
	int scroll_x;

} Entry;


Entry* entry_new(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect rect, int max_input, SDL_Color fg, SDL_Color bg, SDL_Color border);
void entry_render(Entry* entry, SDL_Renderer* renderer, TTF_Font* font);
void entry_destroy(Entry* entry);
void entry_insert(Entry* entry, char* text);
void entry_event(Entry* entry, SDL_Event event);
char* entry_get(Entry* entry);
void entry_clear(Entry* entry);

#endif
