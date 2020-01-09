#include"MyDirectX.h"
#include"resource.h"
using namespace std;
fstream logfile("log.txt", ios::app);
HWND window;
//Windows event handler
LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		gameover = true;
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(window, message, wParam, lParam); //默认消息
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Initialize window settings
	WNDCLASSEX wc;
	wc.cbClsExtra		= 0;					//窗口类后附加字节数
	wc.cbSize			= sizeof(WNDCLASSEX);	//WNDCLASSEX 的大小
	wc.cbWndExtra		= 0;					//窗口实例后附加字节数
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//背景句柄
	wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);		  //光标句柄
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));		//图标句柄
	wc.hIconSm			= nullptr;		//小图标句柄
	wc.hInstance		= hInstance;	//实例句柄
	wc.lpfnWndProc		= (WNDPROC)WinProc;			//窗口消息处理函数
	wc.lpszClassName	= "MainWindowClass";		//类名称指针
	wc.lpszMenuName		= nullptr;					//菜单指针
	wc.style			= CS_VREDRAW | CS_HREDRAW; //窗体风格
	RegisterClassEx(&wc);
	//Init window
	window = CreateWindow(
		"MainWindowClass",
		AppTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREENW, SCREENH,
		nullptr,
		nullptr,
		hInstance,
		nullptr);
	if (!window) return 1;
	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	if (!Game_Init(window)) return 1;

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

