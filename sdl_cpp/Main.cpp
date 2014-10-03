#include "Main.h"

#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include "Constants.h"
#include "Util.h"
#include "Input.h"
#include "MessageBox.h"
#include "Graphics.h"

SDL_Window * Main::window;
int Main::width;
int Main::height;
bool Main::running = true;

void Main::run() {
	init();
	loop();
	shutdown();
}

void Main::init() {
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		Util::fatalSDL();
	}

	if (Constants::fullscreen) {
		SDL_DisplayMode display_mode;
		if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0) {
			Util::fatalSDL();
		}
		width = display_mode.w;
		height = display_mode.h;
	} else {
		width = Constants::windowWidth;
		height = Constants::windowHeight;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	int windowCreationFlags = SDL_WINDOW_OPENGL;
	if (Constants::fullscreen) {
		windowCreationFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	window = SDL_CreateWindow(
		Constants::applicationTitle, 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		windowCreationFlags);
	if (window == NULL) Util::fatalSDL();

	SDL_ShowCursor(0);

	//SDL_GL_GetDrawableSize(window, &width, &height);
	SDL_GetWindowSize(window, &width, &height);

	Graphics::init();
	//SDL_AddTimer(1, AI::init, NULL);
}

void Main::loop() {
	Uint32 updateStartTime;
	Uint32 updateElapsedTime;
	while (running) {
		updateStartTime = SDL_GetTicks();
		Graphics::update();
		// Call draw routines, etc.
		if (!Input::process()) break;
		updateElapsedTime = SDL_GetTicks() - updateStartTime;
		if (updateElapsedTime < millisPerUpdate) {
			SDL_Delay(millisPerUpdate - updateElapsedTime);
		} else {
			SDL_Delay(1);
		}
	}
}

void Main::shutdown() {
	Graphics::shutdown();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char * argv[]) {
	Main::run();
	return 0;
}

