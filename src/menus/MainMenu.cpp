#include "..\OpenPop.h"
#include "..\Graphics\Renderer.h"
#include "..\Graphics\Surface.h"
#include "..\Graphics\PaletteFile.h"
#include "..\Graphics\RawFile.h"
#include "..\Widgets\Screen.h"
#include "MainMenu.h"

using namespace Graphics;
using namespace Widgets;

PaletteFile* pal;
RawFile* raw;

MainMenu::MainMenu(OpenPop* openpop) :
	Screen(openpop)
{
	pal = new PaletteFile("C:\\Program Files\\Bullfrog\\Populous\\Data\\fenew\\fepal0.dat");
	raw = new RawFile("C:\\Program Files\\Bullfrog\\Populous\\Data\\fenew\\febackg0.dat", 640, 480);
}

MainMenu::~MainMenu()
{
}

void MainMenu::Draw(Renderer *renderer)
{
	Surface* surface = new Surface(renderer);
	surface->mWidth = 640;
	surface->mHeight = 480;
	surface->Init();

	//surface->Clear(D3DCOLOR_XRGB(255, 0, 0));
	surface->DrawRAW(pal, raw, 0, 0);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 800;
	rect.bottom = 600;
	renderer->BlitSurface(surface, rect);
}