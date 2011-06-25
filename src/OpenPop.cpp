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

#include "stdafx.h"

#include "Graphics\Renderer.h"
#include "Graphics\SpriteFileManager.h"
#include "Widgets\Screen.h"
#include "Menus\MainMenu.h"
#include "Language\Language.h"
#include "Config.h"
#include "OpenPop.h"

#include "game\GameHost.h"
#include "game\Spell_Type.h"
#include "game\GameScreen.h"
#include "menus\PreGameLobby.h"

using namespace Graphics;
using namespace Widgets;
using namespace Menus;
using namespace Languages;

OpenPop::OpenPop()
{
	mLastTick = 0;
	mFrameRate = 0;
	mOpenPopTickCount = 0;

	mSpriteFileManager = new SpriteFileManager();
	mCurrentLanguage = new Language(gConfig->GetPopFile("language\\lang00.dat"));

	Game::InitSpellDefs();

	mGameHost = new Game::GameHost(this);

	mChangeScreen = NULL;
	//mCurrentScreen = new MainMenu(this);
	//mCurrentScreen = new PreGameLobby(this);
	mCurrentScreen = new Game::GameScreen(this);
}

OpenPop::~OpenPop()
{
	if (mRenderer != NULL)
		delete mRenderer;
}

sint32 OpenPop::Init()
{
	mRenderer = new Renderer();
	mRenderer->hWnd = hWnd;
	
	if (!mRenderer->Init())
		return 0;

	return 1;
}

void OpenPop::Run()
{
	mOpenPopTickCount++;

	sint32 currentTick = GetTickCount();
	sint32 difference = currentTick - mLastTick;
	if (difference == 0)
		difference = 1;

	mFrameRate = 1000 / difference;
	mLastTick = currentTick;

	if (mOpenPopTickCount % 10 == 0) {
		char buf[50];
		sprintf(buf, "Frame rate: %i", mFrameRate);
		SetWindowText(hWnd, buf);
	}

	if (mChangeScreen != NULL) {
		delete mCurrentScreen;
		mCurrentScreen = mChangeScreen;
		mChangeScreen = NULL;
	}

	Draw();
}

void OpenPop::Draw()
{
	mRenderer->StartDraw();

	if (mCurrentScreen != NULL) {
		mCurrentScreen->Draw(mRenderer);
	}

	mRenderer->EndDraw();
}

void OpenPop::Close()
{
	if (mRenderer != NULL)
		mRenderer->Close();
}

std::string OpenPop::GetText(uint32 index)
{
	return mCurrentLanguage->GetText(index);
}

void OpenPop::ChangeScreen(Screen* screen)
{
	mChangeScreen = screen;
}

void OpenPop::MouseMove(sint32 x, sint32 y)
{
	if (mCurrentScreen != NULL) {
		mCurrentScreen->MouseMove(x, y);
	}
}

void OpenPop::MouseDown(sint32 button, sint32 x, sint32 y)
{
	if (mCurrentScreen != NULL) {
		mCurrentScreen->MouseDown(button, x, y);
	}
}