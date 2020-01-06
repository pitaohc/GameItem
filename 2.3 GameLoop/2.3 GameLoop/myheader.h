#pragma once
#include<Windows.h>
#include<string>
#include<iostream>
#include<time.h>
using namespace std;
HWND window;
HDC device;

const string ProgramTitle = "GameLoop";
const string filename;
bool gameover = false;

void DrawBitmap(char* filename, int x, int y);
void GameRun();
bool GameInit();
void GameEnd();

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance);
bool InitInstance(HINSTANCE hInstance, int nCmdShow);