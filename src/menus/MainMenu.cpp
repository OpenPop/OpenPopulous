#include "..\OpenPop.h"
#include "..\Graphics\Renderer.h"
#include "..\Graphics\Surface.h"
#include "..\Graphics\PaletteFile.h"
#include "..\Graphics\RawFile.h"
#include "..\Graphics\SpriteFile.h"
#include "..\Widgets\Screen.h"
#include "MainMenu.h"

using namespace Graphics;
using namespace Widgets;

PaletteFile* pal;
RawFile* raw;
SpriteFile* font;

MainMenu::MainMenu(OpenPop* openpop) :
	Screen(openpop)
{
	std::string popdir = "C:\\Program Files\\Bullfrog\\Populous\\";

	pal = new PaletteFile(popdir + "Data\\fenew\\fepal0.dat");
	raw = new RawFile(popdir + "Data\\fenew\\febackg0.dat", 640, 480);
	font = new SpriteFile(popdir + "Data\\fenew\\Felo33WE.spr");
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
	surface->DrawSprite(pal, font, 47, 200, 200);		//O
	surface->DrawSprite(pal, font, 48, 217, 200);		//P
	surface->DrawSprite(pal, font, 37, 230, 200);		//E
	surface->DrawSprite(pal, font, 46, 240, 200);		//N
	surface->DrawSprite(pal, font, 48, 260, 200);		//P
	surface->DrawSprite(pal, font, 47, 273, 200);		//O
	surface->DrawSprite(pal, font, 48, 290, 200);		//P

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 640;
	rect.bottom = 480;
	renderer->BlitSurface(surface, rect);
}