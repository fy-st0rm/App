#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "menu.h"
#include "button.h"
#include "listbox.h"
#include "entry.h"
#include "text.h"


typedef struct SearchBox
{
	SDL_Rect rect;
	SDL_Color fg, bg, border;

	// Keys
	bool lctrl, rctrl;
	
	// Widgets
	Entry* entry;
	ListBox* listbox;
} SearchBox;

SearchBox* search_box_new(SDL_Renderer* renderer, SDL_Rect rect, TTF_Font* font, SDL_Color fg, SDL_Color bg, SDL_Color border);
void search_box_destroy(SearchBox* search_box);
void search_box_render(SearchBox* search_box, SDL_Renderer* renderer, TTF_Font* font);
void search_box_event(SearchBox* search_box, SDL_Event event);

#endif
