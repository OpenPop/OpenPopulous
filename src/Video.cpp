#include <sdl/sdl.h>

#include "Sprites.h"
#include "Video.h"

SDL_Surface *main_screen;
int test_draw_cnt = 0;

bool InitVideo()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		//return false;
	}

	

	main_screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	if (main_screen == NULL) {
		return false;
	}

	return true;
}

void TestDraw()
{
	void *buffer = main_screen->pixels;

	int bpp = main_screen->format->BytesPerPixel;
	int width = main_screen->w;
	int height = main_screen->h;
	
	memset(buffer, 0, width * height * bpp);

	test_draw_cnt = (test_draw_cnt + 1) % 8;
	DrawSprite(200, 200, hspr, 7618 + test_draw_cnt);

	SDL_Flip(main_screen);
}

void DrawPixel(int x, int y, int col)
{
	SDL_Colour *argb = (SDL_Colour*)&col;
	Uint32 colour = SDL_MapRGB(main_screen->format, argb->r, argb->g, argb->b);

	Uint32 *pixmem32;

	pixmem32 = (Uint32*)main_screen->pixels + (main_screen->w * y) + x;
	*pixmem32 = colour;
}