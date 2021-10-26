#include <string.h>

#include "entry.h"
#include "text.h"
#include "leak_detector_c.h"

Entry* entry_new(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect rect, int max_input, SDL_Color fg, SDL_Color bg, SDL_Color border)
{
	// Constructor	
	Entry* entry = malloc(sizeof(Entry));
	entry->rect = rect;
	
	// Setting up the buffer
	entry->input_pos = 5;
	entry->scroll_x = 0;
	entry->max_input = max_input;
	entry->input = calloc(max_input, sizeof(char));

	// Setting up the cursor
	SDL_Texture* cursor_texture = create_texture(renderer, font, "A");
	SDL_QueryTexture(cursor_texture, NULL, NULL, &entry->cursor.w, &entry->cursor.h);
	SDL_DestroyTexture(cursor_texture);

	entry->cursor.x = entry->input_pos;
	entry->cursor.y = rect.h / 2 - entry->cursor.h / 2;

	// Setting up the colors
	entry->fg = fg;
	entry->bg = bg;
	entry->border = border;

	entry->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);

	return entry;
}

void entry_destroy(Entry* entry)
{
	// Destructor
	SDL_DestroyTexture(entry->texture);
	free(entry->input);
	free(entry);
}

void entry_render(Entry* entry, SDL_Renderer* renderer, TTF_Font* font)
{
	// Drawing border
	SDL_Rect rect = {entry->rect.x - 2, entry->rect.y - 2, entry->rect.w + 4, entry->rect.h + 4};
	SDL_SetRenderDrawColor(renderer, entry->border.r, entry->border.g, entry->border.b, entry->border.a);
	SDL_RenderFillRect(renderer, &rect);
	
	// Setting the target texture
	SDL_SetRenderTarget(renderer, entry->texture);
	SDL_SetRenderDrawColor(renderer, entry->bg.r, entry->bg.g, entry->bg.b, entry->bg.a);
	SDL_RenderClear(renderer);
	
	// Drawing the text
	int entry_size = entry->rect.w / entry->cursor.w;
	char input[entry_size];
	memcpy(input, entry->input + entry->scroll_x, entry_size);
	
	SDL_Texture* texture = create_texture(renderer, font, input);
	SDL_Rect text_rect;
	SDL_QueryTexture(texture, NULL, NULL, &text_rect.w, &text_rect.h);
	draw_text(renderer, entry->input_pos, entry->rect.h / 2 - text_rect.h / 2, texture, entry->fg);
	SDL_DestroyTexture(texture);	

	// Drawing the cursor
	SDL_SetRenderDrawColor(renderer, entry->border.r, entry->border.g, entry->border.b, entry->border.a);
	SDL_Rect temp_rect = entry->cursor;
	temp_rect.x -= entry->scroll_x * entry->cursor.w;
	SDL_RenderFillRect(renderer, &temp_rect);
		
	// Drawing the target texture
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, entry->texture, NULL, &entry->rect);
}

void entry_insert(Entry* entry, char* text)
{
	//TODO: Calculate a better way for scrolling
	// Scroll control
	if ((entry->cursor.x + entry->cursor.w) - (entry->scroll_x * entry->cursor.w) > entry->rect.w)
	{
		int diff = entry->cursor.x + entry->cursor.w - (entry->scroll_x * entry->cursor.w) - (entry->rect.w);
		entry->scroll_x += diff;
	}
	else if (entry->cursor.x - (entry->scroll_x * entry->cursor.w) < 5)
	{
		if (entry->scroll_x > 0)
		{
			int diff = 5 - (entry->cursor.x - (entry->scroll_x * entry->cursor.w));
			entry->scroll_x -= diff;
			if (entry->scroll_x < 0) entry->scroll_x = 0;
		}
	}

	// Cursor movement
	if (text == "left")	
	{
		if ((entry->cursor.x) > entry->input_pos)
			entry->cursor.x -= entry->cursor.w;
	}
	else if (text == "right")
	{
		if ((entry->cursor.x) / entry->cursor.w < strlen(entry->input))
			entry->cursor.x += entry->cursor.w;
	}
	
	// Backspace and delete key handler
	else if (text == "backspace")
	{
		if ((entry->cursor.x/ entry->cursor.w > 0) && (strlen(entry->input) > 0))
		{
			int index = entry->cursor.x / entry->cursor.w - 1;
			memmove(&entry->input[index], &entry->input[index + 1], strlen(entry->input) - index);
			entry->cursor.x -= entry->cursor.w;
		}
	}
	else if (text == "delete")
	{
		if ((entry->cursor.x / entry->cursor.w >= 0) && (strlen(entry->input) > 0) && (entry->cursor.x / entry->cursor.w != strlen(entry->input)))
		{
			int index = entry->cursor.x / entry->cursor.w;
			memmove(&entry->input[index], &entry->input[index + 1], strlen(entry->input) - index);
		}
	}

	// To insert character into input buffer
	else if (entry->cursor.x / entry->cursor.w < entry->max_input)
	{	
		// When cursor is at the end
		if (entry->cursor.x / entry->cursor.w >= strlen(entry->input))
		{
			memcpy(entry->input + (entry->cursor.x / entry->cursor.w), text, sizeof(text));
			entry->cursor.x += strlen(text) * entry->cursor.w;
		}

		// When the cursor is in between
		else if ((0 <= entry->cursor.x / entry->cursor.w) && (entry->cursor.x / entry->cursor.w <= strlen(entry->input)))
		{
			char* new_input = calloc(entry->max_input, sizeof(char));
			int index = entry->cursor.x / entry->cursor.w;
			
			// Copying the old input into new one with the inputed text
			memcpy(new_input, entry->input, index);
			strcpy(new_input + index, text);
			memcpy(new_input + index + 1, entry->input + index, strlen(entry->input) - index);
		
			// Chaning the pointer to the input
			free(entry->input);
			entry->input = new_input;
			entry->cursor.x += (strlen(text)) * entry->cursor.w;
		}
	}
}

void entry_event(Entry* entry, SDL_Event event)
{
	if (event.type == SDL_TEXTINPUT)
	{
		entry_insert(entry, event.text.text);
	}
	
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LEFT:
				entry_insert(entry, "left");
				break;
			case SDLK_RIGHT:
				entry_insert(entry, "right");
				break;	
			case SDLK_BACKSPACE:
				entry_insert(entry, "backspace");
				break;
			case SDLK_DELETE:
				entry_insert(entry, "delete");
				break;
			case SDLK_UP:
				entry->scroll_x += 1;
				break;
			case SDLK_DOWN:
				entry->scroll_x -= 1;
				break;
		}
	}
}

char* entry_get(Entry* entry)
{
	return entry->input;
}

void entry_clear(Entry* entry)
{
	free(entry->input);
	entry->input = calloc(entry->max_input, sizeof(char));
	entry->cursor.x = entry->input_pos;
	entry->scroll_x = 0;
}

