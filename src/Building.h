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

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <vector>

#include "Object.h"
#include "Unit.h"

//Building types
enum BUILDING
{
	BUILDING_SMALL_HUT,
	BUILDING_MEDIUM_HUT,
	BUILDING_LARGE_HUT,
	BUILDING_TOWER,
	BUILDING_WARRIOR,
	BUILDING_TEMPLE	,
	BUILDING_FIREWARRIOR,
	BUILDING_SPY,
	BUILDING_BOAT,
	BUILDING_BALLOON,
};

struct BuildingAvailability
{
	int Buildings;

	inline void SetBuilding(BUILDING b, bool state)
	{
		if (state)
			Buildings |= b;
		else
			Buildings &= ~b;
	}

	inline bool IsBuildingOn(BUILDING b)
	{
		return (Buildings & b);
	}
};

struct BuildingStatus
{
	BuildingAvailability	AvailableBuildings;
	int 					BuildingShots;
};

//Building flags
enum BUILDING_FLAGS
{
	BUILDING_PLAN,
	BUILDING_BUILDING,
	BUILDING_DISMANTALING,
	BUILDING_BURNING,
	BUILDING_SHAKING,
};

//The building class which will be inherited by building type classes
class Building : public Object
{
public:
	int			mFlags;
	int			mMaxInsiders;		//The maximum number of units allowed inside the building
	int			mWood;				//The amount of wood the building currently has
	int			mWoodRequired;		//The amount of wood needed to complete the building
	UnitList	mBuilders;			//The list of units constructing the building
	UnitList	mInsiders;			//The list of units inside the hut

public:
	Building(int type);
	~Building();

	void Draw();
	void Update();
};

typedef std::vector<Building*> BuildingList;

#endif