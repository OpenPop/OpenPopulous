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
#include "..\Graphics\Renderer.h"
#include "..\Graphics\Surface.h"
#include "..\Graphics\PaletteFile.h"
#include "..\Graphics\RawFile.h"
#include "..\Graphics\SpriteFile.h"
#include "..\Graphics\Font.h"
#include "..\Widgets\Screen.h"
#include "..\Widgets\Widget.h"
#include "..\Widgets\TextLink.h"
#include "MainMenu.h"

using namespace Graphics;
using namespace Widgets;

MainMenu::MainMenu(OpenPop* openpop) :
	Screen(openpop)
{
	std::string popdir = "C:\\Program Files\\Bullfrog\\Populous\\";

	mPalette = new PaletteFile(popdir + "Data\\fenew\\fepal0.dat");
	mBackground = new RawFile(popdir + "Data\\fenew\\febackg0.dat", 640, 480);

	mLargeTextFont = new Font(popdir + "Data\\fenew\\Felo33WE.spr", popdir + "Data\\fenew\\fepal0.dat");
	mSmallTextFont = new Font(popdir + "Data\\fenew\\Felo20WE.spr", popdir + "Data\\fenew\\fepal0.dat");
	mTextLinkFont = new Font(popdir + "Data\\fenew\\Feft33WE.spr", popdir + "Data\\fenew\\fepal0.dat");
	mTextLinkHighlightFont = new Font(popdir + "Data\\fenew\\Fehi33WE.spr", popdir + "Data\\fenew\\fepal0.dat");
	mTextLinkShadowFont = new Font(popdir + "Data\\fenew\\Fesd33WE.spr", "");

	SetMenuMain();
}

MainMenu::~MainMenu()
{
}

void MainMenu::Draw(Renderer *renderer)
{
	Screen::Draw(renderer);

	std::string items[] = { "OpenPop", "Single Player", "Multiplayer", "Map Editor" };
	std::string title = items[mMenuType];
	sint32 x = (640 / 2) - (mLargeTextFont->MeasureString(title) / 2);
	renderer->DrawString(mLargeTextFont, title, x, 40);

	if (mMenuType == 0) {
		std::string szVersion = std::string(_openpop_title) + " " + _openpop_revision + " @ " + _openpop_build_date;
		renderer->DrawString(mSmallTextFont, szVersion, 2, 460);
	}
}

void MainMenu::SetMenu(std::string* items, int numItems)
{
	uint32 menuSpacing = 10;
	uint32 ymenuHeight = (numItems * mTextLinkFont->GetHeight()) + (numItems * menuSpacing);
	uint32 ystart = (480 / 5 * 3) - (ymenuHeight / 2);

	for (uint32 i = 0; i < numItems; i++) {
		TextLink* w = new TextLink();
		w->mID = i;
		w->mFont = mTextLinkFont;
		w->mHighlightFont = mTextLinkHighlightFont;
		w->mShadowFont = mTextLinkShadowFont;
		w->mText = items[i];
		w->AutoSize();

		w->mX = (640 / 2) - (w->mWidth / 2);
		w->mY = ystart + (i * mTextLinkFont->GetHeight()) + (i * menuSpacing);

		AddWidget(w);
	}
}

void MainMenu::SetMenuMain()
{
	std::string items[] = { "Single Player", "Multiplayer", "Map Editor", "Options", "Rolling Demo", "Credits", "Exit" };
	SetMenu(items, sizeof(items) / sizeof(items[0]));

	mMenuType = 0;
}

void MainMenu::SetMenuSP()
{
	std::string items[] = { "Tutorial", "The Beginning", "Undiscovered Worlds", "Skirmish", "Load Game", "Back" };
	SetMenu(items, sizeof(items) / sizeof(items[0]));

	mMenuType = 1;
}

void MainMenu::SetMenuMP()
{
	std::string items[] = { "Play Online", "Host Address", "Local Area Network", "Back" };
	SetMenu(items, sizeof(items) / sizeof(items[0]));

	mMenuType = 2;
}

void MainMenu::SetMenuME()
{
	std::string items[] = { "Create New Map", "Edit Map", "Back" };
	SetMenu(items, sizeof(items) / sizeof(items[0]));

	mMenuType = 3;
}

void MainMenu::MouseDown(Widget* widget, sint32 button, sint32 x, sint32 y)
{
	WidgetContainer::MouseDown(widget, button, x, y);

	if (widget->mID == 0 && mMenuType == 0) {
		RemoveAllWidgets();
		SetMenuSP();
	} else if (widget->mID == 1 && mMenuType == 0) {
		RemoveAllWidgets();
		SetMenuMP();
	} else if (widget->mID == 2 && mMenuType == 0) {
		RemoveAllWidgets();
		SetMenuME();
	} else if (widget->mID == 5 && mMenuType == 1) {
		RemoveAllWidgets();
		SetMenuMain();
	} else if (widget->mID == 3 && mMenuType == 2) {
		RemoveAllWidgets();
		SetMenuMain();
	} else if (widget->mID == 2 && mMenuType == 3) {
		RemoveAllWidgets();
		SetMenuMain();
	}
}