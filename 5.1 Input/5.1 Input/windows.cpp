#include"myhead.h"

//global variable
HWND window;
const string AppTitle = "3.1 First Step for Direct3D";
const int SCREENW = 1024;
const int SCREENH = 768;
LPDIRECT3D9 d3d = nullptr;
LPDIRECT3DDEVICE9 d3ddev = nullptr;
bool gameover = false;
bool windowed = true;
fstream logfile("log.txt", ios::app);
//declare function
void Error(char* info, int code);
inline bool KeyDown(int vk_code);
bool Game_Init();
void Game_Run();
void Game_End();
LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
inline bool KeyDown(int vk_code)
{
	return (GetAsyncKeyState(vk_code) & 0x8000);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	//Register wndclassex
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.lpszClassName = AppTitle.c_str();
	wc.lpszMenuName = AppTitle.c_str();
	wc.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClassEx(&wc);
	//Init window
	window = CreateWindow(
		AppTitle.c_str(),
		AppTitle.c_str(),
		WS_EX_TOPMOST|WS_POPUP,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREENW, SCREENH,
		nullptr,
		nullptr,
		hInstance,
		nullptr);
	if (!window) return 1;
	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	Game_Init();

	MSG msg;
	while (!gameover)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		Game_Run();
	}
	Game_End();
	return msg.wParam;
}



bool Game_Init()
{

}

void Game_Run()
{
}

void Game_End()
{
}

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		gameover = true;
		break;
	}
	return DefWindowProc(window, message, wParam, lParam);
}
