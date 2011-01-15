/*
Copyright (C) 2010 Populous Mana Source Development Team

This file is part of poplib.

poplib is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

poplib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with poplib. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <fstream>
#include "SpriteFile.h"

using namespace std;
using namespace Graphics;

const int SpriteFileMagicNumber = 0x50534642;

SpriteFile::SpriteFile(string filename)
{
	ifstream fs;
	fs.open(filename.c_str(), ios::binary);

	fs.seekg(0, ios::end);
	int size = fs.tellg();
	fs.seekg(0, ios::beg);

	mBuffer = new char[size];
	
	fs.read(mBuffer, size);

	fs.close();

	if (!((int*)&mBuffer[0]) == SpriteFileMagicNumber) {
		return;
	}

	mSprites = ((int*)mBuffer)[1];
	mWidths = new short[mSprites];
	mHeights = new short[mSprites];
	mOffsets = new int[mSprites];

	int pos = 8;
	for (int i = 0; i < mSprites; i++) {
		mWidths[i] = *((short*)&mBuffer[pos]); pos += 2;
		mHeights[i] = *((short*)&mBuffer[pos]); pos += 2;
		mOffsets[i] = *((int*)&mBuffer[pos]); pos += 4;
	}
}

SpriteFile::~SpriteFile()
{
}
