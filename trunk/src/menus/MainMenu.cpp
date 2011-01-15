#include "..\OpenPop.h"
#include "..\Graphics\Renderer.h"
#include "..\Graphics\Surface.h"
#include "..\Graphics\PaletteFile.h"
#include "..\Graphics\RawFile.h"
#include "..\Graphics\SpriteFile.h"
#include "..\Graphics\Font.h"
#include "..\Widgets\Screen.h"
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
	

	font = new Font(popdir + "Data\\fenew\\Felo33WE.spr", popdir + "Data\\fenew\\fepal0.dat");
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
	font->DrawString(surface, "OPENPOP", 200, 200);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 640;
	rect.bottom = 480;
	renderer->BlitSurface(surface, rect);
}