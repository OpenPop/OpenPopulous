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

#include "..\stdafx.h"

#include "..\Graphics\Renderer.h"
#include "..\Graphics\SpriteFile.h"
#include "Widget.h"
#include "Box.h"

using namespace Graphics;
using namespace Widgets;

Box::Box()
{
	
}

Box::~Box()
{
}

void Box::Draw(Renderer* renderer)
{
	Widget::Draw(renderer);

	sint32 sw = 16;

	//Left top corner
	renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, 1, mX, mY);

	//Top middle
	for (sint32 x = 1; x < (mWidth - 1) / sw; x++) {
		sint32 si = 2;
		if (x % 2 == 0)
			si = 3;

		renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, si, mX + (sw * x), mY);
	}

	//Right top corner
	renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, 4, mX + mWidth - sw, mY);

	//Right middle
	for (sint32 y = 1; y < (mHeight - 1) / sw; y++) {
		sint32 si = 5;
		renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, si, mX + mWidth - sw, mY + (sw * y));
	}

	//Left middle
	for (sint32 y = 1; y < (mHeight - 1) / sw; y++) {
		sint32 si = 10;
		renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, si, mX, mY + (sw * y));
	}

	//Bottom left corner
	renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, 6, mX, mY + mHeight - sw);

	//Bottom middle
	for (sint32 x = 1; x < (mWidth - 1) / sw; x++) {
		sint32 si = 7;
		if (x % 2 == 0)
			si = 8;

		renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, si, mX + (sw * x), mY + mHeight - sw);
	}
	
	//Bottom right corner
	renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, 9, mX + mWidth - sw, mY + mHeight - sw);

	//Fill
	for (sint32 y = 1; y < (mHeight - 1) / sw; y++) {
		for (sint32 x = 1; x < (mWidth - 1) / sw; x++) {
			renderer->DrawSprite(mPalette, mBoxSprites, mAlphaBoxSprites, 0, mX + (sw * x), mY + (sw * y));
		}
	}
}