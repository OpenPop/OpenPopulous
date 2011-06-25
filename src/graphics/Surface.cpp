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

#include "Renderer.h"
#include "PaletteFile.h"
#include "RawFile.h"
#include "SpriteFile.h"
#include "Surface.h"

using namespace Graphics;

Surface::Surface(Renderer* renderer)
{
	mRenderer = renderer;
}

Surface::~Surface()
{
}

void Surface::Init()
{
	mRenderer->CreateSurface(mD3DSurface, mWidth, mHeight);
}

void Surface::Clear(D3DCOLOR colour)
{
	mRenderer->mD3DDEV->ColorFill(mD3DSurface, NULL, colour);
}

void Surface::LockBits()
{
	RECT rect;
	D3DLOCKED_RECT lrect;

	rect.left = 0;
	rect.top = 0;
	rect.right = mWidth;
	rect.bottom = mHeight;

	HRESULT result = mD3DSurface->LockRect(&lrect, &rect, NULL);

	mBits = (uint32*)lrect.pBits;

	memset(mBits, 0, mWidth * mHeight * 4);
}

void Surface::UnlockBits()
{
	mD3DSurface->UnlockRect();
}

uint32 inline Surface::GetOffset(sint32 x, sint32 y)
{
	return y * mWidth + x;
}

uint32 inline Surface::SwapColourBits(uint32 colour)
{
	return (((colour & 0x000000FF) << 16) | (colour & 0x0000FF00) | ((colour & 0x00FF0000) >> 16));
}

void Surface::FillRect(uint32 colour, sint32 x, sint32 y, sint32 w, sint32 h)
{
	for (sint32 dy = y; dy < y + h; dy++) {
		for (sint32 dx = x; dx < x + w; dx++) {
			mBits[GetOffset(dx, dy)] = colour;
		}
	}
}

void Surface::DrawSprite(PaletteFile* pal, SpriteFile* sfile, SpriteFile* asfile, sint32 index, sint32 destX, sint32 destY)
{
	//Alpha

	//Get sprite info.
	sint32 offset = asfile->mOffsets[index];
	sint32 width = asfile->mWidths[index];
	sint32 height = asfile->mHeights[index];

	uint8* alpha_buf = new uint8[width * height];

	//Draw sprite with transparancy
	sint8 *sbuffer = asfile->mBuffer;
	sint32 pos = offset;
	sint8 counter;
	for (sint32 y = 0; y < height; y++) {
		//Set x to the start of destX
		sint32 x = 0;

		//Loop through the pixels
		do {
			//Read the counter byte
			counter = sbuffer[pos];

			//Increment pos
			pos++;

			//Check if counter is positive
			if (counter > 0) {
				for (sint32 i = 0; i < counter; i++) {
					//Draw so many of the next pixels
					alpha_buf[y * width + x] = (uint8)sbuffer[pos];

					//Increment position
					pos++;

					//Add a pixel onto x
					x++;
				}
			} else if (counter < 0) {
				//Counter is negative therfore a transparant line of pixels
				x += -counter;
			}
			
			//Reloop if counter is not equal to 0
		} while (counter != 0);
	}

	//Get sprite info.
	offset = sfile->mOffsets[index];
	width = sfile->mWidths[index];
	height = sfile->mHeights[index];

	//Draw sprite with transparancy
	sbuffer = sfile->mBuffer;
	pos = offset;
	counter;
	for (sint32 y = destY; y < destY + height; y++) {
		//Set x to the start of destX
		sint32 x = destX;

		//Loop through the pixels
		do {
			//Read the counter byte
			counter = sbuffer[pos];

			//Increment pos
			pos++;

			//Check if counter is positive
			if (counter > 0) {
				for (sint32 i = 0; i < counter; i++) {
					//Draw so many of the next pixels
					uint8 oldcol[4];
					*((uint32*)&oldcol) = SwapColourBits(mBits[GetOffset(x, y)]);

					uint8 col[4];
					*((sint32*)col) = pal->mColours[(uint8)sbuffer[pos]];

					uint8 newcol[4];

					uint8 a = alpha_buf[(y - destY) * width + (x - destX)];
					//a = 255 - a;
					if (a > 0) {
						float alpha = a / 255.0f;
						newcol[0] = abs((oldcol[0] - col[0]) * alpha + col[0]);
						newcol[1] = abs((oldcol[1] - col[1]) * alpha + col[1]);
						newcol[2] = abs((oldcol[2] - col[2]) * alpha + col[2]);

						mBits[GetOffset(x, y)] = SwapColourBits(*((uint32*)&newcol));
					}

					//Increment position
					pos++;

					//Add a pixel onto x
					x++;
				}
			} else if (counter < 0) {
				//Counter is negative therfore a transparant line of pixels
				x += -counter;
			}
			
			//Reloop if counter is not equal to 0
		} while (counter != 0);
	}
}

