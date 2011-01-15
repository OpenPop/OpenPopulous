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

void Surface::DrawSprite(PaletteFile* pal, SpriteFile* sfile, int index, int destX, int destY)
{
	HDC hDC;
	mD3DSurface->GetDC(&hDC);

	//Get sprite info.
	int offset = sfile->mOffsets[index];
	int width = sfile->mWidths[index];
	int height = sfile->mHeights[index];

	//Draw sprite with transparancy
	char *sbuffer = sfile->mBuffer;
	int pos = offset;
	signed char counter;
	for (int y = destY; y < destY + height; y++) {
		//Set x to the start of destX
		int x = destX;

		//Loop through the pixels
		do {
			//Read the counter byte
			counter = sbuffer[pos];

			//Increment pos
			pos++;

			//Check if counter is positive
			if (counter > 0) {
				for (int i = 0; i < counter; i++) {
					//Draw so many of the next pixels
					SetPixel(hDC, x, y, pal->mColours[(unsigned char)sbuffer[pos]]);

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

	mD3DSurface->ReleaseDC(hDC);
}

void Surface::DrawRAW(PaletteFile* pal, RawFile* raw, int x, int y)
{
	HDC hDC;
	mD3DSurface->GetDC(&hDC);
	
	for (int rx = 0; rx < raw->mWidth; rx++) {
		for (int ry = 0; ry < raw->mHeight; ry++) {
			SetPixel(hDC, x + rx, y+ ry, pal->mColours[raw->mBuffer[ry * raw->mWidth + rx]]);
		}
	}
	
	mD3DSurface->ReleaseDC(hDC);
}

void Surface::DrawPixel(int x, int y, int colour)
{
	HDC hDC;
	mD3DSurface->GetDC(&hDC);
	SetPixel(hDC, x, y, colour);
	mD3DSurface->ReleaseDC(hDC);
}