#include "global.h"

bool input_process() {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
		 	if (e.key.keysym.sym == SDLK_ESCAPE) return false;
		} else if (e.type == SDL_WINDOWEVENT) {
			if (e.window.event == SDL_WINDOWEVENT_CLOSE) return false;
		}
	}
	return true;
}
