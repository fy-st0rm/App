#include "engine.h"


int main(int argc, char** argv)
{
	if (engine_init() < 0) return -1;

	Window* window = window_new("Helo", 800, 600, 0);

	char* font_path = "../assets/Terminess (TTF) Nerd Font Complete Mono.ttf";
	int font_size = 25;
	TTF_Font* font = TTF_OpenFont(font_path, font_size);
		
	// Entry
	SDL_Rect e_pos = { 100, 100, 300, 50 };
	SDL_Color e_fg = { 255, 255, 255, 255 };
	SDL_Color e_bg = { 0, 0, 0, 255 };
	SDL_Color e_b = { 165, 165, 0, 255 };
	
	Entry* entry = entry_new(window->renderer, font, e_pos, 100, e_fg, e_bg, e_b); 	
	
	// Button	
	SDL_Rect b_pos = { 10, 20, 200, 50 };
	SDL_Color b_fg = { 255, 255, 255, 255 };
	SDL_Color b_bg = { 0, 0, 0, 255 };
	SDL_Color b_b = { 165, 165, 0, 255 };
	Button* button = button_new(window->renderer, b_pos, font, "Click me!", b_fg, b_bg, b_b);
	
	// Menu
	SDL_Rect m_pos = { 100, 200, 500, 500 };
	SDL_Color m_bg = { 0, 165, 165, 255 };
	Menu* menu = menu_new(window->renderer, m_pos, m_bg, m_bg);
	
	SDL_Color bg = { 165, 165, 165, 255 }; 
	bool loop = true;
	SDL_Event event;

	while (loop)
	{
		window_clear(window, bg);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) loop = false;

			entry_event(entry, event);
			
			if (button_is_clicked(button, event, m_pos.x, m_pos.y))
				notify_send(window, font, "Clicked!", 5, b_fg, b_bg);	
		}

		menu_render_begin(menu, window->renderer);
		button_render(button, window->renderer);
		entry_render(entry, window->renderer, menu->texture, font);
		menu_render_end(menu, window->renderer);

	}
	
	entry_destroy(entry);
	window_destroy(window);
	engine_quit();
}
