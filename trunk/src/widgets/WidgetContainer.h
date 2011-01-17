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

#ifndef _WIDGETS_WIDGETCONTAINER_H_
#define _WIDGETS_WIDGETCONTAINER_H_

#include <list>

namespace Graphics {
	Renderer;
}

namespace Widgets
{

class Widget;

typedef std::list<Widget*> WidgetList;

class WidgetContainer
{
public:
	WidgetList		mWidgets;

	WidgetContainer();
	~WidgetContainer();

	virtual void Draw(Graphics::Renderer* renderer);
	virtual void MouseMove(sint32 x, sint32 y);

	void AddWidget(Widget* w);
	void RemoveWidget(Widget* w);

	Widget* GetWidgetAt(sint32 x, sint32 y);
};

}

#endif