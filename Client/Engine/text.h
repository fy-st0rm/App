#ifndef _TEXT_H_
#define _TEXT_H_

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

SDL_Texture* create_texture(SDL_Renderer* renderer, TTF_Font* font, char* text);
SDL_Texture* create_texture_wrapped(SDL_Renderer* renderer, TTF_Font* font, char* text, int length);
void draw_text(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture, SDL_Color color);

#endif
