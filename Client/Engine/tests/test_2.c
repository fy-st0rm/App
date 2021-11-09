#include "engine.h"

int main(int argc, char** argv)
{
	if (engine_init() < 0) return -1;

	Window* window = window_new("Helo", 800, 600, 0);

	char* font_path = "../assets/Terminess (TTF) Nerd Font Complete Mono.ttf";
	int font_size = 25;
	TTF_Font* font = TTF_OpenFont(font_path, font_size);

	// Listbox
	SDL_Rect l_rect = { 100, 100, 100, 400 };
	SDL_Color l_bg = { 0, 165, 165, 255 };
	SDL_Color l_border = { 255, 255, 255, 255 };	
	ListBox* listbox = listbox_new(window->renderer, l_rect, l_bg, l_border);

	// Button
	SDL_Rect b_rect = { 0, 0, 0, 0 };
	SDL_Color b_fg = { 255, 255, 255, 255 };
	SDL_Color b_bg = { 0, 165, 165, 255 };
	//Button* button = button_new(window->renderer, b_rect, font, "Helo", b_fg, b_bg, l_border);
	
	for (int i = 0; i < 10; i++)
	{
		char text[5];
		sprintf(text, "%d", i);
		Button* button = button_new(window->renderer, b_rect, font, text, b_fg, b_bg, l_border);
		listbox_append(listbox, button);
	}

	SDL_Color bg = { 165, 165, 165, 255 }; 
	bool loop = true;
	SDL_Event event;

	while (loop)
	{
		window_clear(window, bg);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) loop = false;
			listbox_event(listbox, event);
		}

		listbox_render(listbox, window->renderer, font);

	}
	
	window_destroy(window);
	engine_quit();
}
