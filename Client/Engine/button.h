#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Button
{
	SDL_Rect rect;
	SDL_Color fg, bg, border;
	SDL_Texture* text_texture;
} Button;

Button* button_new(SDL_Renderer* renderer, SDL_Rect rect, TTF_Font* font, char* text, SDL_Color fg, SDL_Color bg, SDL_Color border);
void button_destroy(Button* button);
void button_render(Button* button, SDL_Renderer* renderer);
bool button_event(Button* button, SDL_Event event);

#endif
