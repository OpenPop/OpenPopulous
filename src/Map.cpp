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

#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::InitMap(int size)
{
	mSize = size;
	mLandHeight = new unsigned short[size * size];
	memset(mLandHeight, 0, size * size * 2);
}

int Map::GetLandIndex(int x, int y)
{
	return (y * mSize) + x;
}

unsigned short Map::GetLandHeight(int x, int y)
{
	return mLandHeight[GetLandIndex(x, y)];
}

unsigned short Map::SetLandHeight(int x, int y, unsigned short value)
{
	return mLandHeight[GetLandIndex(x, y)] = value;
}

void Map::AddObject(Object* obj)
{
	mObjects.push_back(obj);
}

Object* Map::ObjectAtXY(int x, int y){
	int SizeOfmObjects = sizeof(mObjects) / sizeof(mObjects[0]);

	for(int i=0; i<SizeOfmObjects; i++){
		Object* obj = mObjects[i];

		if(obj->mX == x && obj->mY == y){
			return mObjects[i];
		}
	}

	return 0;
}

Object* Map::ObjectAt(int i)
{
	return mObjects[i];
}

int Map::TotalObjects()
{
	return mObjects.size();
}

void Map::Draw()
{

}

void Map::Update()
{
	for (int i = 0; i < TotalObjects(); i++) {
		ObjectAt(i)->Update();
	}
}