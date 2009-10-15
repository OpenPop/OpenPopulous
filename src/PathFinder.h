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

#ifndef _PATH_FINDER_H_
#define _PATH_FINDER_H_

#include <vector>

class Unit;
class PathFinder
{
public:
	//Travel states
	enum TRAVEL_STATE
	{
		TRAVEL_STATE_ARRIVED,
		TRAVEL_STATE_ON_THE_WAY,
		TRAVEL_STATE_BLOCKED,
	};

	//Node structure
	struct Node
	{
		int		x;
		int		y;
		Node*	next;
		Node*	prev;
		float	heuristic;
		bool	exploredCell;
	};

	typedef std::vector<Node*> NodeList;

	Unit*	mUnit;
	int		mDestX;
	int		mDestY;
	bool	mDirect;

private:
	NodeList	openNodes;
	NodeList	closedNodes;
	Node		*nodePool;
	int			nodePoolCount;

	float		CalculateHeuristic(int x, int y, int destX, int destY);
	Node*		NewNode();

public:
	PathFinder(Unit* unit);
	~PathFinder();

	TRAVEL_STATE CalculatePath();
};

#endif