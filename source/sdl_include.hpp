#pragma once

#if defined(WIN32)
	#define SDL_MAIN_HANDLED
	#include "SDL.h"
#else
	#include "SDL2/SDL.h"
#endif