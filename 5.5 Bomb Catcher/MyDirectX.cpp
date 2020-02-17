#include"MyDirectX.h"
using namespace std;

//Direct3D variables
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;
//DirectInput variables
LPDIRECTINPUT8 dinput = NULL;
LPDIRECTINPUTDEVICE8 dimouse = NULL;
LPDIRECTINPUTDEVICE8 dikeyboard = NULL;
DIMOUSESTATE2 mouse_state;
char keys[256];
XINPUT_GAMEPAD controllers[4];
//Direct3D initialization
bool Direct3D_Init(HWND hWnd, int width, int height, bool fullscreen)
{
	return false;
}
//Direct3D shutdown
void Direct3D_Shutdown()
{

}
//Draw a surface to the screen using StretchRect
void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source)
{

}
//Loads a bitmap file into a surface
LPDIRECT3DSURFACE9 LoadSurface(const string& filename)
{
	return LPDIRECT3DSURFACE9();
}

//DirectInput initialization
bool DirectInput_Init(HWND hWnd)
{
	return false;
}
//DirectInput shutdown
void Directinput_Shutdown()
{

}

//Directinput update
void Directinput_Update()
{

}

//Return mouse X movement
int Mouse_X()
{
	return 0;
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
void XInput_Vibrate(int contNum, int left, int right)
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
				message = "Botton A", XInput_Vibrate(i, 100, 100);
			else if (gamepad.wButtons & XINPUT_GAMEPAD_B)
				message = "Botton B", XInput_Vibrate(i, 1000, 1000);
			else if (gamepad.wButtons & XINPUT_GAMEPAD_X)
				message = "Botton X", XInput_Vibrate(i, 10000, 10000);
			else if (gamepad.wButtons & XINPUT_GAMEPAD_Y)
				message = "Botton Y", XInput_Vibrate(i);
			if (message.length() > 0)
				MessageBox(0, message.c_str(), "Controller", 0);
		}
	}
}
