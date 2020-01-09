#pragma once
//IO��
#include<iomanip>
#include<iostream>
#include<fstream>
#include<sstream>
//Windows��c++ͷ
#include<algorithm>
#include<vector>
#include<random>
#include<Windows.h>
#include<time.h>
//Direct3Dͷ
#include<d3d9.h>
#include<d3dx9.h>

using namespace std;
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
//global variable
HWND window;										//Windows���ھ��
const string AppTitle = "4.1 Surface and Bitmap";	//�������
const string PictureFile = "photo.png";
int SCREENW = 1920;			//���ڿ�
int SCREENH = 1080;			//���ڸ�
LPDIRECT3D9 d3d = nullptr;			//D3Dָ��
LPDIRECT3DDEVICE9 d3ddev = nullptr;	//D3D�豸ָ��
bool gameover = false;				//��Ϸ������ʾ
bool windowed = true;				//�Ƿ񴰿ڻ�
fstream logfile("log.txt", ios::app);//������־�ļ�����
//declare function
void Error(char* info, int code);//�����������
inline bool KeyDown(int vk_code);//��������
bool Game_Init();	//��Ϸ��ʼ������
void Game_Run();	//��Ϸѭ������
void Game_End();	//��Ϸ��������
LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);//Windows��Ϣ���� 
//New objects in this solution
LPDIRECT3DSURFACE9 backbuffer = nullptr;
LPDIRECT3DSURFACE9 surface = nullptr;