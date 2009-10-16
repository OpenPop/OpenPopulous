
#include <windows.h>

#include "Game.h"
#include "Input.h"
#include "OpenPop.h"
#include "Sprites.h"
#include "Video.h"
#include "Language.h"

int pressed_button;

bool ready_to_quit;

void Initialization()
{
	InitVideo();

	//Load sprites
	LoadLanguage();
	Sprites::LoadSpriteCollections();

	gGame = new Game();
}

void GameLoop()
{
	Uint32 last_tick = SDL_GetTicks();

	ready_to_quit = false;

	while (!ready_to_quit) {
		CheckInput();

		if (SDL_GetTicks() > last_tick + 70) {
			last_tick = SDL_GetTicks();

			gGame->Update();

			Draw();
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

int StartOpenPop()
{
	Initialization();
	GameLoop();
	Deinitalization();

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return StartOpenPop();
}