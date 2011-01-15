#include "Renderer.h"
#include "PaletteFile.h"
#include "RawFile.h"
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