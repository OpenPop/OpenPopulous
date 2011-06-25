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

#include "..\stdafx.h"

#include <d3d9.h>
#include "PaletteFile.h"
#include "RawFile.h"
#include "SpriteFile.h"
#include "Font.h"
#include "Surface.h"
#include "Renderer.h"

namespace Graphics
{

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

sint32 Renderer::Init()
{
	mD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (mD3D == NULL) {
		MessageBox(hWnd, "Error initialising Direct3D", "Error", MB_OK);
		return 0;
	}

	//Set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//Create Direct3D device
	mD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&mD3DDEV);

	if (mD3DDEV == NULL) {
		MessageBox(hWnd, "Error creating Direct3D device", "Error", MB_OK);
		return 0;
	}

	mD3DDEV->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &mBackBuffer);

	mForeground = new Surface(this);
	mForeground->mWidth = 640;
	mForeground->mHeight = 480;
	mForeground->Init();

	return 1;
}

bool Renderer::StartDraw()
{
	//Make sure the Direct3D device is valid
	if (mD3DDEV == NULL)
		return false;

	//Clear the screen with a green colour
	mD3DDEV->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);

	//Start rendering
	if (mD3DDEV->BeginScene() == S_OK) {

		if (mForeground != NULL)
			mForeground->LockBits();

		mDrawing = true;
		return true;
	}
}

void Renderer::EndDraw()
{
	if (mForeground != NULL) {
		mForeground->UnlockBits();

		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = 640;
		rect.bottom = 480;
		BlitSurface(mForeground, rect);
	}

	if (!mDrawing)
		return;

	//Stop rendering
	mD3DDEV->EndScene();

	//Display the back buffer on the screen
	mD3DDEV->Present(NULL, NULL, NULL, NULL);
}

void Renderer::Close()
{
	//Release the Direct3D device
	if (mD3DDEV != NULL)
		mD3DDEV->Release();

	//Release the Direct3D object
	if (mD3D != NULL)
		mD3D->Release();
}

sint32 Renderer::CreateSurface(LPDIRECT3DSURFACE9& surface, sint32 width, sint32 height)
{
	return mD3DDEV->CreateOffscreenPlainSurface(
		width,
		height,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);
}

void Renderer::BlitSurface(Surface* surface, RECT rect)
{
	mD3DDEV->StretchRect(surface->mD3DSurface, NULL, mBackBuffer, &rect, D3DTEXF_NONE);
}

void Renderer::FillRect(uint32 colour, sint32 x, sint32 y, sint32 w, sint32 h)
{
	mForeground->FillRect(colour, x, y, w, h);
}

void Renderer::DrawSprite(PaletteFile* pal, SpriteFile* sfile, SpriteFile* asfile, sint32 index, sint32 x, sint32 y)
{
	mForeground->DrawSprite(pal, sfile, asfile, index, x, y);
}

void Renderer::DrawSprite(PaletteFile* pal, SpriteFile* sfile, sint32 index, sint32 x, sint32 y)
{
	mForeground->DrawSprite(pal, sfile, index, x, y);
}

void Renderer::DrawSprite(PaletteFile* pal, SpriteFile* sfile, uint8 alpha, sint32 index, sint32 x, sint32 y)
{
	if (alpha == 0xFF)
		mForeground->DrawSprite(pal, sfile, index, x, y);
	else
		mForeground->DrawSprite(pal, sfile, alpha, index, x, y);
}

void Renderer::DrawRAW(PaletteFile* pal, RawFile* raw, sint32 x, sint32 y)
{
	mForeground->DrawRAW(pal, raw, x, y);
}

void Renderer::DrawString(Font* font, std::string text, sint32 x, sint32 y)
{
	font->DrawString(mForeground, text, x, y);
}

void Renderer::DrawBox(PaletteFile* palette, SpriteFile* spriteFile, sint32 x, sint32 y, sint32 width, sint32 height, sint32 nw)
{
	DrawBox(palette, spriteFile, 0xFF, x, y, width, height, nw);
}

