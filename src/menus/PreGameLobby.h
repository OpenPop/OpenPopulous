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

#ifndef _MENUS_PREGAMELOBBY_H_
#define _MENUS_PREGAMELOBBY_H_

class OpenPop;

namespace Graphics {
	Renderer;
	Font;
}

namespace Widgets {
	class Screen;
	class Widget;
	class TextLink;
}

namespace Menus
{

class PreGameLobby :
	public Widgets::Screen
{
public:
	PreGameLobby(OpenPop* openpop);
	~PreGameLobby();

	void Draw(Graphics::Renderer *renderer);

private:
	Graphics::Font*		mTextLinkFont;
	Graphics::Font*		mTextLinkHighlightFont;
	Graphics::Font*		mTextLinkShadowFont;
	Graphics::Font*		mLargeTextFont;
	Graphics::Font*		mSmallTextFont;

	Graphics::SpriteFile*	mTestSpritesS;
	Graphics::SpriteFile*	mTestSpritesA;

	Widgets::TextLink*	mBackLink;

	void MouseDown(Widgets::Widget* widget, sint32 button, sint32 x, sint32 y);
};

}

#endif