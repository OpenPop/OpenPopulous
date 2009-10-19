/********************************************************************** 
  This file is part of OpenPop

  OpenPop is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  OpenPop is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenPop.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#include "Graphics.h"
#include "Sprites.h"
#include "Video.h"

int scale = 3;

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