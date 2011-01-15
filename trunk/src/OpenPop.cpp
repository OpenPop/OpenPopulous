#include "Graphics\Renderer.h"
#include "Widgets\Screen.h"
#include "Menus\MainMenu.h"
#include "OpenPop.h"

using namespace Graphics;
using namespace Widgets;

OpenPop::OpenPop()
{
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
