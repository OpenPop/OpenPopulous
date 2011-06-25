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

#ifndef _GAME_SPELLTYPE_H_
#define _GAME_SPELLTYPE_H_

#include "..\stdafx.h"

namespace Game
{
	enum SPELL_TYPES
	{
		SPELL_BLAST,
		SPELL_LIGHTNING,
		SPELL_TORNADO,
		SPELL_SWARM,
		SPELL_INVISIBILITY,
		SPELL_HYPNOTISE,
		SPELL_FIRESTORM,
		SPELL_GHOSTARMY,
		SPELL_ERODE,
		SPELL_SWAMP,
		SPELL_LANDBRIDGE,
		SPELL_ANGELOFDEATH,
		SPELL_EARTHQUAKE,
		SPELL_FLATTEN,
		SPELL_VOLCANO,
		SPELL_CONVERT,
		SPELL_ARMAGEDDON,
		SPELL_SHIELD,
		SPELL_BLOODLUST,
		SPELL_TELEPORT,
		SPELL_COUNT,
	};

	struct SpellDefinition
	{
		uint32 Range;
		uint32 ManaCost;
		uint8 MaxShots;
	};

	extern SpellDefinition SpellDefs[SPELL_COUNT];

	void InitSpellDefs();
}

#endif