#include "entry.h"
#include "text.h"


Entry* entry_new(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color fg, SDL_Color bg, SDL_Color border)
{	
	Entry* entry = malloc(sizeof(Entry));
	entry->x = x;
	entry->y = y;
	entry->w = w;
	entry->h = h;
	entry->fg = fg;
	entry->bg = bg;
	entry->border = border;
	entry->input = calloc(1024, sizeof(char));

	entry->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, w, h);

	return entry;
}

void entry_render(Entry* entry, SDL_Renderer* renderer, TTF_Font* font)
{
	// Drawing border
	SDL_Rect rect = {entry->x - 2, entry->y - 2, entry->w + 4, entry->h + 4};
	SDL_SetRenderDrawColor(renderer, entry->border.r, entry->border.g, entry->border.b, entry->border.a);
	SDL_RenderFillRect(renderer, &rect);
	
	// Setting the target texture
	SDL_SetRenderTarget(renderer, entry->texture);
	SDL_SetRenderDrawColor(renderer, entry->bg.r, entry->bg.g, entry->bg.b, entry->bg.a);
	SDL_RenderClear(renderer);
	
	// Drawing the text
	entry->input = "Helo World!";
	SDL_Texture* texture = create_texture(renderer, font, entry->input);
	SDL_Rect text_rect;
	SDL_QueryTexture(texture, NULL, NULL, &text_rect.w, &text_rect.h);
	draw_text(renderer, 0, entry->h / 2 - text_rect.h / 2, texture, entry->fg);
		
	// Drawing the target texture
	SDL_SetRenderTarget(renderer, NULL);
	SDL_Rect surface_rect = {entry->x, entry->y, entry->w, entry->h};
	SDL_RenderCopy(renderer, entry->texture, NULL, &surface_rect);
}

void entry_destroy(Entry* entry)
{
	SDL_DestroyTexture(entry->texture);
	free(entry->input);
	free(entry);
}
