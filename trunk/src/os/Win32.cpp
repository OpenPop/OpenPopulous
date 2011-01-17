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

#include <windows.h>
#include <windowsx.h>

#include "..\OpenPop.h"
#include "Win32.h"

#define APPTITLE		"OpenPop"

sint32 WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, sint32 nCmdShow)
{
	OS::osWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

namespace OS
{

OpenPop* game;

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
ATOM RegisterOpenPopClass(HINSTANCE hInstance);

sint32 osWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, sint32 nCmdShow)
{
	MSG msg;

	RegisterOpenPopClass(hInstance);

	HWND hWnd;

	RECT rect = RECT();
	rect.right = 640;
	rect.bottom = 480;
	
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);

	hWnd = CreateWindowA(
		APPTITLE,
		APPTITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	//sint32 error = GetLastError();

	if (!hWnd)
		return FALSE;

	//Display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	game = new OpenPop();
	game->hWnd = hWnd;

	if (!game->Init())
		return 0;

	//main message loop
	sint32 done = 0;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//look for quit message
			if (msg.message == WM_QUIT) {
				done = 1;
			}

			//decode and pass messages on to WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			//process game loop
			game->Run();
		}
	}

	return msg.wParam;
}


LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_DESTROY:
			game->Close();
			PostQuitMessage(0);
			return 0;
		case WM_MOUSEMOVE:
			sint32 x = GET_X_LPARAM(lParam);
			sint32 y = GET_Y_LPARAM(lParam);
			game->MouseMove(x, y);
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

ATOM RegisterOpenPopClass(HINSTANCE hInstance)
{
	//create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	//fill the struct with info
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= (WNDPROC)WinProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= APPTITLE;
	wc.hIconSm			= NULL;

	//set up the window with the class info
	return RegisterClassEx(&wc);
}

}