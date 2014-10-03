#include <sstream>
#include "MessageBox.h"
#include "Util.h"

void Util::fatal(const char * msg) {
	MessageBox::error(msg);
	exit(1);
}

void Util::fatalSDL() {
	MessageBox::error(SDL_GetError());
	exit(1);
}

void Util::fatalSDL(const char * msg) {
	std::stringstream ss;
	ss << msg << "\n" << SDL_GetError();
	fatal(ss.str().c_str());
}

