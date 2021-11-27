#include "search.h"

SearchBox* search_box_new(SDL_Renderer* renderer, SDL_Rect rect, TTF_Font* font, SDL_Color fg, SDL_Color bg, SDL_Color border)
{
	SearchBox* search_box = malloc(sizeof(SearchBox));

	search_box->rect = rect;
	search_box->fg = fg;
	search_box->bg = bg;
	search_box->border = border;

	search_box->lctrl = false;
	search_box->rctrl = false;

	// Search entry
	
	// Generating entry height
	int entry_height = 0;
	SDL_Texture* temp_texture = create_texture(renderer, font, "A");
	SDL_QueryTexture(temp_texture, NULL, NULL, NULL, &entry_height);
	SDL_DestroyTexture(temp_texture);
	entry_height += 6;

	SDL_Rect entry_rect = { rect.x, rect.y, rect.w, entry_height };
	search_box->entry = entry_new(renderer, font, entry_rect, 100, fg, bg, border);

	// Listbox
	SDL_Rect listbox_rect = { rect.x, rect.y + entry_height, rect.w, rect.h - entry_height };
	search_box->listbox = listbox_new(renderer, listbox_rect, bg, border);
	search_box->listbox->focused = -1;

	/*
	for (int i = 0; i < 20; i++)
	{
		char txt[2];
		sprintf(txt, "%d", i);
		SDL_Rect b_rect = { 0, 0, 0, entry_height };
		Button* new_button = button_new(renderer, b_rect, font, txt, fg, bg, border); 
		listbox_append(search_box->listbox, new_button);
	}*/

	return search_box;
}

void search_box_destroy(SearchBox* search_box)
{
	entry_destroy(search_box->entry);
	free(search_box);
}

void search_box_event(SearchBox* search_box, SDL_Event event)
{
	entry_event(search_box->entry, event);
	listbox_event(search_box->listbox, event);

	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LCTRL:
				search_box->lctrl = true;
				break;
			case SDLK_RCTRL:
				search_box->rctrl = true;
				break;

			case SDLK_j:
				if ((search_box->lctrl) || (search_box->rctrl))
				{
					search_box->listbox->active = true;
					entry_remove_focus(search_box->entry);
				}
				break;
			case SDLK_k:
				if ((search_box->lctrl) || (search_box->rctrl))
				{
					search_box->listbox->active = false;
					entry_set_focus(search_box->entry);
				}
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LCTRL:
				search_box->lctrl = false;
				break;
			case SDLK_RCTRL:
				search_box->rctrl = false;
				break;
		}
	}
}

void search_box_render(SearchBox* search_box, SDL_Renderer* renderer, TTF_Font* font)
{
	entry_render(search_box->entry, renderer, NULL, font);

	listbox_render(search_box->listbox, renderer, font);
}
