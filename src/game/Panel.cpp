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

#include "SpellButton.h"
#include "Panel.h"

using namespace std;
using namespace Game;
using namespace Graphics;

Panel::Panel(OpenPop* openpop)
{
	mOpenPop = openpop;

	mPaletteFile = new PaletteFile(gConfig->GetPopFile("Data\\pal0-a.dat"));

	SetupSpellButtons();
}

Panel::~Panel()
{

}

void Panel::SetupSpellButtons()
{
	sint32 i = 0;
	for (sint32 y = 0; y < 6; y++) {
		for (sint32 x = 0; x < 3; x++) {
			sint32 dx = 1 + (32 * x);
			sint32 dy = 211 + (44 * y);

			SpellButton* btn = new SpellButton(mOpenPop);
			btn->mPaletteFile = mPaletteFile;
			btn->mSpellIDX = i;
			btn->mX = dx;
			btn->mY = dy;
			btn->mWidth = 31;
			btn->mHeight = 43;

			mSpellButtons.push_back(btn);

			i++;
		}
	}
}

void Panel::RemoveSpellButtons()
{
	list<SpellButton*>::iterator it;

	for (it = mSpellButtons.begin(); it != mSpellButtons.end(); it++) {
		SpellButton* sb = *it;

		delete sb;
	}

	mSpellButtons.clear();
}

void Panel::Update()
{

}

void Panel::Draw(Renderer* renderer)
{
	PaletteFile* pal = mPaletteFile;
	SpriteFile* hfx = mOpenPop->mSpriteFileManager->mHFX;

	//Minimap
	renderer->DrawSprite(pal, hfx, 690, 0, 0);
	renderer->DrawSprite(pal, hfx, 691, 50, 0);
	renderer->DrawSprite(pal, hfx, 692, 0, 49);
	renderer->DrawSprite(pal, hfx, 693, 50, 49);

	renderer->DrawSprite(pal, hfx, HFX_SPRITE_MINIMAP_BACKGROUND, 0, 98);
	renderer->DrawSprite(pal, hfx, HFX_SPRITE_MINIMAP_BACKGROUND, 68, 98);

	//Shaman area
	renderer->DrawBox(pal, hfx, 0, 109, 100, 70, HFX_SPRITE_PANEL_1_NW, HFX_SPRITE_PANEL_1_N, HFX_SPRITE_PANEL_1_NE, HFX_SPRITE_PANEL_1_E, HFX_SPRITE_PANEL_1_C, HFX_SPRITE_PANEL_1_W, -1, -1, -1);

	//Tab buttons
	renderer->DrawBox(pal, hfx, 3, 85, 32, 27, HFX_SPRITE_TAB_BACK_NW);
	renderer->DrawBox(pal, hfx, 33, 85, 32, 27, HFX_SPRITE_TAB_FRONT_NW);
	renderer->DrawBox(pal, hfx, 63, 85, 32, 27, HFX_SPRITE_TAB_BACK_NW);

	renderer->DrawSprite(pal, hfx, HFX_SPRITE_TAB_BUILDINGS, 7, 90);
	renderer->DrawSprite(pal, hfx, HFX_SPRITE_TAB_SPELLS, 37, 90);
	renderer->DrawSprite(pal, hfx, HFX_SPRITE_TAB_UNITS, 68, 90);

	//Mini globe
	renderer->DrawBox(pal, hfx, 5, 122, 22, 18, HFX_SPRITE_PANEL_3_NW);
	renderer->DrawSprite(pal, hfx, HFX_SPRITE_MINIGLOBE_OFF, 8, 122);

	//Shaman
	renderer->DrawBox(pal, hfx, 32, 113, 30, 35, HFX_SPRITE_PANEL_3_NW);
	renderer->FillRect(0, 34, 115, 25, 30);

	//Shaman Health
	renderer->DrawBox(pal, hfx, 63, 126, 10, 21, HFX_SPRITE_HEALTH_NW);
	renderer->FillRect(0xFFFFFF, 65, 128, 6, 17);

	//Help button
	renderer->DrawBox(pal, hfx, 63, 113, 13, 12, HFX_SPRITE_SMALL_PANEL_NW);

	//Tribe icons
	renderer->DrawBox(pal, hfx, 77, 113, 20, 11, HFX_SPRITE_RED_ENEMY_ICON_NW);
	renderer->DrawBox(pal, hfx, 77, 126, 20, 11, HFX_SPRITE_YELLOW_ENEMY_ICON_NW);
	renderer->DrawBox(pal, hfx, 77, 138, 20, 11, HFX_SPRITE_GREEN_ENEMY_ICON_NW);

	//Units panel
	renderer->DrawBox(pal, hfx, 0, 150, 100, 70, HFX_SPRITE_PANEL_1_NW, HFX_SPRITE_PANEL_1_N, HFX_SPRITE_PANEL_1_NE, HFX_SPRITE_PANEL_1_E, HFX_SPRITE_PANEL_1_C, HFX_SPRITE_PANEL_1_W, -1, -1, -1);

	renderer->DrawBox(pal, hfx, 0, 152, 15, 36, HFX_SPRITE_SMALL_PANEL_NW);
	renderer->DrawBox(pal, hfx, 4, 156, 7, 22, HFX_SPRITE_HEALTH_NW);

	renderer->DrawBox(pal, hfx, 15, 152, 15, 36, HFX_SPRITE_SMALL_PANEL_NW);
	renderer->DrawSprite(pal, hfx, HFX_SPRITE_BUTTON_UNIT_BRAVE, 16, 155);

	renderer->DrawBox(pal, hfx, 90, 31, 152, 15, 36, HFX_SPRITE_SMALL_PANEL_NW);
	renderer->DrawBox(pal, hfx, 90, 47, 152, 15, 36, HFX_SPRITE_SMALL_PANEL_NW);
	renderer->DrawBox(pal, hfx, 90, 63, 152, 15, 36, HFX_SPRITE_SMALL_PANEL_NW);
	renderer->DrawBox(pal, hfx, 90, 80, 152, 15, 36, HFX_SPRITE_SMALL_PANEL_NW);

	//Mana bar
	renderer->DrawBox(pal, hfx, 3, 190, 92, 12, HFX_SPRITE_HEALTH_NW);
	renderer->FillRect(0, 5, 192, 88, 8);

	//Tab panel
	renderer->DrawBox(pal, hfx, 0, 204, 100, 272, HFX_SPRITE_PANEL_2_NW, HFX_SPRITE_PANEL_2_N, HFX_SPRITE_PANEL_2_NE, HFX_SPRITE_PANEL_2_E, HFX_SPRITE_PANEL_2_C, HFX_SPRITE_PANEL_2_W, -1, -1, -1);

	list<SpellButton*>::iterator it;
	for (it = mSpellButtons.begin(); it != mSpellButtons.end(); it++) {
		SpellButton* sb = *it;
		sb->Draw(renderer);
	}
}