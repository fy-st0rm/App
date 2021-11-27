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

	// Initializing widgets
	SDL_Rect temp_search_rect = { 100, 100, 400, 400 };
	app->search_box_rect = temp_search_rect;
	app->search_box = search_box_new(window->renderer, app->search_box_rect, font, main_fg, main_bg, gray); 
	
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

			search_box_event(app->search_box, app->event);
		}

		search_box_render(app->search_box, app->window->renderer, app->font);
		
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
	search_box_destroy(app->search_box);
	free(app);
}
