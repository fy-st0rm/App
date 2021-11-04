#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <stdbool.h>
#include <string.h>

#include "window.h"
#include "text.h"
#include "entry.h"
#include "menu.h"
#include "button.h"
#include "notify.h"
#include "search.h"
#include "leak_detector_c.h"

static int engine_init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return -1;
	
	if (TTF_Init() == -1)
		return -1;

	return 0;
}

static void engine_quit()
{
	free(notifications);
	SDL_Quit();
	TTF_Quit();
}


#endif
