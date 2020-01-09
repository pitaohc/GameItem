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