#include "global.h"

int window_width = 640;
int window_height = 480;
SDL_Window * window_window;

void window_init() {
	SDL_DisplayMode displayMode;
	int windowCreationFlags;

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		fatalSDL();
	}

	if (FULLSCREEN) {
		if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
			fatalSDL();
		}
		window_width = displayMode.w;
		window_height = displayMode.h;
	}

	windowCreationFlags = 0;
	if (FULLSCREEN) {
		//windowCreationFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		windowCreationFlags |= SDL_WINDOW_FULLSCREEN;
	}

	window_window = SDL_CreateWindow(
		APPLICATION_TITLE, 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		windowCreationFlags);
	if (window_window == NULL) fatalSDL();

	SDL_ShowCursor(0);

	// Why is the following needed? Is it for retina displays?
	//SDL_GL_GetDrawableSize(window_window, &width, &height);
	SDL_GetWindowSize(window_window, &window_width, &window_height);
}

