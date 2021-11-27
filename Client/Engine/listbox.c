#include "listbox.h"

//TODO:
//[] Button selection
//[] Return selection
//[] Mouse and keyboard events?

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
	listbox->speed = 50;
	
	// Selection thingy
	listbox->active = false;
	listbox->selected = 0;
	listbox->focused = 0;

	SDL_Color selected_color = { 7, 54, 66 };	
	listbox->selected_color = selected_color;
	listbox->focused_color = selected_color;

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
		int height = listbox->buttons[i]->rect.h;
		SDL_Rect rect = { 0, (i * height) + listbox->scroll_y, listbox->rect.w, height };	
		listbox->scroll_end = (i * height) + listbox->scroll_y;
		
		if  (((rect.y + rect.h) > 0) && (rect.y < listbox->rect.h))
		{
			// Changing the colors for selected and focused buttons
			if (i == listbox->selected)
				button_change_bg(listbox->buttons[i], listbox->selected_color);
			else if (i == listbox->focused)
				button_change_bg(listbox->buttons[i], listbox->focused_color);
			else
				button_change_bg(listbox->buttons[i], listbox->buttons[i]->backup_bg); 

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
	/*
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
	else if (event.type == SDL_MOUSEMOTION)
	{
		for (int i = 0; i < listbox->len; i++)
		{
			SDL_Rect rect = { 0, (i * 50) + listbox->scroll_y, listbox->rect.w, 50 };	
			// Finding the focused button
			SDL_Point pos;
			SDL_GetMouseState(&pos.x, &pos.y);

			if (SDL_PointInRect(&pos, &rect))
				listbox->focused = i;
		}
	}
	*/
	if (listbox->active)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				// Scroll down
				case SDLK_j:
				case SDLK_DOWN:
					if (listbox->selected < listbox->len - 1) 
					{
						listbox->selected += 1;
						if ((listbox->scroll_end > listbox->rect.h - 50) && 
								(listbox->buttons[listbox->selected]->rect.y + listbox->buttons[listbox->selected]->rect.h + listbox->rect.y > listbox->rect.y + listbox->rect.h))
							listbox->scroll_y -= listbox->speed;
					}
					break;
				
				// Scroll up
				case SDLK_k:
				case SDLK_UP:
					if (listbox->selected > 0)
					{
						listbox->selected -= 1;
						if ((listbox->scroll_y < listbox->scroll_start) && 
								(listbox->buttons[listbox->selected]->rect.y + listbox->rect.y < listbox->rect.y))
							listbox->scroll_y += listbox->speed;
					}
					break;

				case SDLK_RETURN:
					if (listbox->focused > 0)
						listbox->selected = listbox->focused;
					break;
			}
		}
	}
}

void listbox_change_rect(ListBox* listbox, SDL_Renderer* renderer, SDL_Rect rect)
{
	if ((listbox->rect.x != rect.x) || (listbox->rect.y != rect.y) || (listbox->rect.w != rect.w) || (listbox->rect.h != rect.h))
	{
		listbox->rect = rect;
		menu_change_rect(listbox->menu, renderer, rect);
	}
}	

void listbox_change_bg(ListBox* listbox, SDL_Color bg)
{
	menu_change_bg(listbox->menu, bg);
}

void listbox_change_border(ListBox* listbox, SDL_Color border)
{
	menu_change_border(listbox->menu, border);
}
