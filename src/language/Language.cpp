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

#include <windows.h>
#include <iostream>
#include <fstream>
#include "Language.h"

using namespace std;
using namespace Languages;

Language::Language(string filename)
{
	ifstream fs;
	fs.open(filename.c_str(), ios::binary);

	fs.seekg(0, ios::end);
	sint32 size = fs.tellg();
	fs.seekg(0, ios::beg);

	mBuffer = (char16*)(new sint8[size]);
	
	fs.read((char8*)mBuffer, size);

	fs.close();

	//Read offsets
	mOffsets = new uint32[1400];
	mOffsets[0] = 0;
	int index = 1;
	for (uint32 i = 0; i < size / 2; i++) {
		if (mBuffer[i] == 0) {
			mOffsets[index] = i+1;
			index++;
		}
	}
}

Language::~Language()
{

}

string Language::GetText(uint32 index)
{
	string rtn_str;
	char16* str = &mBuffer[mOffsets[index]];

	for (int i = 0; i < lstrlenW(str); i++) {
		rtn_str += str[i];
	}

	return rtn_str;
}