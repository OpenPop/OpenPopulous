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

#include "..\OpenPop.h"
#include "..\Config.h"
#include "..\Graphics\Renderer.h"
#include "..\Graphics\PaletteFile.h"
#include "..\Graphics\SpriteFile.h"
#include "..\Graphics\SpriteFileManager.h"
#include "..\Widgets\Screen.h"

#include "..\Graphics\HFX_Defs.h"

#include "GameHost.h"
#include "Tribe.h"
#include "Spell_Type.h"
#include "Spell.h"
#include "SpellButton.h"

using namespace Game;
using namespace Graphics;

SpellButton::SpellButton(OpenPop* openpop)
{
	mOpenPop = openpop;
}

SpellButton::~SpellButton()
{

}

void SpellButton::Update()
{

}

Spell* SpellButton::GetSpell()
{
	return &(mOpenPop->mGameHost->GetLocalTribe()->mSpells[mSpellIDX]);
}

void SpellButton::Draw(Renderer* renderer)
{
	uint32 spellSpriteIdx;

	Spell* spell = GetSpell();

	mSpellShots = spell->Shots;
	mSpellMaxShots = SpellDefs[mSpellIDX].MaxShots;
	mChargeAmount = spell->Charge;
	mChargeMax = SpellDefs[mSpellIDX].ManaCost;
	mSpellRedShots = spell->PrizeShots;

	bool permenent = spell->Permenent;
	bool charging = spell->Charging;

	bool has_shot = (mSpellShots > 0);

	if (charging || has_shot)
		spellSpriteIdx = HFX_SPRITE_BUTTON_SHOT_SPELL_ARMAGEDDON + mSpellIDX;
	else
		spellSpriteIdx = HFX_SPRITE_BUTTON_SPELL_BLAST + mSpellIDX;

	PaletteFile* pal = mPaletteFile;
	SpriteFile* hfx = mOpenPop->mSpriteFileManager->mHFX;

	if (permenent || has_shot) {
		renderer->DrawBox(pal, hfx, mX, mY, mWidth, mHeight, (permenent ? HFX_SPRITE_SPELL_BUTTON_NW : HFX_SPRITE_SPELL_BUTTON_TEMPORARY_NW));

		//Spell image
		sint32 w = hfx->mWidths[spellSpriteIdx];
		sint32 h = hfx->mHeights[spellSpriteIdx];
		renderer->DrawSprite(pal, hfx, spellSpriteIdx, mX + (mWidth / 2) - (w / 2), mY + (mHeight / 2) - (h / 2));

		//Shots
		uint32 shotGap = 1;
		if (mSpellMaxShots == 1)
			shotGap = 0;
		else if (mSpellMaxShots == 2)
			shotGap = 3;

		uint32 shotLineWidth = (mSpellMaxShots * 4) + (mSpellMaxShots * shotGap);
		uint32 shotLineStartX = (mWidth / 2) - (shotLineWidth / 2);

		for (sint32 i = 0; i < mSpellMaxShots; i++) {
			sint32 dx = mX + shotLineStartX + (i * 4) + (i * shotGap);
			sint32 dy = mY + 2;

			if (mSpellShots > i) {
				if (mSpellRedShots > i)
					renderer->DrawSprite(pal, hfx, HFX_SPRITE_SPELL_SHOT_RED, dx, dy);
				else
					renderer->DrawSprite(pal, hfx, HFX_SPRITE_SPELL_SHOT_BLUE, dx, dy);
			} else {
				if (permenent)
					renderer->DrawSprite(pal, hfx, HFX_SPRITE_SPELL_SHOT_EMPTY, dx, dy);
				else
					renderer->DrawSprite(pal, hfx, HFX_SPRITE_SPELL_SHOT_EMPTY_TEMP, dx, dy);
			}
		}

		//Charging
		if (charging) {
			renderer->DrawBox(pal, hfx, mX + 2, mY + 34, 26, 5, HFX_SPRITE_HEALTH_NW);

			renderer->FillRect(renderer->SwapColourBits(mPaletteFile->mColours[153]), mX + 3, mY + 35, 24, 3);

			uint32 chargeWidth = ((real32)mChargeAmount / (real32)mChargeMax) * (real32)24;
			renderer->FillRect(renderer->SwapColourBits(mPaletteFile->mColours[221]), mX + 3, mY + 35, chargeWidth, 3);
		}
	} else {
		renderer->DrawBox(pal, hfx, 100, mX, mY, mWidth, mHeight, HFX_SPRITE_SPELL_BUTTON_NW, HFX_SPRITE_SPELL_BUTTON_NW + 4, HFX_SPRITE_SPELL_BUTTON_NW + 1, HFX_SPRITE_SPELL_BUTTON_NW + 6, -1, HFX_SPRITE_SPELL_BUTTON_NW + 7, HFX_SPRITE_SPELL_BUTTON_NW + 2, HFX_SPRITE_SPELL_BUTTON_NW + 5, HFX_SPRITE_SPELL_BUTTON_NW + 3);
	}
}