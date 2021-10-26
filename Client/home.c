#include "home.h"
#include "stdlib.h"


HomePage* home_page_new(Window* window, TTF_Font* font)
{
	HomePage* home_page = malloc(sizeof(HomePage));
	home_page->window = window;
	home_page->font = font;

	home_page->loop = true;
	home_page->page = "LOGIN";
	home_page->focus = 1;

	// Creating textures
	home_page->login_texture = create_texture(window->renderer, font, "// Login...");
	home_page->signup_texture = create_texture(window->renderer, font, "// Signup...");
	home_page->username_texture = create_texture(window->renderer, font, "Enter your username:");
	home_page->password_texture = create_texture(window->renderer, font, "Enter your password:");
	home_page->arrow_texture = create_texture(window->renderer, font, ">");

	// Creating widgets
	
	// Menu
	home_page->menu_rect.w = 400;
	home_page->menu_rect.h = 300;
	home_page->menu_rect.x = window->w / 2 - home_page->menu_rect.w / 2;
	home_page->menu_rect.y = window->h / 2 - home_page->menu_rect.h / 2;
	
	home_page->menu = menu_new(window->renderer, home_page->menu_rect, main_bg, main_bg);

	// Username entry
	home_page->username_rect.x = 20;
	home_page->username_rect.y = 85;
	home_page->username_rect.w = 300;
	home_page->username_rect.h = 30;
		
	home_page->username_entry = entry_new(window->renderer, font, home_page->username_rect, 100, main_fg, main_bg, main_bg);
	entry_set_cursor_color(home_page->username_entry, gray);

	// Password entry
	home_page->password_rect.x = 20;
	home_page->password_rect.y = 160;
	home_page->password_rect.w = 300;
	home_page->password_rect.h = 30;
	
	home_page->password_entry = entry_new(window->renderer, font, home_page->password_rect, 100, main_fg, main_bg, main_bg);
	entry_set_cursor_color(home_page->password_entry, gray);

	return home_page;
}

void home_page_update_widgets(HomePage* home_page)
{
	// Updating menu rect
	home_page->menu_rect.x = home_page->window->w / 2 - home_page->menu_rect.w / 2;
	home_page->menu_rect.y = home_page->window->h / 2 - home_page->menu_rect.h / 2;
	menu_update_rect(home_page->menu, home_page->menu_rect);
}

void home_page_username(HomePage* home_page)
{
	draw_text(home_page->window->renderer, 5, 55, home_page->username_texture, blue);
	draw_text(home_page->window->renderer, 5, 87, home_page->arrow_texture, cyan);
	entry_render(home_page->username_entry, home_page->window->renderer, home_page->menu->texture, home_page->font);
}

void home_page_password(HomePage* home_page)
{
	draw_text(home_page->window->renderer, 5, 130, home_page->password_texture, blue);
	draw_text(home_page->window->renderer, 5, 162, home_page->arrow_texture, cyan);
	entry_render(home_page->password_entry, home_page->window->renderer, home_page->menu->texture, home_page->font);
}

void home_page_handle_focus(HomePage* home_page)
{
	if (home_page->focus == 1)
	{
		entry_set_focus(home_page->username_entry);
		entry_remove_focus(home_page->password_entry);
	}
	else if (home_page->focus == 2)
	{
		entry_set_focus(home_page->password_entry);
		entry_remove_focus(home_page->username_entry);
	}
}

void home_page_run(HomePage* home_page)
{
	// Frame stuff
	int fps = 60;
	int frame_delay = 1000 / fps;
	Uint32 frame_start;
	int frame_time;
	
	
	while (home_page->loop)
	{
		frame_start = SDL_GetTicks();
		window_clear(home_page->window, 0, 0, 0, 0);

		// Event loop
		if (SDL_PollEvent(&home_page->event))
		{
			if (home_page->event.type == SDL_QUIT)
				home_page->loop = false;
			if (home_page->event.type == SDL_WINDOWEVENT)
			{
				switch (home_page->event.window.event)
				{
					// Handling window resize event
					case SDL_WINDOWEVENT_RESIZED:
					{
						SDL_GetWindowSize(home_page->window->window, &home_page->window->w, &home_page->window->h);
						home_page_update_widgets(home_page);
						break;
					}
				}
			}

			if (home_page->event.type == SDL_KEYDOWN)
			{
				switch (home_page->event.key.keysym.sym)
				{
					// To change the focus to another widget
					case SDLK_TAB:
					{
						home_page->focus++;
						if (home_page->focus > 2) home_page->focus = 1;
						break;
					}
				}
			}

			// Giving widgets the event
			entry_event(home_page->username_entry, home_page->event);
			entry_event(home_page->password_entry, home_page->event);
		}
		// Focus halder
		home_page_handle_focus(home_page);

		// Rendering process
		menu_render_begin(home_page->menu, home_page->window->renderer);
		
		if (home_page->page == "LOGIN")
			draw_text(home_page->window->renderer, 5, 5, home_page->login_texture, green); 
		else if (home_page->page == "SIGNUP")
			draw_text(home_page->window->renderer, 5, 5, home_page->signup_texture, green); 

		home_page_username(home_page);
		home_page_password(home_page);

		menu_render_end(home_page->menu, home_page->window->renderer);

		// capping the frame rate to 60
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time)
		{
			SDL_Delay(frame_delay - frame_time);
		}

	}
}

void home_page_close(HomePage* home_page)
{
	// Destroying textures
	SDL_DestroyTexture(home_page->login_texture);
	SDL_DestroyTexture(home_page->signup_texture);
	SDL_DestroyTexture(home_page->username_texture);
	SDL_DestroyTexture(home_page->password_texture);

	// Destroying widgets
	entry_destroy(home_page->username_entry);
	entry_destroy(home_page->password_entry);

	free(home_page);
}
