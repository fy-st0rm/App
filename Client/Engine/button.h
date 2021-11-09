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
	SDL_Color fg, bg, border, backup_bg;
	char* text;
	SDL_Texture* text_texture;
	bool active;
} Button;

Button* button_new(SDL_Renderer* renderer, SDL_Rect rect, TTF_Font* font, char* text, SDL_Color fg, SDL_Color bg, SDL_Color border);
void button_destroy(Button* button);
void button_render(Button* button, SDL_Renderer* renderer);
bool button_is_clicked(Button* button, SDL_Event, int offset_x, int offset_y);
bool button_active(Button* button, int offset_x, int offset_y);
void button_change_fg(Button* button, SDL_Color fg);
void button_change_bg(Button* button, SDL_Color bg);
void button_change_text(Button* button, SDL_Renderer* renderer, TTF_Font* font, char* text);
void button_change_rect(Button* button, SDL_Renderer* renderer, TTF_Font* font, SDL_Rect rect);

#endif
