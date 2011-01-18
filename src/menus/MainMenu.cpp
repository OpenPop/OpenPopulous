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

	mSmallTextFont = new Font(popdir + "Data\\fenew\\Felo20WE.spr", popdir + "Data\\fenew\\fepal0.dat");
	mTextLinkFont = new Font(popdir + "Data\\fenew\\Feft33WE.spr", popdir + "Data\\fenew\\fepal0.dat");
	mTextLinkHighlightFont = new Font(popdir + "Data\\fenew\\Fehi33WE.spr", popdir + "Data\\fenew\\fepal0.dat");

	SetMenuMain();
	//SetMenuSP();
}

MainMenu::~MainMenu()
{
}

void MainMenu::Draw(Renderer *renderer)
{
	Screen::Draw(renderer);

	std::string szVersion = std::string(_openpop_title) + " " + _openpop_revision + " @ " + _openpop_build_date;
	renderer->DrawString(mSmallTextFont, szVersion, 2, 460);
}

void MainMenu::SetMenuMain()
{
	std::string items[] = { "Single Player", "Multiplayer", "Options", "Rolling Demo", "Credits", "Exit" };
	uint32 numItems = sizeof(items) / sizeof(items[0]);

	uint32 menuSpacing = 10;
	uint32 ymenuHeight = (numItems * mTextLinkFont->GetHeight()) + (numItems * menuSpacing);
	uint32 ystart = (480 / 5 * 3) - (ymenuHeight / 2);

	for (uint32 i = 0; i < numItems; i++) {
		TextLink* w = new TextLink();
		w->mID = i;
		w->mFont = mTextLinkFont;
		w->mHighlightFont = mTextLinkHighlightFont;
		w->mText = items[i];
		w->AutoSize();

		w->mX = (640 / 2) - (w->mWidth / 2);
		w->mY = ystart + (i * mTextLinkFont->GetHeight()) + (i * menuSpacing);

		AddWidget(w);
	}

	mMenuType = 0;
}

void MainMenu::SetMenuSP()
{
	std::string items[] = { "Tutorial", "The Beginning", "Undiscovered Worlds", "Skirmish", "Load Game", "Back" };
	uint32 numItems = sizeof(items) / sizeof(items[0]);

	uint32 menuSpacing = 10;
	uint32 ymenuHeight = (numItems * mTextLinkFont->GetHeight()) + (numItems * menuSpacing);
	uint32 ystart = (480 / 5 * 3) - (ymenuHeight / 2);

	for (uint32 i = 0; i < numItems; i++) {
		TextLink* w = new TextLink();
		w->mID = i;
		w->mFont = mTextLinkFont;
		w->mHighlightFont = mTextLinkHighlightFont;
		w->mText = items[i];
		w->AutoSize();

		w->mX = (640 / 2) - (w->mWidth / 2);
		w->mY = ystart + (i * mTextLinkFont->GetHeight()) + (i * menuSpacing);

		AddWidget(w);
	}

	mMenuType = 1;
}

void MainMenu::MouseDown(Widget* widget, sint32 button, sint32 x, sint32 y)
{
	WidgetContainer::MouseDown(widget, button, x, y);

	if (widget->mID == 0 && mMenuType == 0) {
		RemoveAllWidgets();
		SetMenuSP();
	} else if (widget->mID == 5 && mMenuType == 1) {
		RemoveAllWidgets();
		SetMenuMain();
	}
}