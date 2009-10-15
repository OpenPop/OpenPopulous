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

#include <math.h>

#include "Game.h"
#include "Map.h"
#include "PathFinder.h"
#include "Unit.h"

PathFinder::PathFinder(Unit* unit)
{

}

PathFinder::~PathFinder()
{

}

PathFinder::TRAVEL_STATE PathFinder::CalculatePath()
{
	Map* map = gGame->mMap;
	
	//Start the search from unit position to dest co-ordinates
	Node* startNode = NewNode();
	startNode->x = mUnit->mX;
	startNode->y = mUnit->mY;
	startNode->heuristic= CalculateHeuristic(mUnit->mX, mUnit->mY, mDestX, mDestY);

	bool path_found = true;

	for (;;) {
		if (openNodes.empty()) {
			path_found = false;
			break;
		}
		

	}

	return TRAVEL_STATE_BLOCKED;
}

float PathFinder::CalculateHeuristic(int x, int y, int destX, int destY)
{
	float x_delta = abs(x - destX);
	float y_delta = abs(y - destY);

	return sqrt((x_delta * x_delta) + (y_delta * y_delta));
}

PathFinder::Node* PathFinder::NewNode()
{
	Node* node = new Node();
	openNodes.push_back(node);

	return node;
}