#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL2/SDL.h>


typedef struct Window
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	int w, h;
} Window;


// Window functions
Window* window_new(char* title, int w, int h, int flag);
void window_clear(Window* window, SDL_Color color);
void window_destroy(Window* window);

#endif
