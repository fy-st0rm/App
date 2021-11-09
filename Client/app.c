#include "app.h"

App* app_new(Window* window, TTF_Font* font, int server)
{
	App* app = malloc(sizeof(App));

	app->window = window;
	app->font = font;
	app->server = server;

	app->loop = true;
	app->page = HOME;

	// Initializing keys
	app->lctrl = false;
	
	// Loading the help text
	char temp[strlen(help)];
	strcpy(temp, help);
	char* first_line = strtok(temp, "\n");

	int width;
	SDL_Texture* temp_texture = create_texture(window->renderer, font, first_line);
	SDL_QueryTexture(temp_texture, NULL, NULL, &width, NULL);
	SDL_DestroyTexture(temp_texture);
	app->help = create_texture_wrapped(window->renderer, font, help, width);

	// Loading widgets
	
	// Server listbox
	SDL_Rect sv_listbox_rect = { 0, 0, 100, window->h};
	app->sv_listbox_rect = sv_listbox_rect;
	app->sv_listbox = listbox_new(window->renderer, sv_listbox_rect, main_bg, main_bg);

	// Test buttons
	SDL_Rect test_rect = { 0, 0, 0, 0 };
	for (int i = 0; i < 20; i++)
	{
		char text[5];
		sprintf(text, "%d", i);
		Button* server = button_new(window->renderer, test_rect, font, text, main_fg, main_bg, green);
		listbox_append(app->sv_listbox, server);
	}

	return app;
}

void app_run(App* app)
{
	// Frame stuff
	int fps = 75;
	int frame_delay = 1000 / fps;
	Uint32 frame_start;
	int frame_time;

	while (app->loop)
	{
		frame_start = SDL_GetTicks();
		window_clear(app->window, sec_bg);

		// Event loop
		if (SDL_PollEvent(&app->event))
		{
			if (app->event.type == SDL_QUIT) app->loop = false;
			else if (app->event.type == SDL_WINDOWEVENT)
			{
				switch (app->event.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
						SDL_GetWindowSize(app->window->window, &app->window->w, &app->window->h);
						break;
				}
			}
			else if (app->event.type == SDL_KEYDOWN)
			{
				switch(app->event.key.keysym.sym)
				{
					case SDLK_LCTRL:
						app->lctrl = true;
						break;

					case SDLK_h:
						if (app->lctrl)
							app->page = HOME;
						break;

					case SDLK_l:
						if (app->lctrl)
							app->page = SERVER_LIST;
						break;
				}
			}
			else if (app->event.type == SDL_KEYUP)
			{
				switch(app->event.key.keysym.sym)
				{
					case SDLK_LCTRL:
						app->lctrl = false;
						break;
				}
			}
			else if (app->event.type == SDL_MOUSEMOTION)
			{
				// This handles the activation of server list control via mouse
				SDL_Point point;
				SDL_GetMouseState(&point.x, &point.y);

				if (SDL_PointInRect(&point, &app->sv_listbox->rect))
					app->page = SERVER_LIST;
				else
					app->page = HOME;
			}

			// Giving widgets event handlers
			if (app->page == SERVER_LIST)
			{
				listbox_change_border(app->sv_listbox, green);
				listbox_event(app->sv_listbox, app->event);
			}
			else
				listbox_change_border(app->sv_listbox, main_bg);
		}
		

		// Rendering here	

		// Drawing the help
		SDL_Rect rect;
		SDL_QueryTexture(app->help, NULL, NULL, &rect.w, &rect.h);
		draw_text(app->window->renderer, app->window->w / 2 - rect.w / 2, app->window->h / 2 - rect.h / 2, app->help, main_fg);


		SDL_Rect sv_listbox_rect = { 0, 0, 100, app->window->h };
		listbox_change_rect(app->sv_listbox, app->window->renderer, sv_listbox_rect);
		listbox_render(app->sv_listbox, app->window->renderer, app->font);


		// capping the frame rate to 60
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time)
		{
			SDL_Delay(frame_delay - frame_time);		
		}
	}
}

void app_close(App* app)
{
	free(app);
}
