#include"myhead.h"

//global variable
HWND window;
const string AppTitle = "5.1 Input";
int SCREENW = 640;
int SCREENH = 480;
LPDIRECT3D9 d3d = nullptr;
LPDIRECT3DDEVICE9 d3ddev = nullptr;
LPDIRECTINPUT8 dinput = nullptr;
LPDIRECTINPUTDEVICE8 dinputdev = nullptr;
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
//Initialize XInput and any connected controllers
bool XInput_Init(int contNum = 0)
{
	XINPUT_CAPABILITIES caps;
	ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
	XInputGetCapabilities(contNum, XINPUT_FLAG_GAMEPAD, &caps);
	if (caps.Type != XINPUT_DEVTYPE_GAMEPAD) return false;
	return true;
}
//Causes the controller to vibrate
void XInput_Vibrate(int contNum = 0, int left = 65535, int right = 65535)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(PXINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = left;
	vibration.wRightMotorSpeed = right;
	XInputSetState(contNum, &vibration);
}
//Checks the state of the controller
void XInput_Update()
{
	XINPUT_STATE state;
	string message;
	for (int i = 0; i < 4; i++)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		message = "";
		//get the state of the controller
		DWORD result = XInputGetState(i, &state);
		XINPUT_GAMEPAD& gamepad = state.Gamepad;
		if (result == 0)
		{
			if (gamepad.bLeftTrigger)
				message = "Left Trigger";
			else if (gamepad.bRightTrigger)
				message = "Right Trigger";
			else if (gamepad.sThumbLX < -10000 ||
				gamepad.sThumbLX>10000)
				message = "Left Thumb Stick";
			else if (gamepad.sThumbRX <= -10000 ||
				gamepad.sThumbRX > 10000)
				message = "Right Thumb Stick";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_BACK)
				gameover = true;
			else if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				message = "DPAD down";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				message = "DPAD left";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				message = "DPAD right";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				message = "DPAD up";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				message = "L shoulder";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				message = "R shoulder";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
				message = "L Thumb";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
				message = "R Thumb";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_START)
				message = "Start";
			else if (gamepad.wButtons & XINPUT_GAMEPAD_A)
				message = "Botton A", XInput_Vibrate(i, 100,100);
			else if (gamepad.wButtons & XINPUT_GAMEPAD_B)
				message = "Botton B", XInput_Vibrate(i, 1000,1000);
			else if (gamepad.wButtons & XINPUT_GAMEPAD_X)
				message = "Botton X", XInput_Vibrate(i, 10000,10000);
			else if (gamepad.wButtons & XINPUT_GAMEPAD_Y)
				message = "Botton Y", XInput_Vibrate(i);
			if (message.length() > 0)
				MessageBox(0, message.c_str(), "Controller", 0);
		}
	}
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
	if(!RegisterClassEx(&wc)) return 0;
	//Init window
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
	if (!window) return 1;
	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	if(!Game_Init()) return 0;

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
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) return false;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferHeight = SCREENH;
	d3dpp.BackBufferWidth = SCREENW;
	d3dpp.hDeviceWindow = window;
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);
	if (!d3ddev) return false;
	XInput_Init();
	return true;
}

void Game_Run()
{
	if (!d3ddev) return;
	d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 150), 1.0f, 0);
	if (d3ddev->BeginScene())
	{
		d3ddev->EndScene();
		d3ddev->Present(nullptr, nullptr, nullptr, nullptr);

	}
	if (KeyDown(VK_ESCAPE))
		PostMessage(window, WM_DESTROY, 0, 0);
	XInput_Update();
}

void Game_End()
{
	if (d3ddev) d3ddev->Release();
	if (d3d)		d3d->Release();
	d3ddev = nullptr;
	d3d = nullptr;
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
