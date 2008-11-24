#include <windows.h>

#include "Input.h"
#include "OpenPop.h"
#include "Sprites.h"
#include "Video.h"

bool ready_to_quit;

void Initialization()
{
	InitVideo();

	//Load sprites
	LoadSpriteCollections();
}

void GameLoop()
{
	Uint32 last_tick = SDL_GetTicks();

	ready_to_quit = false;

	while (!ready_to_quit) {
		CheckInput();

		if (SDL_GetTicks() > last_tick + 70) {
			last_tick = SDL_GetTicks();

			TestDraw();
		}
	}
}

void Deinitalization()
{
	
}

void QuitGame()
{
	ready_to_quit = true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Initialization();
	GameLoop();
	Deinitalization();
}

//#include <cstdio>
//
//#include "Language.h"
//#include "Sprites.h"
//
//int main()
//{
//	LoadLanguage();
//	LoadSpriteCollections();
//
//	for (int i = 0; i < 1000; i++) {
//		wprintf(L"%d. %s\n", i, GetString(i));
//	}
//
//	return 0;
//}