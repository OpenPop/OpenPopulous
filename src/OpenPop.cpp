
#include <windows.h>

#include "Game.h"
#include "Input.h"
#include "OpenPop.h"
#include "Sprites.h"
#include "Video.h"
#include "Language.h"

#define SCREEN_WIDTH	800								// We want our screen width 800 pixels
#define SCREEN_HEIGHT	600								// We want our screen height 600 pixels
#define SCREEN_DEPTH	32								// We want 32 bits per pixel

int pressed_button;

//Ted's ////////////////////////////////////

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