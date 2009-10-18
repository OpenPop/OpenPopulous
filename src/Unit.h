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

#ifndef _UNIT_H_
#define _UNIT_H_

#include <vector>

#include "Object.h"

//These are the types of instructions that units can have
enum INSTRUCTIONS
{
	INSTRUCTION_CAST_SPELL,			//Shaman: Cast spell (spell prob. be in player class)
	INSTRUCTION_MOVE,				//Move to the specified x, y
	INSTRUCTION_OBJECT_ACTION,		//The default action for the specified object
};

//Structure for a single unit instruction
struct UnitInstruction
{
	int action;
	float x, y;				//Used for walk commands
	Object *object;			//Used for object commands (E.g. Cut tree, attack unit/building)
};

typedef std::vector<UnitInstruction> InstructionList;

enum UNIT_TYPES
{
	UNIT_WILDMAN = 1,
	UNIT_BRAVE,
	UNIT_WARRIOR,
	UNIT_PREACHER,
	UNIT_FIREWARRIOR,
	UNIT_SPY,
	UNIT_SHAMAN,
	UNIT_AOD, // Angel of Death
};

enum UNIT_FLAGS
{
	UNIT_IDLE,
	UNIT_PATROLLING,
	UNIT_ATTACKING,
	UNIT_DEAD,
	UNIT_GHOST,
	UNIT_SHIELDED,
	UNIT_INVISIBLE,
};

//The unit class which will be inherited by unit type classes
class Unit : public Object
{
public:
	int					mFlags;
	int					mGhostTime;			//How long before the ghost disappears (game turns)	
	int					mInvisibleTime;		//How long the unit's invisibillity has left (game turns)
	int					mShieldTime;		//How long the unit's shield has left (game turns)
	int					mHealth;			//The unit's health
	int					mMaxHealth;			//The unit's maximum health
	int					mStrength;			//How good the unit is in combat
	int					mManaProduceAmount;	//How much mana they produce
	int					mSpeed;				//How fast the unit walks
	InstructionList		mInstructions;		//The unit's instruction line

public:
	Unit(int type);
	~Unit();

	void Draw();
	void Update();

	void ClearInstructions();
	void AddInstruction(UnitInstruction instruction);

	//Pathfinding
};

typedef std::vector<Unit*> UnitList;

#endif
