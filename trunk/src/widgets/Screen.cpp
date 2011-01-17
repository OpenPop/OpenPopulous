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

#include "..\OpenPop.h"
#include "..\Graphics\Renderer.h"
#include "Screen.h"

using namespace Graphics;
using namespace Widgets;

Screen::Screen(OpenPop* openpop)
{
	mOpenPop = openpop;
	mBackground = NULL;
}

Screen::~Screen()
{
}

void Screen::Draw(Renderer* renderer)
{
	if (mBackground != NULL)
		renderer->DrawRAW(mPalette, mBackground, 0, 0);

	WidgetContainer::Draw(renderer);
}

void Screen::MouseMove(sint32 x, sint32 y)
{
	WidgetContainer::MouseMove(x, y);
}
