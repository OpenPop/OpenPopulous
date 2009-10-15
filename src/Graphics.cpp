#include "Graphics.h"
#include "Sprites.h"
#include "Video.h"

namespace Graphics
{
	int GetScreenWidth()
	{
		return main_screen->w;
	}

	int GetScreenHeight()
	{
		return main_screen->h;
	}

	void DrawPixel(int x, int y, int col)
	{
		SDL_Colour *argb = (SDL_Colour*)&col;
		Uint32 colour = SDL_MapRGB(main_screen->format, argb->r, argb->g, argb->b);

		Uint32 *pixmem32;

		pixmem32 = (Uint32*)main_screen->pixels + (main_screen->w * y) + x;
		*pixmem32 = colour;
	}

	void DrawSprite(int destX, int destY, const Sprites::SpriteCollection *collection, int sprite)
	{
		Sprites::DrawSprite(destX, destY, collection, sprite);
	}
}