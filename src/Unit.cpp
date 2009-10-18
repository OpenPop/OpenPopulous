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
#include "Tribes.h"
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
				
				if(mTribe == Tribes::TRIBE_BLUE){
					colour = Tribes::TRIBECOL_BLUE; 
				}else if(mTribe == Tribes::TRIBE_RED){
					colour = Tribes::TRIBECOL_RED; 
				}else if(mTribe == Tribes::TRIBE_YELLOW){
					colour = Tribes::TRIBECOL_YELLOW; 
				}else if(mTribe == Tribes::TRIBE_GREEN){
					colour = Tribes::TRIBECOL_GREEN; 
				}else{
					colour = Tribes::TRIBECOL_NEUTRAL;
				}

				Graphics::DrawPixel((mX * scale) + x, (mZ * scale) + y, colour);
		}
	}
}

void Unit::Update()
{
	if (mType == UNIT_WILDMAN) {
		// TODO: Do random stuff here?
	}
}