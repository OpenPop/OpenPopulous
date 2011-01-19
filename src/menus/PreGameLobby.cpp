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
#include "..\Language\Language.h"
#include "MainMenu.h"
#include "PreGameLobby.h"

using namespace Graphics;
using namespace Widgets;
using namespace Menus;

PreGameLobby::PreGameLobby(OpenPop* openpop) :
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

	mTestSpritesS = new SpriteFile(popdir + "Data\\fenew\\Feboxes.spr");
	mTestSpritesA = new SpriteFile(popdir + "Data\\fenew\\Feboxsp.spr");

	mBackLink = new TextLink();
	mBackLink->mFont = mTextLinkFont;
	mBackLink->mHighlightFont = mTextLinkHighlightFont;
	mBackLink->mShadowFont = mTextLinkShadowFont;
	mBackLink->mID = 0;
	mBackLink->mText = LANG(328);
	mBackLink->AutoSize();
	mBackLink->mX = (640 / 2) - (mBackLink->mWidth / 2);
	mBackLink->mY = 450;

	AddWidget(mBackLink);
}

PreGameLobby::~PreGameLobby()
{
	RemoveAllWidgets();
}

void PreGameLobby::Draw(Renderer *renderer)
{
	Screen::Draw(renderer);

	//for (int i = 0; i < mTestSpritesA->mSprites; i++)
	//	renderer->DrawSprite(mPalette, mTestSpritesS, mTestSpritesA, i, 10 * i + 10, 10);

	//for (int i = 0; i < mTestSpritesS->mSprites; i++)
	//	renderer->DrawSprite(mPalette, mTestSpritesS, i, 10 * i + 10, 100);
}

void PreGameLobby::MouseDown(Widget* widget, sint32 button, sint32 x, sint32 y)
{
	WidgetContainer::MouseDown(widget, button, x, y);

	if (widget == mBackLink) {
		mOpenPop->ChangeScreen(new MainMenu(mOpenPop));
		delete this;
	}
}