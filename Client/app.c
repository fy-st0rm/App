#include "app.h"

App* app_new(Window* window, TTF_Font* font, int server)
{
	App* app = malloc(sizeof(App));

	app->window = window;
	app->font = font;
	app->server = server;

	app->loop = true;
	app->page = HOME;

	SDL_Texture* temp_texture = create_texture(window->renderer, font, "a");
	SDL_Rect rect;
	SDL_QueryTexture(temp_texture, NULL, NULL, &rect.w, NULL);	
	
	// Loading the help text
	char temp[strlen(help)];
	strcpy(temp, help);
	char* first_line = strtok(temp, "\n");

	int width = strlen(first_line) * rect.w;
	SDL_DestroyTexture(temp_texture);
	app->help = create_texture_wrapped(window->renderer, font, help, width);

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
			if (app->event.type == SDL_WINDOWEVENT)
			{
				switch (app->event.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
						SDL_GetWindowSize(app->window->window, &app->window->w, &app->window->h);
						break;
				}
			}
		}
		
		if (app->page == HOME)
		{
			// Drawing the help
			SDL_Rect rect;
			SDL_QueryTexture(app->help, NULL, NULL, &rect.w, &rect.h);
			draw_text(app->window->renderer, app->window->w / 2 - rect.w / 2, app->window->h / 2 - rect.h / 2, app->help, main_fg);
		}

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
