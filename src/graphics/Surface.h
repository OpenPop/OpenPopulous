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
class Renderer;
class Surface
{
public:
	Renderer*				mRenderer;
	LPDIRECT3DSURFACE9		mD3DSurface;
	int						mWidth;
	int						mHeight;

	Surface(Graphics::Renderer* renderer);
	~Surface();

	void Init();
	void Clear(D3DCOLOR colour);
	void DrawRAW(PaletteFile* pal, RawFile* raw, int x, int y);
	void DrawPixel(int x, int y, int colour);
};

}

#endif