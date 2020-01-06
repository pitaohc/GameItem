#include"myheader.h"
//#include<bits/stdc++.h>

using namespace std;
void DrawBitmap(const char* filename, int x, int y)
{
	//load the bitmap image
	HBITMAP image = (HBITMAP)LoadImage(0, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//read the bitmap's properties
	BITMAP bm;
	GetObject(image, sizeof(BITMAP), &bm);
	HDC hdcImage = CreateCompatibleDC(device);
	SelectObject(hdcImage, image);

	BitBlt(
		device,
		x, y,
		bm.bmWidth, bm.bmHeight,
		hdcImage,
		0, 0,
		SRCCOPY);

	DeleteDC(hdcImage);
	DeleteObject((HBITMAP)image);
	
	
}

bool GameInit()
{
	srand(time(NULL));
	return true;
}

void GameRun()
{
	if (gameover) return;

	RECT rect;
	GetClientRect(window, &rect);
	if (rect.right - rect.left > 0 && rect.bottom - rect.top > 0)
	{
		int x = rand() % (rect.right - rect.left);
		int y = rand() % (rect.bottom - rect.top);
		DrawBitmap(filename.c_str(), x, y);
	}
	
}

void GameEnd()
{
	ReleaseDC(window, device);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT drawRect;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);
	//	for (int i = 0; i < 20; i++)
	//	{
	//		int x = i * 20;
	//		int y = i * 20;
	//		drawRect = { x,y,x + 100,y + 20 };
	//		DrawText(hdc, ProgramTitle.c_str(), ProgramTitle.size(), &drawRect, DT_CENTER);

	//	}
	//	EndPaint(hWnd, &ps);
	//	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		gameover = true;
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.lpszClassName = ProgramTitle.c_str();
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	return RegisterClassEx(&wc);
}

bool InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	window = CreateWindow(
		ProgramTitle.c_str(),
		ProgramTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!window) return false;
	ShowWindow(window, nCmdShow);
	UpdateWindow(window);
	device = GetDC(window);
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//string str = "hello ";
	//wstring wstr =L"ÄãºÃ";
	////MessageBoxW(NULL, wstr.c_str(), wstr.c_str(), MB_OK | MB_ICONEXCLAMATION);
	//MessageBox(NULL, str.c_str(), str.c_str(), MB_OK | MB_ICONEXCLAMATION);


	//create the Window
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow)) return 0;
	if (!GameInit()) return 0;
	while (!gameover)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		GameRun();
		Sleep(100);
	}
	GameEnd();
	return msg.wParam;
}
