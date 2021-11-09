#ifndef _CONFIG_H_
#define _CONFIG_H_

// Common includes
#include <SDL2/SDL.h>

// std's
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Networking based
#include <sys/socket.h>
#include <netinet/in.h>
#include "tokens.h"

#include "encrypt.h"

#define BUFFER_SIZE 1024

// Networking settings
#define PORT 8080
static char* ip = "127.0.0.1";

static int server;

// Help
static char* help = "          Welcome to ****           \n"
					"  Ctrl+l  : To focus on server list.\n"
					"  Ctrl+n  : To join new server.     \n"
					"  Ctrl+h  : To go to home page.     ";

// Colors
static SDL_Color main_bg 	= {   0,  43,  54 };
static SDL_Color sec_bg		= {   7,  54,  66 };
static SDL_Color main_fg 	= { 238, 232, 213 };
static SDL_Color red		= { 220,  50,  47 };
static SDL_Color blue		= {  38, 139, 210 };
static SDL_Color cyan		= {  42, 161, 152 };
static SDL_Color green		= { 133, 153, 	0 };
static SDL_Color gray		= {  88, 110, 117 };

// UI stuff
//static char* font_path = "/usr/share/fonts/TTF/Terminess (TTF) Nerd Font Complete.ttf";
static char* font_path = "Client/assets/Terminess (TTF) Nerd Font Complete Mono.ttf";
//static char* font_path = "Client/assets/JetBrainsMonoNL-Regular.ttf";
static int font_size = 23;

#endif
