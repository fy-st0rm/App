#include "engine.h"
#include "leak_detector_c.h"

int main(int argc, char** argv)
{
	atexit(report_mem_leak);
	if (engine_init() < 0) return -1;

	Window* window = window_new("Helo", 800, 600);
	
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

	// Menu test
	SDL_Color m_bg = {165, 0, 165, 0};
	SDL_Color m_b = {0, 165, 165, 0};
	SDL_Rect m_rect = {100, 300, 500, 300};
	Menu* menu = menu_new(window->renderer, m_rect, m_bg, m_b);

	// Button test
	SDL_Color b_bg = {255, 255, 255, 255};
	SDL_Color b_fg = {0, 0, 0, 255};
	SDL_Color b_b = {0, 0, 0, 255};
	SDL_Rect b_rect = {100, 50, 100, 50};
	Button* button = button_new(window->renderer, b_rect, font, "helo",  b_fg, b_bg, b_b);

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
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_RETURN:
					{
						char* output = entry_get(entry);
						if (output != "")
							printf("%s\n", output);
						entry_clear(entry);
						break;
					}
					case SDLK_ESCAPE:
					{
						entry_remove_focus(entry);
						break;
					}
					case SDLK_TAB:
					{
						entry_set_focus(entry);
						break;
					}
				}

			}

			if (button_is_clicked(button, event))
			{
				printf("Clicked\n");
			}
				
		}
		
		// Rendering

		button_render(button,  window->renderer);
		menu_render_begin(menu, window->renderer);
		entry_render(entry, window->renderer, menu->texture, font);
		menu_render_end(menu, window->renderer);

		// capping the frame rate to 60
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time)
		{
			SDL_Delay(frame_delay - frame_time);
		}
	}
	
	button_destroy(button);
	entry_destroy(entry);
	menu_destroy(menu);
	window_destroy(window);
	engine_quit();	

	return 0;
}
