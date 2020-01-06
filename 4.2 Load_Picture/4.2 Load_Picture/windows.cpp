#include"myhead.h"
int rate = 0;
//游戏初始化函数
bool Game_Init()
{
	//initialization Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) return false;
	//set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	if (windowed)
	{
		d3dpp.Windowed = windowed;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferHeight = SCREENH;
		d3dpp.BackBufferWidth = SCREENW;
		d3dpp.hDeviceWindow = window;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	}
	else
	{
		D3DDISPLAYMODE d3ddm;
		d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
		d3dpp.Windowed = windowed;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.BackBufferHeight = d3ddm.Height;
		d3dpp.BackBufferWidth = d3ddm.Width;
		d3dpp.hDeviceWindow = window;
		d3dpp.FullScreen_RefreshRateInHz = d3ddm.RefreshRate;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		SCREENW = d3ddm.Width;
		SCREENH = d3ddm.Height;
	}
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (!d3ddev) return false;
	//set random number seed
	srand(time(nullptr));
	//clear the backbuffer to black
	d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	//create pointer to the back buffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	HRESULT result = d3ddev->CreateOffscreenPlainSurface(
		100,
		100,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		nullptr);
	if (result != D3D_OK) return false;
	//Load surface from file into newly created surface
	result = D3DXLoadSurfaceFromFile(
		surface,
		nullptr,
		nullptr,
		PictureFile.c_str(),
		nullptr,
		D3DX_DEFAULT,
		0,
		nullptr);
	if (result != D3D_OK) return false;

	return true;

}
//游戏循环函数
void Game_Run()
{
	if (!d3ddev) return;
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	if (d3ddev->BeginScene())
	{
		d3ddev->StretchRect(surface, nullptr, backbuffer, nullptr, D3DTEXF_NONE);

		d3ddev->EndScene();
		d3ddev->Present(nullptr, nullptr, nullptr, nullptr);
	}



	//check the escape key (to exit)
	if (KeyDown(VK_ESCAPE))
	{
		PostMessage(window, WM_DESTROY, 0, 0);
	}
}
//游戏结束函数
void Game_End()
{
	if (surface) surface->Release();
	if (backbuffer)backbuffer->Release();
	if (d3ddev)d3ddev->Release();
	if (d3d)d3d->Release();
	surface = nullptr;
	backbuffer = nullptr;
	d3ddev = nullptr;
	d3d = nullptr;
}

inline bool KeyDown(int vk_code)
{
	return (GetAsyncKeyState(vk_code) & 0x8000);
}
//程序入口
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	//Register wndclassex
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
	if (windowed)
	{
		window = CreateWindow(
			AppTitle.c_str(),
			AppTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			SCREENW, SCREENH,
			nullptr,
			nullptr,
			hInstance,
			nullptr);
	}
	else
	{
		window = CreateWindow(
			AppTitle.c_str(),
			AppTitle.c_str(),
			WS_EX_TOPMOST | WS_POPUP,
			0, 0,
			SCREENW, SCREENH,
			nullptr,
			nullptr,
			hInstance,
			nullptr);
	}
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
//
LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_DESTROY:
		gameover = true;
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(window, message, wParam, lParam);
}
