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