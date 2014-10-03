#include "SDL.h"
#include "Input.h"

bool Input::process() {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
		 	if (e.key.keysym.sym == SDLK_ESCAPE) return false;
		}
	}
	return true;
}