void Renderer::DrawBox(PaletteFile* palette, SpriteFile* spriteFile, uint8 a, sint32 x, sint32 y, sint32 width, sint32 height, sint32 nw)
{
	DrawBox(palette, spriteFile, a, x, y, width, height, nw, nw + 4, nw + 1, nw + 6, nw + 8, nw + 7, nw + 2, nw + 5, nw + 3);
}

void Renderer::DrawBox(PaletteFile* palette, SpriteFile* spriteFile, sint32 x, sint32 y, sint32 width, sint32 height, sint32 nw, sint32 n, sint32 ne, sint32 w, sint32 c, sint32 e, sint32 sw, sint32 s, sint32 se)
{
	DrawBox(palette, spriteFile, 0xFF, x, y, width, height, nw, n, ne, w, c, e, sw, s, se);
}

void Renderer::DrawBox(PaletteFile* palette, SpriteFile* spriteFile, uint8 a, sint32 x, sint32 y, sint32 width, sint32 height, sint32 nw, sint32 n, sint32 ne, sint32 w, sint32 c, sint32 e, sint32 sw, sint32 s, sint32 se)
{
	sint32 nw_w = (nw != -1 ? spriteFile->mWidths[nw] : 0);
	sint32 nw_h = (nw != -1 ? spriteFile->mHeights[nw] : 0);
	sint32 ne_w = (ne != -1 ? spriteFile->mWidths[ne] : 0);
	sint32 ne_h = (ne != -1 ? spriteFile->mHeights[ne] : 0);
	sint32 sw_w = (sw != -1 ? spriteFile->mWidths[sw] : 0);
	sint32 sw_h = (sw != -1 ? spriteFile->mHeights[sw] : 0);
	sint32 se_w = (se != -1 ? spriteFile->mWidths[se] : 0);
	sint32 se_h = (se != -1 ? spriteFile->mHeights[se] : 0);

	//Middle
	if (c != -1) {
		for (sint32 dy = y; dy < y + height - spriteFile->mHeights[c]; dy += spriteFile->mHeights[c]) {
			for (sint32 dx = x; dx < x + width - spriteFile->mWidths[c]; dx += spriteFile->mWidths[c]) {
				DrawSprite(palette, spriteFile, a, c, dx, dy);
			}
		}
	}

	//North
	if (n != -1) {
		for (sint32 dx = x + spriteFile->mWidths[n]; dx < x + width - ne_w; dx += spriteFile->mWidths[n]) {
			DrawSprite(palette, spriteFile, a, n, dx, y);
		}
	}
	//South
	if (s != -1) {
		for (sint32 dx = x + nw_w; dx < x + width - ne_w; dx += spriteFile->mWidths[s]) {
			DrawSprite(palette, spriteFile, a, s, dx, y + height - spriteFile->mHeights[s]);
		}
	}
	//West
	if (w != -1) {
		for (sint32 dy = y + nw_h; dy < y + height - sw_h; dy += spriteFile->mHeights[w]) {
			DrawSprite(palette, spriteFile, a, w, x, dy);
		}
	}
	//East
	if (e != -1) {
		for (sint32 dy = y + ne_h; dy < y + height - se_h; dy += spriteFile->mHeights[e]) {
			DrawSprite(palette, spriteFile, a, e, x + width - spriteFile->mWidths[e], dy);
		}
	}

	//Corners
	if (nw != -1)
		DrawSprite(palette, spriteFile, a, nw, x, y);
	if (ne != -1)
		DrawSprite(palette, spriteFile, a, ne, x + width - ne_w, y);
	if (sw != -1)
		DrawSprite(palette, spriteFile, a, sw, x, y + height - sw_h);
	if (se != -1)
		DrawSprite(palette, spriteFile, a, se, x + width - se_w, y + height - se_h);
}

uint32 Renderer::SwapColourBits(uint32 colour)
{
	return (((colour & 0x000000FF) << 16) | (colour & 0x0000FF00) | ((colour & 0x00FF0000) >> 16));
}

}