void Surface::DrawSprite(PaletteFile* pal, SpriteFile* sfile, sint32 index, sint32 destX, sint32 destY)
{
	//Get sprite info.
	sint32 offset = sfile->mOffsets[index];
	sint32 width = sfile->mWidths[index];
	sint32 height = sfile->mHeights[index];

	//Draw sprite with transparancy
	sint8 *sbuffer = sfile->mBuffer;
	sint32 pos = offset;
	sint8 counter;
	for (sint32 y = destY; y < destY + height; y++) {
		//Set x to the start of destX
		sint32 x = destX;

		//Loop through the pixels
		do {
			//Read the counter byte
			counter = sbuffer[pos];

			//Increment pos
			pos++;

			//Check if counter is positive
			if (counter > 0) {
				for (sint32 i = 0; i < counter; i++) {
					//Draw so many of the next pixels
					mBits[GetOffset(x, y)] = SwapColourBits(pal->mColours[(uint8)sbuffer[pos]]);

					//Increment position
					pos++;

					//Add a pixel onto x
					x++;
				}
			} else if (counter < 0) {
				//Counter is negative therfore a transparant line of pixels
				x += -counter;
			}
			
			//Reloop if counter is not equal to 0
		} while (counter != 0);
	}
}

void Surface::DrawSprite(PaletteFile* pal, SpriteFile* sfile, uint8 a, sint32 index, sint32 destX, sint32 destY)
{
	//Get sprite info.
	sint32 offset = sfile->mOffsets[index];
	sint32 width = sfile->mWidths[index];
	sint32 height = sfile->mHeights[index];

	//Draw sprite with transparancy
	sint8 *sbuffer = sfile->mBuffer;
	sint32 pos = offset;
	sint8 counter;
	for (sint32 y = destY; y < destY + height; y++) {
		//Set x to the start of destX
		sint32 x = destX;

		//Loop through the pixels
		do {
			//Read the counter byte
			counter = sbuffer[pos];

			//Increment pos
			pos++;

			//Check if counter is positive
			if (counter > 0) {
				for (sint32 i = 0; i < counter; i++) {
					//Draw so many of the next pixels
					uint8 oldcol[4];
					*((uint32*)&oldcol) = SwapColourBits(mBits[GetOffset(x, y)]);

					uint8 col[4];
					*((sint32*)col) = pal->mColours[(uint8)sbuffer[pos]];

					uint8 newcol[4];

					if (a > 0) {
						float alpha = (255 - a) / 255.0f;
						newcol[0] = abs((oldcol[0] - col[0]) * alpha + col[0]);
						newcol[1] = abs((oldcol[1] - col[1]) * alpha + col[1]);
						newcol[2] = abs((oldcol[2] - col[2]) * alpha + col[2]);

						mBits[GetOffset(x, y)] = SwapColourBits(*((uint32*)&newcol));
					}

					//Increment position
					pos++;

					//Add a pixel onto x
					x++;
				}
			} else if (counter < 0) {
				//Counter is negative therfore a transparant line of pixels
				x += -counter;
			}
			
			//Reloop if counter is not equal to 0
		} while (counter != 0);
	}
}

void Surface::DrawRAW(PaletteFile* pal, RawFile* raw, sint32 x, sint32 y)
{
	for (sint32 rx = 0; rx < raw->mWidth; rx++) {
		for (sint32 ry = 0; ry < raw->mHeight; ry++) {
			sint32 colour = pal->mColours[raw->mBuffer[ry * raw->mWidth + rx]];
			mBits[GetOffset(x + rx, y + ry)] = SwapColourBits(colour);
		}
	}
}

void Surface::DrawPixel(sint32 x, sint32 y, sint32 colour)
{
	HDC hDC;
	mD3DSurface->GetDC(&hDC);
	SetPixel(hDC, x, y, colour);
	mD3DSurface->ReleaseDC(hDC);
}