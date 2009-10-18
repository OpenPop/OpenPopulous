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

#include "Unit.h"
#include "OpenPop.h"
#include "Graphics.h"

Unit::Unit(int type)
{
	mType = type;
}

Unit::~Unit()
{

}

void Unit::ClearInstructions()
{

}

void Unit::AddInstruction(UnitInstruction instruction)
{
	
}

void Unit::Draw()
{
	for (int y = 0; y <= scale; y++) {
			for (int x = 0; x <= scale; x++) {
				unsigned int colour;
	
				if(mTribe == gGame->TRIBE_BLUE){
					colour = gGame->TRIBECOL_BLUE; 
				}else if(mTribe == gGame->TRIBE_RED){
					colour = gGame->TRIBECOL_RED; 
				}else if(mTribe == gGame->TRIBE_YELLOW){
					colour = gGame->TRIBECOL_YELLOW; 
				}else if(mTribe == gGame->TRIBE_GREEN){
					colour = gGame->TRIBECOL_GREEN; 
				}else{
					colour = gGame->TRIBECOL_NEUTRAL;
				}

				Graphics::DrawPixel((mX * scale) + x, (obj->mZ * scale) + y, colour);
		}
	}
}

void Unit::Update()
{
	if (mType == UNIT_WILDMAN) {
		// TODO: Do random stuff here?
	}
}