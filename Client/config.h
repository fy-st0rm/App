#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <SDL2/SDL.h>

// Networking settings
#define PORT 8080
static char* ip = "127.0.0.1";

static int server = 0;

// Colors
static SDL_Color main_bg 	= {   0,  43,  54 };
static SDL_Color main_fg 	= { 238, 232, 213 };
static SDL_Color blue		= {  38, 139, 210 };
static SDL_Color cyan		= {  42, 161, 152 };
static SDL_Color green		= { 133, 153, 	0 };
static SDL_Color gray		= {  88, 110, 117 };

// UI stuff
static char* font_path = "/usr/share/fonts/TTF/Terminess (TTF) Nerd Font Complete.ttf";
static int font_size = 25;

#endif
