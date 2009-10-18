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

#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "Map.h"

class Game
{
public:
	Map		*mMap;
	Player	*mPlayer[MAX_PLAYERS];

	unsigned int TRIBECOL_NEUTRAL;
	unsigned int TRIBECOL_BLUE;
	unsigned int TRIBECOL_RED;
	unsigned int TRIBECOL_YELLOW;
	unsigned int TRIBECOL_GREEN;

	enum TRIBES{
		TRIBE_BLUE,
		TRIBE_RED,
		TRIBE_YELLOW,
		TRIBE_GREEN,
	};

public:
	Game();
	~Game();

	void LoadMap(char *filename);
	void LoadNewMapFormat(char *buffer, int length);
	void LoadOldMapFormat(char *buffer, int length);

	void Update();
};

extern Game* gGame;

#endif