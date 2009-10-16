#include <sdl/sdl.h>

#include "Input.h"
#include "OpenPop.h"

void CheckInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				QuitGame();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						QuitGame();
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
		}
	}
}