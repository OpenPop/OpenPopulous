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

#ifndef _GAME_PANEL_H_
#define _GAME_PANEL_H_

#include <list>

class OpenPop;

namespace Graphics
{
	class Renderer;
	class PaletteFile;
}

namespace Game
{
class SpellButton;

class Panel
{
public:
	OpenPop*				mOpenPop;
	Graphics::PaletteFile*	mPaletteFile;

	sint32					mX;
	sint32					mY;
	sint32					mWidth;
	sint32					mHeight;

	std::list<SpellButton*>		mSpellButtons;

	Panel(OpenPop* openPop);
	~Panel();

	void SetupSpellButtons();
	void RemoveSpellButtons();

	virtual void Update();
	virtual void Draw(Graphics::Renderer* renderer);

};

}

#endif