#include "global.h"

void fatal(const char * msg) {
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR, 
		APPLICATION_TITLE, 
		msg, 
		NULL);
	exit(1);	
}

void fatalSDL() {
	fatal(SDL_GetError());
}

void fatalIMG() {
	fatal(IMG_GetError());
}

