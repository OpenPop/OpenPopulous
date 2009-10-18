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

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <sdl/sdl.h>

namespace Sprites
{
	class SpriteCollection;
}

namespace Graphics
{
	int GetScreenWidth();
	int GetScreenHeight();
	void DrawPixel(int x, int y, int col);
	void DrawSprite(int destX, int destY, const Sprites::SpriteCollection *collection, int sprite);

}

int scale = 3;

#endif