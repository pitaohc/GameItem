//#include<iostream>
//#include<d3d9.h>
//#include<d3dx9.h>
//#include<time.h>
//#include<fstream>
//#include<iomanip>
//using namespace std;
//#pragma comment(lib,"d3d9.lib")
//fstream logfile("log.txt", ios::app);
//const string AppTitle = "Direct3D_Windowed";
//const int SCREENW = 1024;
//const int SCREENH = 768;
//bool Windowed = true;
//LPDIRECT3D9 d3d = NULL;
//LPDIRECT3DDEVICE9 d3ddev = NULL;
//HWND window;
//bool gameover = false;
//
//#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)& 0x8000)?true:false)
//void Error(const char* str, int code = 1);
//bool Game_Init(HWND window);
//void Game_Run(HWND window);
//void Game_End(HWND window);
//LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
//
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wc;
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hIcon = NULL;
//	wc.hIconSm = NULL;
//	wc.hInstance = hInstance;
//	wc.lpfnWndProc = (WNDPROC)WinProc;
//	wc.lpszClassName = AppTitle.c_str();
//	wc.lpszMenuName = NULL;
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	return RegisterClassEx(&wc);
//}
//
//bool InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//	HWND window = CreateWindow(
//		AppTitle.c_str(),
//		AppTitle.c_str(),
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, 0,
//		CW_USEDEFAULT, 0,
//		nullptr,
//		nullptr,
//		hInstance,
//		nullptr);
//
//	if (!window) return false;
//	ShowWindow(window, nCmdShow);
//	UpdateWindow(window);
//	return true;
//}
//
//
////WinMain入口
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow)
//{
//
//	MSG msg;
//	MyRegisterClass(hInstance);
//	if (!InitInstance(hInstance, nCmdShow)) return 0;
//	if (!Game_Init()) return 0;
//	while (!gameover)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		Game_Run();
//	}
//	Game_End();
//	return msg.wParam;
//}
////输出错误信息并终止程序运行
//void Error(const char* str, int code)
//{
//
//	time_t tt = time(NULL);
//	tm t;
//	localtime_s(&t, &tt);
//	logfile << t.tm_year + 1900 << "-" << t.tm_mon + 1 << "-" << t.tm_mday << "\t"
//		<< setfill('0') << setw(2) << t.tm_hour << ":" << setfill('0') << t.tm_min << ":" << t.tm_sec << endl
//		<< "Error:" << str << "\ncode: " << code << endl << endl;
//	MessageBox(NULL, str, "Error", MB_ICONERROR);
//	if (code > 10)
//		exit(code);
//}
////游戏函数初始化
//bool Game_Init(HWND window)
//{
//	d3d = Direct3DCreate9(D3D_SDK_VERSION);
//	if (!d3d)
//	{
//		Error("Init Direct3D", 2);
//		return false;
//	}
//	D3DPRESENT_PARAMETERS d3dpp;
//	ZeroMemory(&d3dpp, sizeof(d3dpp));
//	d3dpp.Windowed = Windowed;
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	d3dpp.BackBufferCount = 1;
//	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
//	d3dpp.BackBufferHeight = SCREENH;
//	d3dpp.BackBufferWidth = SCREENW;
//	d3dpp.hDeviceWindow = window;
//	d3d->CreateDevice(
//		D3DADAPTER_DEFAULT,
//		D3DDEVTYPE_HAL,
//		window,
//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		&d3dpp,
//		&d3ddev);
//	if (d3ddev == NULL)
//	{
//		Error("Init D3D device Error", 2);
//		return false;
//	}
//
//	return true;
//}
////游戏主函数
//void Game_Run(HWND window)
//{
//	if (!d3ddev) return;
//
//	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 200), 1.0f, 0);
//	//渲染
//	if (d3ddev->BeginScene())
//	{
//		//do something
//		d3ddev->EndScene();
//		d3ddev->Present(NULL, NULL, NULL, NULL);
//	}
//	//计算
//	//检查按键
//	if (KEY_DOWN(VK_ESCAPE))
//		PostMessage(window, WM_DESTROY, 0, 0);
//}
////游戏结束函数
//void Game_End(HWND window)
//{
//
//}
////Windows消息处理
//LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	RECT drawRect;
//	PAINTSTRUCT ps;
//	HDC hdc;
//	switch (message)
//	{
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		for (int i = 0; i < 20; i++)
//		{
//			int x = i * 20;
//			int y = i * 20;
//			drawRect = { x,y,x + 100,y + 20 };
//			DrawText(hdc, AppTitle.c_str(), AppTitle.size(), &drawRect, DT_CENTER);
//
//		}
//		EndPaint(hWnd, &ps);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		gameover = true;
//		break;
//	default:
//		break;
//	}
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}
