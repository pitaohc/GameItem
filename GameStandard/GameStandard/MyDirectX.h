#pragma once

//Header files
#define WIN32_EXTRA_LEAN
#define DIRECTINPUT_VERSION 0x0800
#ifndef NULL
	#ifdef __cplusplus
		#define NULL nullptr
	#else
		#define NULL ((void *)0)
	#endif
#endif
#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<XInput.h>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<sstream>
#include<random>
#include<ctime>
//Libraries
using namespace std;
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"xinput.lib")

//Global variable
extern HWND window;
extern const string AppTitle;
extern int SCREENW;
extern int SCREENH;
extern bool gameover;
extern bool fullscreen_flag;
//Direct3D objects
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
extern fstream logfile;
//Direct3D functions
bool Direct3D_Init(HWND hWnd, int width, int height, bool fullscreen);
void Direct3D_Shutdown();
LPDIRECT3DSURFACE9 LoadSurface(const string& filename);
void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source);
//DirectInput objects,devices and states
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
extern DIMOUSESTATE2 mouse_state;
extern XINPUT_GAMEPAD controllers[4];
//DirectInput functions
bool DirectInput_Init(HWND hWnd);
void Directinput_Update();
void Directinput_Shutdown();
int Key_Down(int key);
int Mouse_Button(int button);
int Mouse_X();
int Mouse_Y();
void XInput_Vibrate(int contNum = 0, int amount = 65535);
bool XInput_Controller_Found();
//Game functions
bool Game_Init(HWND window);
void Game_Run();
void Game_End();
//Log report functions
void Error(char* info, int code);
void Warning(char* info, int code);
void LogInfo(char* info);