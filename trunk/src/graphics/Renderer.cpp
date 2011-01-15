#include <d3d9.h>
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

int Renderer::Init()
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
	if (mD3DDEV->BeginScene()) {
		mDrawing = true;
		return true;
	}
}

void Renderer::EndDraw()
{
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

int Renderer::CreateSurface(LPDIRECT3DSURFACE9& surface, int width, int height)
{
	return mD3DDEV->CreateOffscreenPlainSurface(
		width,
		height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);
}

void Renderer::BlitSurface(Surface* surface, RECT rect)
{
	mD3DDEV->StretchRect(surface->mD3DSurface, NULL, mBackBuffer, &rect, D3DTEXF_NONE);
}

}