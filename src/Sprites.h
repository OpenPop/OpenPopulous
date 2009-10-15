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

#ifndef _SPRITES_H_
#define _SPRITES_H_

namespace Sprites
{
	struct PopPalette
	{
		unsigned int		entry[256];
	};

	struct SpriteCollection
	{
		unsigned int		num_sprites;
		unsigned int		*offsets;
		unsigned short		*widths;
		unsigned short		*heights;
		unsigned int		buffer_size;
		char				*buffer;
	};

	extern PopPalette *pal;
	extern SpriteCollection *hfx, *hspr;

	void LoadSpriteCollections();
	void FreeSpriteCollections();
	void DrawSprite(int destX, int destY, const SpriteCollection *collection, int sprite);
}

#endif