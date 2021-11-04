#include "text.h"
#include "leak_detector_c.h"

SDL_Texture* create_texture(SDL_Renderer* renderer, TTF_Font* font, char* text)
{
	// Generates a texture for the character
	SDL_Color white = {255, 255, 255, 255};
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, white);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* create_texture_wrapped(SDL_Renderer* renderer, TTF_Font* font, char* text, int length)
{
	SDL_Color white = {255, 255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text, white, length);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void draw_text(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture, SDL_Color color)
{
	// Renders the texture onto the screen
	SDL_Rect rect;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

	rect.x = x;
	rect.y = y;
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
