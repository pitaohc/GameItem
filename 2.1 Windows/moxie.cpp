//#include<iostream>
//#include<Windows.h>
//using namespace std;
//const string ProgramTitle = "Hello";
//const string str = "hello\nworld\n!!!\n";
//LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//bool InitInstance(HINSTANCE hInstance, int nCmdShow);
////ATOM MyRegisterClass(HINSTANCE hInstance);
//bool InitInstance(HINSTANCE hInstance, int nCmdShow) 
//{
//	HWND hWnd = CreateWindow(
//		ProgramTitle.c_str(),
//		ProgramTitle.c_str(),
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, 0,
//		CW_USEDEFAULT, 0,
//		NULL,
//		NULL,
//		hInstance,
//		NULL);
//	if (!hWnd) return false;
//
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//	return true;
//}
//LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	RECT drawRect;
//	HDC hdc;
//	PAINTSTRUCT ps;
//	switch (message)
//	{
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		for (int i = 0; i < 20; i++)
//		{
//			int x = i * 20;
//			int y = i * 20;
//			drawRect = { x,y,x + 100,y + 20 };
//			DrawText(hdc, str.c_str(), str.length(), &drawRect, DT_CALCRECT);
//		}
//		EndPaint(hWnd, &ps);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		break;
//	}
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	MSG msg;
//	WNDCLASSEX wc;
//	wc.cbClsExtra = 0;
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.cbWndExtra = 0;
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hIcon = NULL;
//	wc.hIconSm = NULL;
//	wc.hInstance = hInstance;
//	wc.lpfnWndProc = (WNDPROC)WinProc;
//	wc.lpszClassName = ProgramTitle.c_str();
//	wc.lpszMenuName = NULL;
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	RegisterClassEx(&wc);
//	if (InitInstance(hInstance, nCmdShow) == false) return 0;
//	while (GetMessage(&msg,NULL,0,0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	
//	return msg.wParam;
//}