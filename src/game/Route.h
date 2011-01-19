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

#ifndef _GAME_ROUTE_H_
#define _GAME_ROUTE_H_

#include <list>

namespace Game
{

struct RoutePoint
{
	uint32		mX;
	uint32		mY;
};
typedef std::list<RoutePoint> RoutePointList;

class Route
{
public:
	uint32				mDestX;
	uint32				mDestY;
	RoutePointList		mRoutePoints;

	Route();
	~Route();

	void Calculate();
};

}

#endif