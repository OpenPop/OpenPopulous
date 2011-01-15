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

#include "Graphics\Renderer.h"
#include "Widgets\Screen.h"
#include "Menus\MainMenu.h"
#include "OpenPop.h"

using namespace Graphics;
using namespace Widgets;

OpenPop::OpenPop()
{
	mLastTick = 0;
	mFrameRate = 0;
	mCurrentScreen = new MainMenu(this);
}

OpenPop::~OpenPop()
{
	if (mRenderer != NULL)
		delete mRenderer;
}

int OpenPop::Init()
{
	mRenderer = new Renderer();
	mRenderer->hWnd = hWnd;
	
	if (!mRenderer->Init())
		return 0;

	return 1;
}

void OpenPop::Run()
{
	int currentTick = GetTickCount();
	int difference = currentTick - mLastTick;
	if (difference == 0)
		difference = 1;

	mFrameRate = 1000 / difference;
	mLastTick = currentTick;

	char buf[50];
	sprintf(buf, "Frame rate: %i", mFrameRate);
	SetWindowText(hWnd, buf);

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

void OpenPop::MouseMove(int x, int y)
{
	if (mCurrentScreen != NULL) {
		mCurrentScreen->MouseMove(x, y);
	}
}