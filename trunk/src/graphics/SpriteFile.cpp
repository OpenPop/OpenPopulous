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

#include <iostream>
#include <fstream>
#include "SpriteFile.h"

using namespace std;
using namespace Graphics;

const uint32 SpriteFileMagicNumber = 0x42465350;

SpriteFile::SpriteFile(string filename)
{
	ifstream fs;
	fs.open(filename.c_str(), ios::binary);

	fs.seekg(0, ios::end);
	sint32 size = fs.tellg();
	fs.seekg(0, ios::beg);

	mBuffer = new sint8[size];
	
	fs.read((char*)mBuffer, size);

	fs.close();

	if (*((uint32*)&mBuffer[0]) != SpriteFileMagicNumber) {
		return;
	}

	mSprites = ((sint32*)mBuffer)[1];
	mWidths = new uint16[mSprites];
	mHeights = new uint16[mSprites];
	mOffsets = new uint32[mSprites];

	sint32 pos = 8;
	for (uint32 i = 0; i < mSprites; i++) {
		mWidths[i] = *((short*)&mBuffer[pos]); pos += 2;
		mHeights[i] = *((short*)&mBuffer[pos]); pos += 2;
		mOffsets[i] = *((sint32*)&mBuffer[pos]); pos += 4;
	}
}

SpriteFile::~SpriteFile()
{
}
