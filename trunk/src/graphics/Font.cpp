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

#include "Surface.h"
#include "PaletteFile.h"
#include "SpriteFile.h"
#include "Font.h"

using namespace std;
using namespace Graphics;

Font::Font(string sfile, string pfile)
{
	mPaletteFile = new PaletteFile(pfile);
	mSpriteFile = new SpriteFile(sfile);
}

Font::~Font()
{
}

void Font::DrawString(Surface* surface, string text, int x, int y)
{
	for (int i = 0; i < text.length(); i++) {
		char c = text[i];
		c -= 32;

		surface->DrawSprite(mPaletteFile, mSpriteFile, c, x, y);

		//Increment X by char width
		x += mSpriteFile->mWidths[c];
	}
}

int Font::MeasureString(std::string text)
{
	int x = 0;
	for (int i = 0; i < text.length(); i++) {
		char c = text[i];
		c -= 32;

		//Increment X by char width
		x += mSpriteFile->mWidths[c];
	}

	return x;
}

int Font::GetHeight()
{
	return mSpriteFile->mHeights[0];
}