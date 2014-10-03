#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "assert.h"
#include "limits.h"
#include "settings.h"

typedef int bool;
#define false 0
#define true 1

typedef Uint32 Time;

/*
typedef struct {
	Tone m;
	Tone n;
} Oscillator;
*/

#define PI  3.141592653589793238462

void fatal(const char * msg);
void fatalSDL();
void fatalIMG();

extern SDL_Window * window_window;
extern int window_width;
extern int window_height;

