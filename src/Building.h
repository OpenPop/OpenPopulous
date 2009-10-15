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
	BUILDING_SMALL_HUT		=	2^0,
	BUILDING_MEDIUM_HUT		=	2^1,
	BUILDING_LARGE_HUT		=	2^2,
	BUILDING_GUARD_TOWER	=	2^3,
	BUILDING_WARRIOR		=	2^4,
	BUILDING_TEMPLE			=	2^5,
	BUILDING_FIREWARRIOR	=	2^6,
	BUILDING_SPY			=	2^7,
	BUILDING_BOAT			=	2^8,
	BUILDING_BALLOON		=	2^9,

	MAX_BUILDINGS			=	10,
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
	char					BuildingShots[MAX_BUILDINGS];
};

//Building flags
enum BUILDING_FLAGS
{
	BUILDING_PLAN			=	2^0,
	BUILDING_BUILDING		=	2^1,
	BUILDING_DISMANTALING	=	2^2,
	BUILDING_BURNING		=	2^3,
	BUILDING_SHAKING		=	2^4,
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
	Building();
	virtual ~Building();

	virtual void Draw();
	virtual void Update();
};

typedef std::vector<Building*> BuildingList;

#endif