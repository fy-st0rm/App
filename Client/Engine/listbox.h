#ifndef _LISTBOX_H_
#define _LISTBOX_H_

#include "menu.h"

typedef struct ListBox
{
	SDL_Rect rect;
	SDL_Color bg, border;
	Menu* menu;
} ListBox;

ListBox* listbox_new(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color bg, SDL_Color border)

#endif
