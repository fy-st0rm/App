#include <stdlib.h>
#include <stdio.h>

#include "window.h"
#include "notify.h"
#include "leak_detector_c.h"


Window* window_new(char* title, int w, int h, int flag)
{
	Window* window = malloc(sizeof(Window));
	window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flag);
	window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
	window->w = w;
	window->h = h;	
	
	return window;
}

void window_clear(Window* window, SDL_Color color)
{
	SDL_RenderPresent(window->renderer);
	SDL_SetRenderDrawColor(window->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(window->renderer);

	// Drawing notifications
	notify_draw(window);	
}

void window_destroy(Window* window)
{
	SDL_DestroyWindow(window->window);
	SDL_DestroyRenderer(window->renderer);
	free(window);
}
