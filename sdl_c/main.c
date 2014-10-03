
// For base code, see http://stackoverflow.com/questions/18591758/sdl2-tilemap-too-slow


/*
	Conventions:

	Externally visible variables and functions are prefix by the filename
	in which they are implemented.  For example, window_init() is defined
	in window.c.

	Other than the prfix for globally visible identifiers, variable and
	function names are in lowerCamelCase.

	Type names are in UpperCamelCase.

	Use tabs for indentation.
*/

#include "global.h"

void window_init();
extern SDL_Window * window_window;

void screen_init();
void screen_update();

bool input_process();

bool main_running = true;

static void init() {
	srand(SEED);
	window_init();
	screen_init();
}

static void loop() {
	Uint32 updateStartTime;
	Uint32 updateElapsedTime;

	while (main_running) {
		updateStartTime = SDL_GetTicks();
		if (!input_process()) {
			main_running = false;
			break;
		}
		screen_update();
		updateElapsedTime = SDL_GetTicks() - updateStartTime;
		if (updateElapsedTime < MILLIS_PER_UPDATE) {
			SDL_Delay(MILLIS_PER_UPDATE - updateElapsedTime);
		} else {
			puts("Frame deadline missed.");
			SDL_Delay(1);
		}
	}
}

static void shutdown() {
	SDL_DestroyWindow(window_window);
	SDL_Quit();
}

int main(int argc, char * argv[]) {
	init();
	loop();
	shutdown();
	return 0;
}

