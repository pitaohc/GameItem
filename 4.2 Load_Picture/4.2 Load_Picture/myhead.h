#pragma once
//IO流
#include<iomanip>
#include<iostream>
#include<fstream>
#include<sstream>
//Windows和c++头
#include<algorithm>
#include<vector>
#include<random>
#include<Windows.h>
#include<time.h>
//Direct3D头
#include<d3d9.h>
#include<d3dx9.h>

using namespace std;
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
//global variable
HWND window;										//Windows窗口句柄
const string AppTitle = "4.1 Surface and Bitmap";	//程序标题
const string PictureFile = "photo.png";
int SCREENW = 1920;			//窗口宽
int SCREENH = 1080;			//窗口高
LPDIRECT3D9 d3d = nullptr;			//D3D指针
LPDIRECT3DDEVICE9 d3ddev = nullptr;	//D3D设备指针
bool gameover = false;				//游戏结束表示
bool windowed = true;				//是否窗口化
fstream logfile("log.txt", ios::app);//程序日志文件对象
//declare function
void Error(char* info, int code);//错误输出函数
inline bool KeyDown(int vk_code);//虚拟键检测
bool Game_Init();	//游戏初始化函数
void Game_Run();	//游戏循环函数
void Game_End();	//游戏结束函数
LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);//Windows消息处理 
//New objects in this solution
LPDIRECT3DSURFACE9 backbuffer = nullptr;
LPDIRECT3DSURFACE9 surface = nullptr;