#include "listbox.h"

ListBox* listbox_new(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color bg, SDL_Color border)
{
	ListBox* listbox = malloc(sizeof(ListBox));
	
	listbox->rect = rect;
	listbox->bg = bg;
	listbox->border = border;
	listbox->menu = menu_new(renderer, rect, bg, border);
	
	listbox->len = 0;
	listbox->scroll_start = 0;
	listbox->scroll_end = 0;
	listbox->scroll_y = 0;
	listbox->speed = 10;

	return listbox;
}

void listbox_destroy(ListBox* listbox)
{
	menu_destroy(listbox->menu);
	free(listbox->buttons);
	free(listbox);
}

void listbox_render(ListBox* listbox, SDL_Renderer* renderer, TTF_Font* font)
{
	menu_render_begin(listbox->menu, renderer);

	for (int i = 0; i < listbox->len; i++)
	{
		SDL_Rect rect = { 0, (i * 50) + listbox->scroll_y, listbox->rect.w, 50 };	
		listbox->scroll_end = (i * 50) + listbox->scroll_y;
		
		if  (((rect.y + rect.h) > 0) && (rect.y < listbox->rect.h))
		{
			button_change_rect(listbox->buttons[i], renderer, font, rect);
			button_render(listbox->buttons[i], renderer);
		}
	}	
	menu_render_end(listbox->menu, renderer);
}

void listbox_append(ListBox* listbox, Button* button)
{
	Button** new_buttons;
	if (listbox->len == 0)
		new_buttons = malloc(sizeof(Button*));
	else
	{
		new_buttons = malloc(sizeof(Button*) * (listbox->len + 1));
		for (int i = 0; i < listbox->len; i++)
			new_buttons[i] = listbox->buttons[i];
	}
	
	new_buttons[listbox->len] = button;

	if (listbox->len > 0)	
		free(listbox->buttons);
	listbox->len++;
	listbox->buttons = new_buttons;
}

void listbox_event(ListBox* listbox, SDL_Event event)
{
	if (event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y > 0)	// Scroll up
		{
			if (listbox->scroll_y < listbox->scroll_start)
				listbox->scroll_y += listbox->speed;
		}
		else if (event.wheel.y < 0) // Scroll down
		{
			if (listbox->scroll_end > listbox->rect.h - 50)
				listbox->scroll_y -= listbox->speed;
		}
	}
}

