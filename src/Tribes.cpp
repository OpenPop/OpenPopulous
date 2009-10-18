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

#include "Tribes.h"
#include "Sprites.h"

void Tribes::LoadTribeCols(){
	Tribes::TRIBECOL_NEUTRAL = Sprites::pal -> entry [175 + (8 * 0) + 5]; // neutral tribe starts at 175
	Tribes::TRIBECOL_BLUE    = Sprites::pal -> entry [215 + (8 * 0) + 5]; // other tribes start at 215
	Tribes::TRIBECOL_RED     = Sprites::pal -> entry [215 + (8 * 3) + 5]; // 3 = 3rd tribe
	Tribes::TRIBECOL_YELLOW  = Sprites::pal -> entry [215 + (8 * 2) + 5]; // 5 = entry in gradient
	Tribes::TRIBECOL_GREEN   = Sprites::pal -> entry [215 + (8 * 1) + 5];
}