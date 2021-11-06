#ifndef _LISTBOX_H_
#define _LISTBOX_H_

#include "menu.h"
#include "button.h"

typedef struct ListBox
{
	SDL_Rect rect;
	SDL_Color bg, border;
	int len;
	int scroll_start, scroll_end, scroll_y;
	int speed;
	
	Menu* menu;
	Button** buttons;
} ListBox;

ListBox* listbox_new(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color bg, SDL_Color border);
void listbox_destroy(ListBox* listbox);
void listbox_render(ListBox* listbox, SDL_Renderer* renderer, TTF_Font* font);
void listbox_append(ListBox* listbox, Button* button);
void listbox_event(ListBox* listbox, SDL_Event event);

#endif
