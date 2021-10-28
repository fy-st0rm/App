#include "notify.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>

void notify_add(Notify* notify)
{
	for (int i = 0; i < notifications_len; i++)
	{
		Notify* notify = notifications[i];
		notify->rect.y += notify->rect.h + 10;
	}

	notifications = realloc(notifications, sizeof(Notify*) * (notifications_len + 1));
	notifications[notifications_len] = notify;
	notifications_len++;
}

void notify_remove(int index)
{
	// Creating new storage for notifcations
	Notify** new_notify = malloc(sizeof(Notify*) * (notifications_len - 1));
	for (int i = 0, j = 0; i < notifications_len; i++)
	{
		if (i != index)
		{
			new_notify[j] = notifications[i];
			j++;
		}
	}

	// Destroying the notify and freeing the old notification storage
	Notify* notify = notifications[index];
	SDL_DestroyTexture(notify->texture);
	free(notify);
	free(notifications);
	
	// Changing the pointer
	notifications = new_notify;
	notifications_len--;
}

void notify_send(Window* window, TTF_Font* font, char* text, int time, SDL_Color fg, SDL_Color bg)
{
	Notify* notify = malloc(sizeof(Notify));
	notify->texture = create_texture(window->renderer, font, text);	
	notify->time = time;
	notify->tick = SDL_GetTicks();
	notify->fg = fg;
	notify->bg = bg;
	
	SDL_QueryTexture(notify->texture, NULL, NULL, &notify->rect.w, &notify->rect.h);
	notify->rect.x = window->w - (notify->rect.w + 10);
	notify->rect.y = 5;

	notify_add(notify);
}

void notify_draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < notifications_len; i++)
	{
		Notify* notify = notifications[i];
		SDL_SetRenderDrawColor(renderer, notify->bg.r, notify->bg.g, notify->bg.b, notify->bg.a);
		SDL_Rect temp = { notify->rect.x - 5, notify->rect.y, notify->rect.w + 5, notify->rect.h + 5 };
		SDL_RenderFillRect(renderer, &temp);

		draw_text(renderer, notify->rect.x, notify->rect.y, notify->texture, notify->fg);
		
		// When the timer runs out destroy that notification	
		Uint32 sec = (SDL_GetTicks() - notify->tick) / 1000;
		if (sec == notify->time)
			notify_remove(i);
	}
}
