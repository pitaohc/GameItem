//#include"myhead.h"
//#include<bits/stdc++.h>
#include<Windows.h>
#include<string>
#include<iostream>
   
using namespace std;
const string ProgramTitle = "Hello world";
bool gameover = false;
void GameRun();
bool GameInit();
void GameEnd();
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance);
bool InitInstance(HINSTANCE hInstance, int nCmdShow);

void GameRun()
{
	cout << "hello world" << endl;
}

bool GameInit()
{
	return true;
}

void GameEnd()
{
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT drawRect;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 20; i++)
		{
			int x = i * 20;
			int y = i * 20;
			drawRect = { x,y,x + 100,y + 20 };
			DrawText(hdc, ProgramTitle.c_str(), ProgramTitle.size(), &drawRect, DT_CENTER);

		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		gameover = true;
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
   HWND hWnd = CreateWindow(
		ProgramTitle.c_str(), 
		ProgramTitle.c_str(), 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 
		CW_USEDEFAULT, 0, 
		nullptr, 
		nullptr, 
		hInstance, 
		nullptr);

	if (!hWnd) return false;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
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
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		GameRun();
	}
	GameEnd();
	return msg.wParam;
}
