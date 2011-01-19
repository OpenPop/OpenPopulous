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

#ifndef _LANGUAGE_LANGUAGE_H_
#define _LANGUAGE_LANGUAGE_H_

#include <string>

namespace Languages
{

class Language
{
public:
	Language(std::string filename);
	~Language();

	std::string GetText(uint32 index);

private:
	char16*			mBuffer;
	uint32*			mOffsets;
};

}

#endif