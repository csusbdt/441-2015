#include "global.h"

static SDL_Renderer * renderer;
static SDL_Texture * texture;

#define CELL_WIDTH 64
#define CELL_HEIGHT 64

SDL_Rect src = { 0, 0, CELL_WIDTH, CELL_HEIGHT };
SDL_Rect dst = { 0, 0, CELL_WIDTH, CELL_HEIGHT };

int tileSheetWidth;
int tileSheetHeight;

void screen_init() {
	Uint32 format;
	int access;

	renderer = SDL_CreateRenderer(window_window, -1, 0);
	if (renderer == NULL) fatalSDL();

	//texture = IMG_LoadTexture(renderer, "Cara_walking_sprite_sheet.png");
	texture = IMG_LoadTexture(renderer, "mushroom_forest.png");
	if (texture == NULL) fatalIMG();
	if (SDL_QueryTexture(texture, &format, & access, &tileSheetWidth, &tileSheetHeight) != 0) {
		fatalSDL();
	}
	if (texture == NULL) fatalSDL();
}

void screen_update() {
	int x;
	int y;

	for (x = 0; x < window_width; x += CELL_WIDTH) {
		src.x = x % tileSheetWidth;
		dst.x = x;
		for (y = 0; y < window_height; y += CELL_HEIGHT) {
			src.y = y % tileSheetHeight;
			dst.y = y;
			if (SDL_RenderCopy(renderer, texture, &src, &dst) != 0) {
				fatalSDL();
			}
		}
	}
	SDL_RenderPresent(renderer);
}

