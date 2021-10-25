#include "engine.h"



int main(int argc, char** argv)
{
	if (engine_init() < 0) return -1;

	Window* window = window_new("Helo", 500, 500);
	
	// Font
	const char* font_path = "/usr/share/fonts/TTF/Terminess (TTF) Nerd Font Complete.ttf";
	int font_size = 25;
	TTF_Font* font = TTF_OpenFont(font_path, font_size); 
	if (!font)
		return -1;

	// Entry test
	SDL_Color e_fg = {255, 255, 255, 0};
	SDL_Color e_bg = {0, 0, 0, 0};
	SDL_Color e_b = {0, 165, 165, 0};
	SDL_Rect e_rect = {100, 100, 300, 50};
	Entry* entry = entry_new(window->renderer, font, e_rect, 1024, e_fg, e_bg, e_b); 

	// Frame stuff
	int fps = 60;
	int frame_delay = 1000 / fps;
	Uint32 frame_start;
	int frame_time;
		
	// Main loop
	SDL_Event event;
	bool loop = true;
	while (loop)
	{
		frame_start = SDL_GetTicks();
		window_clear(window, 165, 165, 165, 255);
		
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				loop = false;
			}
			entry_event(entry, event);
			
		}
		
		// Rendering
		entry_render(entry, window->renderer, font);

		// capping the frame rate to 60
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time)
		{
			SDL_Delay(frame_delay - frame_time);
		}
	}
	
	window_destroy(window);
	engine_quit();	
	return 0;
}
