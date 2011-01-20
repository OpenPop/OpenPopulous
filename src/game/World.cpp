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

#include <cstring>
#include "Object.h"
#include "World.h"

using namespace Game;

World::World()
{
	mSize = 128;
}

World::~World()
{

}

void World::Init()
{
	//Create the land tile array
	mLandTiles = new WorldTile[mSize * mSize];
	memset(mLandTiles, 0, mSize * mSize * sizeof(WorldTile));
}

void World::Update()
{
	ObjectList::iterator it;

	for (it = mObjects.begin(); it != mObjects.end(); it++) {
		Object* obj = *it;
		obj->Update();
	}
}