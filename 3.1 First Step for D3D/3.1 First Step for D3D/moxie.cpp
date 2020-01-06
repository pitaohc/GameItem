//#include<iomanip>
//#include<iostream>
//#include<fstream>
//#include<sstream>
//#include<random>
//#include<Windows.h>
//#include<time.h>
//#include<d3d9.h>
//#include<d3dx9.h>
//using namespace std;
//
//#pragma comment(lib,"d3d9.lib")
//class myRGB
//{
//public:
//	myRGB(int r = 255, int g = 0, int b = 0, int _state = 0) 
//		:red(r), green(g), blue(b), state(_state) {};
//	void Change(int step=1)
//	{
//		switch (state)
//		{
//		case 0:
//			green += step;
//			if (green >= 255)
//			{
//				green = 255;
//				++state;
//			}
//			break;
//		case 1:
//			red -= step;
//			if (red <= 0)
//			{
//				red = 0;
//				++state;
//			}
//			break;
//		case 2:
//			blue += step;
//			if (blue >= 255)
//			{
//				blue = 255;
//				++state;
//			}
//			break;
//		case 3:
//			green -= step;
//			if (green <= 0)
//			{
//				green = 0;
//				++state;
//			}
//			break;
//		case 4:
//			red += step;
//			if (red >= 255)
//			{
//				red = 255;
//				++state;
//			}
//			break;
//		case 5:
//			blue -= step;
//			if (blue <= 255)
//			{
//				blue = 255;
//				state = 0;
//			}
//			break;
//		}
//	}
//	void Rand()
//	{
//		srand(time(nullptr));
//		red = rand() % 256;
//		green = rand() % 256;
//		blue = rand() % 256;
//	}
//	int red, green, blue;
//	int state;
//};
//myRGB rgb;
////global variable
//HWND window;
//const string AppTitle = "3.1 First Step for Direct3D";
//const int SCREENW = 1024;
//const int SCREENH = 768;
//LPDIRECT3D9 d3d = nullptr;
//LPDIRECT3DDEVICE9 d3ddev = nullptr;
//bool gameover = false;
//bool windowed = true;
//fstream logfile("log.txt", ios::app);
////declare function
//void Error(char* info, int code);
//inline bool KeyDown(int vk_code);
//bool Game_Init();
//void Game_Run();
//void Game_End();
//LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	WNDCLASSEX wc;
//	//Register wndclassex
//	wc.cbClsExtra=0;
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.cbWndExtra = 0;
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hIcon = nullptr;
//	wc.hIconSm = nullptr;
//	wc.hInstance = hInstance;
//	wc.lpfnWndProc = (WNDPROC)WinProc;
//	wc.lpszClassName = AppTitle.c_str();
//	wc.lpszMenuName = AppTitle.c_str();
//	wc.style = CS_VREDRAW | CS_HREDRAW;
//	RegisterClassEx(&wc);
//	//Init window
//	window = CreateWindow(
//		AppTitle.c_str(),
//		AppTitle.c_str(),
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT,CW_USEDEFAULT,
//		SCREENW,SCREENH,
//		nullptr,
//		nullptr,
//		hInstance,
//		nullptr);
//	if (!window) return 1;
//	ShowWindow(window, nCmdShow);
//	UpdateWindow(window);
//
//	Game_Init();
//
//	MSG msg;
//	while (!gameover)
//	{
//		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessageA(&msg);
//		}
//		Game_Run();
//	}
//	Game_End();
//	return msg.wParam;
//}
//
//inline bool KeyDown(int vk_code)
//{
//	return (GetAsyncKeyState(vk_code)& 0x8000);
//}
//
//bool Game_Init()
//{
//	d3d = Direct3DCreate9(D3D_SDK_VERSION);
//	if (!d3d)return false;
//	D3DPRESENT_PARAMETERS d3dpp;
//	ZeroMemory(&d3dpp, sizeof(d3dpp));
//	d3dpp.BackBufferCount = 1;
//	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
//	d3dpp.BackBufferHeight = SCREENH;
//	d3dpp.BackBufferWidth = SCREENW;
//	d3dpp.hDeviceWindow = window;
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	d3dpp.Windowed = windowed;
//	d3d->CreateDevice(
//		D3DADAPTER_DEFAULT,
//		D3DDEVTYPE_HAL,
//		window,
//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		&d3dpp,
//		&d3ddev);
//	if (!d3ddev)return false;
//	return true;
//}
//
//void Game_Run()
//{
//	if (!d3ddev) return;
//	d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(rgb.red, rgb.green, rgb.blue), 1.0f, 0);
//	if (d3ddev->BeginScene())
//	{
//
//		d3ddev->EndScene();
//		d3ddev->Present(nullptr, nullptr, nullptr, nullptr);
//	}
//	rgb.Change();
//	if (KeyDown(VK_LSHIFT))
//	{
//		rgb.Rand();
//	}
//	//if (KeyDown(VK_RBUTTON))
//	//{
//	//	--r, --g, --b;
//	//}
//	if (KeyDown(VK_ESCAPE))
//		PostMessage(window, WM_DESTROY, 0, 0);
//}
//
//void Game_End()
//{
//
//	if (d3ddev)
//	{
//		d3ddev->Release();
//		d3ddev = nullptr;
//	}
//	if (d3d)
//	{
//		d3d->Release();
//		d3d = nullptr;
//	}
//}
//
//LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_DESTROY:
//		gameover = true;
//		break;
//	}
//	return DefWindowProc(window,message,wParam,lParam);
//}
