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
#include "RawFile.h"

using namespace std;
using namespace Graphics;

RawFile::RawFile(string filename, sint32 width, sint32 height)
{
	mWidth = width;
	mHeight = height;

	mBuffer = new sint8[width * height];

	ifstream fs;
	fs.open(filename.c_str(), ios::binary);

	for (sint32 y = 0; y < mHeight; y++) {
		for (sint32 x = 0; x < mWidth; x++) {
			fs.read((char*)&mBuffer[y * mWidth + x], sizeof(sint8));
		}
	}

	fs.close();
}