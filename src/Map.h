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

#ifndef _MAP_H_
#define _MAP_H_

#include "Object.h"

class Map
{
public:
	unsigned char	mLandscape;			//The landscape type
	unsigned char	mObjectBank;		//The object bank type

	unsigned short	mSize;				//Map size
	unsigned short	*mLandHeight;		//Pointer to land array (Map size * Map size)

	ObjectList		mObjects;			//List of all the objects

public:
	Map();
	~Map();

	void InitMap(int size);

	int GetLandIndex(int x, int y);
	unsigned short GetLandHeight(int x, int y);
	unsigned short SetLandHeight(int x, int y, unsigned short value);

	void AddObject(Object* obj);
	Object* ObjectAt(int i);
	Object* ObjectAtXY(int x, int y);
	int TotalObjects();

	void Draw();
	void Update();
};

#endif