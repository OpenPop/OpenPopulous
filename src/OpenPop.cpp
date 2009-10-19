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
	LoadLanguage();
	Sprites::LoadSpriteCollections();
	gGame = new Game();
	InitVideo();
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