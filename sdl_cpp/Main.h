#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include "Constants.h"
#include "Util.h"
#include "MessageBox.h"

/**
	Create application window and implement top-level logic.
*/
class Main {
public: 
	static void run();

	static SDL_Window * window;
	static int width;
	static int height;
	static bool running;

private:
	static void init();
	static void loop();
	static void shutdown();

	static const Uint32 millisPerUpdate = 1000 / 60.0;
};

