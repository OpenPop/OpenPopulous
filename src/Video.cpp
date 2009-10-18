#include <sdl/sdl.h>
#include <sdl/sdl_opengl.h>
#include <algorithm>

#include "Game.h"
#include "Map.h"
#include "Graphics.h"
#include "Sprites.h"
#include "Video.h"

using namespace std;

SDL_Surface *main_screen;
int test_draw_cnt = 0;

#define SCREEN_WIDTH	768
#define SCREEN_HEIGHT	768
#define SCREEN_DEPTH	32

bool InitVideo()
{

	main_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_DOUBLEBUF | SDL_HWSURFACE);

	SDL_WM_SetCaption("OpenPop","");

	if (main_screen == NULL) {
		return false;
	}

	return true;
}

void Draw()
{
	Draw2DMap();

	SDL_Flip(main_screen);
}

void Draw2DMap()
{
	Map* map = gGame->mMap;

	for (int y = 0; y < map->mSize; y++) {
		for (int x = 0; x < map->mSize; x++) {
			SDL_Color sdl_col = GetLandColour(map->GetLandHeight(x, y));
			int *col = (int*)(&sdl_col);

			for (int yy = 0; yy < 2 * scale; yy++) {
				for (int xx = 0; xx < 2 * scale; xx++) {
					Graphics::DrawPixel((x * (scale * 2)) + xx, (y * (scale * 2)) + yy, *col);
				}
			}
		}
	}

	for (int i = 0; i < map->TotalObjects(); i++) {
		Object* obj = map->ObjectAt(i);
		obj->Draw();
	}
}

SDL_Color GetLandColour(unsigned short height)
{
	if (height == 0) {
		SDL_Color col;
		col.r = 135;
		col.g = 155;
		col.b = 226;
		return col;
	} else if (height < 8) {
		return HSLtoRGB(24, 224, 200);
	} else if (height > 1023) {
		return HSLtoRGB(24, 224, 40);
	} else {
		return HSLtoRGB(24, 224, 178 - (height / 8));
	}
}

SDL_Color HSLtoRGB(int hue, int sat, int lum)
{
	float pHue,	pSat, pLum;
	float pRed,	pGreen,	pBlue;
	float temp1, temp2;
	float temp3[3];

	pHue = (float)(hue) / 239.0f;
	pSat = (float)(sat) / 239.0f;
	pLum = (float)(lum) / 239.0f;

	if (pSat == 0) {
		pRed = pLum;
		pGreen = pLum;
		pBlue = pLum;
	} else {
		if (pLum < 0.5f)
			temp2 = pLum * (1.0f + pSat);
		else
			temp2 = pLum + pSat - pLum * pSat;
		temp1 = 2 * pLum - temp2;

		temp3[0] = pHue + 1.0f / 3.0f;
		temp3[1] = pHue;
		temp3[2] = pHue - 1.0f / 3.0f;

		for (int n = 0; n < 3.0f; n++) {
			if (temp3[n] < 0.0f)
				temp3[n] = temp3[n] + 1.0f;
			if (temp3[n] > 1.0f)
				temp3[n] = temp3[n] - 1.0f;

			if (6.0f * temp3[n] < 1.0f) {
				temp3[n] = temp1 + (temp2 - temp1) * 6.0f * temp3[n];
			} else {
				if (2.0f * temp3[n] < 1.0f) {
					temp3[n] = temp2;
				} else {
					if (3.0f * temp3[n] < 2.0f)
						temp3[n] = temp1 + (temp2 - temp1)
									* ((2.0f / 3.0f) - temp3[n]) * 6.0f;
					else
						temp3[n] = temp1;
				}
			}
		}
		pRed = temp3[0];
		pGreen = temp3[1];
		pBlue = temp3[2];
	}

	SDL_Color col;

	col.r = max(min((int)(pRed * 255.0f), 255), 0);
	col.g = max(min((int)(pGreen * 255.0f), 255), 0);
	col.b = max(min((int)(pBlue * 255.0f), 255), 0);
	col.unused = 0;

	return col;
}