#include "menu.h"

Menu* menu_new(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color bg, SDL_Color border)
{
	Menu* menu = malloc(sizeof(Menu));

	menu->rect = rect;
	menu->bg = bg;
	menu->border = border;

	menu->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
	return menu;
}

void menu_destroy(Menu* menu)
{
	SDL_DestroyTexture(menu->texture);
	free(menu);
}

void menu_render_begin(Menu* menu, SDL_Renderer* renderer)
{
	// Draw border
	SDL_Rect border_rect = { menu->rect.x - 2, menu->rect.y - 2, menu->rect.w + 4, menu->rect.h + 4 };
	SDL_SetRenderDrawColor(renderer, menu->border.r, menu->border.g, menu->border.b, menu->border.a);
	SDL_RenderFillRect(renderer, &border_rect);

	// Setting the target texture
	SDL_SetRenderTarget(renderer, menu->texture);
	SDL_SetRenderDrawColor(renderer, menu->bg.r, menu->bg.g, menu->bg.b, menu->bg.a);
	SDL_RenderClear(renderer);

	// Code beyond this function will be drawn inside of the menu texture
}

void menu_render_end(Menu* menu, SDL_Renderer* renderer)
{
	// Resetting the target texture and rendering the texture of menu
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, menu->texture, NULL, &menu->rect);
}

void menu_update_rect(Menu* menu, SDL_Rect rect)
{
	menu->rect = rect;
}

