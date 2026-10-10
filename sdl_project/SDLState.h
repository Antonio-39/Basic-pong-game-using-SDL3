#pragma once
#include <SDL3/SDL.h>
#include "Env.h"

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height, logW, logH;

	SDLState()
	{
		width = WINDOW_WIDTH;
		height = WINDOW_HEIGHT;
		logW = LOGICAL_WIDTH;
		logH = LOGICAL_HEIGHT;
	}
};