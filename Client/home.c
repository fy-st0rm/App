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
	entry_remove_focus(home_page->password_entry);

	// Create button
	home_page->create_button_rect.w = 200;
	home_page->create_button_rect.h = 40;
	home_page->create_button_rect.x = home_page->menu_rect.w / 2 - home_page->create_button_rect.w / 2;
	home_page->create_button_rect.y = 200;

	home_page->create_button = button_new(window->renderer, home_page->create_button_rect, font, "<Create>", main_fg, main_bg, main_bg);

	// Mode button
	home_page->mode_button_rect.w = 200;
	home_page->mode_button_rect.h = 40;
	home_page->mode_button_rect.x = home_page->menu_rect.w / 2 - home_page->mode_button_rect.w / 2;
	home_page->mode_button_rect.y = 250;

	home_page->mode_button = button_new(window->renderer, home_page->mode_button_rect, font, "<Singup>", main_fg, main_bg, main_bg);

	return home_page;
}

void home_page_resize_widgets(HomePage* home_page)
{
	// Updating menu rect
	home_page->menu_rect.x = home_page->window->w / 2 - home_page->menu_rect.w / 2;
	home_page->menu_rect.y = home_page->window->h / 2 - home_page->menu_rect.h / 2;
	menu_update_rect(home_page->menu, home_page->menu_rect);
}

void home_page_update_widgets(HomePage* home_page)
{
	// Updating buttons
	if (button_active(home_page->create_button, home_page->menu_rect.x, home_page->menu_rect.y))
		button_change_fg(home_page->create_button, green);
	else
		button_change_fg(home_page->create_button, main_fg);
	
	if (button_active(home_page->mode_button, home_page->menu_rect.x, home_page->menu_rect.y))
		button_change_fg(home_page->mode_button, green);
	else
		button_change_fg(home_page->mode_button, main_fg);
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

void home_page_run(HomePage* home_page)
{
	// Frame stuff
	int fps = 75;
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
			
			else if (home_page->event.type == SDL_WINDOWEVENT)
			{
				switch (home_page->event.window.event)
				{
					// Handling window resize event
					case SDL_WINDOWEVENT_RESIZED:
					{
						SDL_GetWindowSize(home_page->window->window, &home_page->window->w, &home_page->window->h);
						home_page_resize_widgets(home_page);
						break;
					}
				}
			}

			// Giving widgets the event
			entry_event(home_page->username_entry, home_page->event);
			entry_event(home_page->password_entry, home_page->event);
			entry_mouse_event(home_page->username_entry, home_page->event, home_page->menu_rect.x, home_page->menu_rect.y);
			entry_mouse_event(home_page->password_entry, home_page->event, home_page->menu_rect.x, home_page->menu_rect.y);
	
			// Buttons event
			if (button_is_clicked(home_page->mode_button, home_page->event, home_page->menu_rect.x, home_page->menu_rect.y))
			{
				if (home_page->page == "LOGIN")
				{
					home_page->page = "SIGNUP";
					button_change_text(home_page->mode_button, home_page->window->renderer, home_page->font, "<Login>");

					entry_clear(home_page->username_entry);
					entry_clear(home_page->password_entry);
					entry_set_focus(home_page->username_entry);
				}
				else if (home_page->page == "SIGNUP")
				{
					home_page->page = "LOGIN";
					button_change_text(home_page->mode_button, home_page->window->renderer, home_page->font, "<Signup>");
					
					entry_clear(home_page->username_entry);
					entry_clear(home_page->password_entry);
					entry_set_focus(home_page->username_entry);
				}
			}
		}
		
		// Updating buttons
		home_page_update_widgets(home_page);

		// Rendering process
		menu_render_begin(home_page->menu, home_page->window->renderer);

		if (home_page->page == "LOGIN")
			draw_text(home_page->window->renderer, 5, 5, home_page->login_texture, green); 
		else if (home_page->page == "SIGNUP")
			draw_text(home_page->window->renderer, 5, 5, home_page->signup_texture, green); 
		
		// Rendering widgets
		home_page_username(home_page);
		home_page_password(home_page);
		
		button_render(home_page->create_button, home_page->window->renderer);
		button_render(home_page->mode_button, home_page->window->renderer);
		
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
	button_destroy(home_page->create_button);
	button_destroy(home_page->mode_button);

	free(home_page);
}
