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

#ifndef _GRAPHICS_SURFACE_H_
#define _GRAPHICS_SURFACE_H_

#include <d3d9.h>

namespace Graphics
{

class PaletteFile;
class RawFile;
class SpriteFile;
class Renderer;
class Surface
{
public:
	Renderer*				mRenderer;
	LPDIRECT3DSURFACE9		mD3DSurface;
	sint32					mWidth;
	sint32					mHeight;

	uint32*					mBits;

	Surface(Graphics::Renderer* renderer);
	~Surface();

	void Init();
	void Clear(D3DCOLOR colour);

	void LockBits();
	void UnlockBits();

	uint32 GetOffset(sint32 x, sint32 y);
	uint32 SwapColourBits(uint32 colour);

	void FillRect(uint32 colour, sint32 x, sint32 y, sint32 w, sint32 h);
	void DrawSprite(PaletteFile* pal, SpriteFile* sfile, SpriteFile* asfile, sint32 index, sint32 x, sint32 y);
	void DrawSprite(PaletteFile* pal, SpriteFile* sfile, sint32 index, sint32 x, sint32 y);
	void DrawSprite(PaletteFile* pal, SpriteFile* sfile, uint8 alpha, sint32 index, sint32 x, sint32 y);
	void DrawRAW(PaletteFile* pal, RawFile* raw, sint32 x, sint32 y);
	void DrawPixel(sint32 x, sint32 y, sint32 colour);
};

}

#endif