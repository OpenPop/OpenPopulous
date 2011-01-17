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
#include "Widget.h"
#include "WidgetContainer.h"

using namespace Graphics;
using namespace Widgets;

WidgetContainer::WidgetContainer()
{
	
}

WidgetContainer::~WidgetContainer()
{
}

void WidgetContainer::Draw(Renderer* renderer)
{
	WidgetList::iterator it;

	for (it = mWidgets.begin(); it != mWidgets.end(); it++) {
		Widget* w = *it;
		w->Draw(renderer);
	}
}

void WidgetContainer::MouseMove(sint32 x, sint32 y)
{
	Widget* overWidget = GetWidgetAt(x, y);

	WidgetList::iterator it;

	for (it = mWidgets.begin(); it != mWidgets.end(); it++) {
		Widget* w = *it;

		if (w == overWidget)
			w->mMouseOver = true;
		else
			w->mMouseOver = false;
	}
}

void WidgetContainer::AddWidget(Widget* w)
{
	mWidgets.push_front(w);
}

void WidgetContainer::RemoveWidget(Widget* w)
{
	mWidgets.remove(w);
}

Widget* WidgetContainer::GetWidgetAt(sint32 x, sint32 y)
{
	WidgetList::iterator it;

	for (it = mWidgets.begin(); it != mWidgets.end(); it++) {
		Widget* w = *it;
		if (x >= w->mX && x < w->mX + w->mWidth) {
			if (y >= w->mY && y < w->mY + w->mHeight) {
				return w;
			}
		}
	}
}