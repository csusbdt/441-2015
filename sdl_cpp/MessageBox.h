#pragma once

#include <string>
#include "SDL.h"
#include "Constants.h"

class MessageBox {
public:
	static void info(const char * msg) {
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_INFORMATION, 
			Constants::applicationTitle, 
			msg, 
			NULL);
	}

	static void info(const std::string & msg) {
		info(msg.c_str());
	}

	static void error(const char * msg) {
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			Constants::applicationTitle, 
			msg, 
			NULL);
	}

	static void error(const std::string & msg) {
		error(msg.c_str());
	}
};

