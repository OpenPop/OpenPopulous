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

PaletteFile* pal;
RawFile* raw;
Font* font;

MainMenu::MainMenu(OpenPop* openpop) :
	Screen(openpop)
{
	std::string popdir = "C:\\Program Files\\Bullfrog\\Populous\\";

	pal = new PaletteFile(popdir + "Data\\fenew\\fepal0.dat");
	raw = new RawFile(popdir + "Data\\fenew\\febackg0.dat", 640, 480);
	

	font = new Font(popdir + "Data\\fenew\\Felo20WE.spr", popdir + "Data\\fenew\\fepal0.dat");

	mPalette = pal;
	mBackground = raw;

	sint32 numItems = 7;
	std::string items[] = { "New Game", "Tutorial", "Load Game", "Multiplayer", "Options", "Credits", "Exit" };

	Font* f1 = new Font(popdir + "Data\\fenew\\Feft33WE.spr", popdir + "Data\\fenew\\fepal0.dat");
	Font* f2 = new Font(popdir + "Data\\fenew\\Fehi33WE.spr", popdir + "Data\\fenew\\fepal0.dat");

	sint32 menuSpacing = 10;
	sint32 ymenuHeight = (numItems * f1->GetHeight()) + (numItems * menuSpacing);
	sint32 ystart = (480 / 5 * 3) - (ymenuHeight / 2);

	for (sint32 i = 0; i < numItems; i++) {
		TextLink* w = new TextLink();
		w->mFont = new Font(popdir + "Data\\fenew\\Feft33WE.spr", popdir + "Data\\fenew\\fepal0.dat");
		w->mHighlightFont = new Font(popdir + "Data\\fenew\\Fehi33WE.spr", popdir + "Data\\fenew\\fepal0.dat");
		w->mText = items[i];
		w->AutoSize();

		w->mX = (640 / 2) - (w->mWidth / 2);
		w->mY = ystart + (i * f1->GetHeight()) + (i * menuSpacing);

		AddWidget(w);
	}
}

MainMenu::~MainMenu()
{
}

void MainMenu::Draw(Renderer *renderer)
{
	Screen::Draw(renderer);

	std::string szVersion = std::string(_openpop_title) + " " + _openpop_revision + " @ " + _openpop_build_date;
	renderer->DrawString(font, szVersion, 2, 460);
}