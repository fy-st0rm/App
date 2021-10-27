#ifndef _HOME_H_
#define _HOME_H_

#include "Engine/engine.h"
#include "config.h"


typedef struct HomePage
{
	Window* window;
	TTF_Font* font;
	SDL_Event event;

	bool loop;
	char* page;

	// Textures
	SDL_Texture* login_texture;
	SDL_Texture* signup_texture;
	SDL_Texture* username_texture;
	SDL_Texture* password_texture;
	SDL_Texture* arrow_texture;

	int focus;

	// Widgets
	Menu* menu;
	SDL_Rect menu_rect;

	Entry* username_entry;
	SDL_Rect username_rect;

	Entry* password_entry;
	SDL_Rect password_rect;

	Button* create_button;
	SDL_Rect create_button_rect;

	Button* mode_button;
	SDL_Rect mode_button_rect;
} HomePage;

HomePage* home_page_new(Window* window, TTF_Font* font);
void home_page_run				(HomePage* home_page);
void home_page_close			(HomePage* home_page);
void home_page_resize_widgets	(HomePage* home_page);
void home_page_update_widgets	(HomePage* home_page);
void home_page_username			(HomePage* home_page);
void home_page_password			(HomePage* home_page);

#endif
