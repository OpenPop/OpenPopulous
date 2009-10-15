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

#ifndef _SPELL_H_
#define _SPELL_H_

//Building types
enum SPELL
{
	//Normal spells
	SPELL_BLAST				=	2^0,
	SPELL_CONVERT			=	2^1,
	SPELL_GHOST_ARMY		=	2^2,
	SPELL_SWARM				=	2^3,
	SPELL_INVISIBILLITY		=	2^4,
	SPELL_MAGICAL_SHIELD	=	2^5,
	SPELL_LANDBRIDGE		=	2^6,
	SPELL_LIGHTNING			=	2^7,
	SPELL_HYPNOTISE			=	2^8,
	SPELL_TORNADO			=	2^9,
	SPELL_SWAMP				=	2^10,
	SPELL_FLATTEN			=	2^11,
	SPELL_EARTHQUAKE		=	2^12,
	SPELL_ERODE				=	2^13,
	SPELL_FIRESTORM			=	2^14,
	SPELL_ANGEL_OF_DEATH	=	2^15,
	SPELL_VOLCANO			=	2^16,

	//Guest spells
	SPELL_BLOODLUST			=	2^17,
	SPELL_ARMAGEDDON		=	2^18,
	SPELL_TELEPORT			=	2^19,

	//Forge world spells
	SPELL_HILL				=	2^20,
	SPELL_VALLEY			=	2^21,
	SPELL_RAISE				=	2^22,
	SPELL_LOWER				=	2^23,
	SPELL_WILDMEN			=	2^24,
	SPELL_TREES				=	2^25,

	MAX_SPELLS				=	26,
};

struct SPELL_INFO
{
	unsigned int	mana;
	unsigned char	max_shots;
	unsigned int	range;
}

//Spell info constants
const spell_attribs[] = 
{
	{10000,		4,		3072},		//Blast
	{10000,		4,		8192},		//Convert
	{18000,		4,		4096},		//Ghost Army
	{40000,		4,		6144},		//Swarm
	{50000,		4,		4096},		//Invisibillity
	{60000,		4,		4096},		//Magical Shield
	{70000,		4,		5120},		//Landbridge
	{80000,		4,		6144},		//Lightning
	{85000,		3,		4096},		//Hypnotise
	{90000,		3,		4096},		//Tornado
	{100000,	3,		4096},		//Swamp
	{125000,	3,		4096},		//Flatten
	{175000,	2,		4096},		//Earthquake
	{210000,	2,		4096},		//Erode
	{400000,	2,		4096},		//Firestorm
	{510000,	1,		3072},		//Angel of Death
	{800000,	1,		3072},		//Volcano
	{1000000,	4,		4096},		//Bloodlust
	{1000000,	1,		8192},		//Armageddon
	{1000000,	4,		0},			//Teleport
	{80000,		4,		4096},		//Hill
	{80000,		4,		4096},		//Valley
	{100000,	4,		4096},		//Raise
	{100000,	4,		4096},		//Lower
	{80000,		4,		4096},		//Wildmen
	{80000,		4,		4096},		//Trees
};

struct SpellAvailability
{
	int Spells;

	inline void SetSpell(SPELL s, bool state)
	{
		if (state)
			Spells |= s;
		else
			Spells &= ~s;
	}

	inline bool IsSpellOn(SPELL s)
	{
		return (Spells & s);
	}
};

struct SpellStatus
{
	SpellAvailability	AvailableSpells;
	SpellAvailability	ChargingSpells;
	char				SpellShots[MAX_SPELLS];
	short				SpellCharge[MAX_SPELLS];
};

#endif