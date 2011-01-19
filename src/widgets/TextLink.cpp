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
#include "..\Graphics\Font.h"
#include "Widget.h"
#include "TextLink.h"

using namespace Graphics;
using namespace Widgets;

TextLink::TextLink()
{
	
}

TextLink::~TextLink()
{
}

void TextLink::Draw(Renderer* renderer)
{
	Widget::Draw(renderer);

	mHighlighted = mMouseOver;

	//Draw shadow
	//renderer->DrawString(mShadowFont, mText, mX - 5, mY - 5);

	if (mHighlighted)
		renderer->DrawString(mHighlightFont, mText, mX, mY);
	else
		renderer->DrawString(mFont, mText, mX, mY);
}

void TextLink::AutoSize()
{
	mWidth = mFont->MeasureString(mText);
	mHeight = mFont->GetHeight();
}