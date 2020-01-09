#include"MyDirectX.h"
#include"resource.h"
using namespace std;
fstream logfile("log.txt", ios::app);
HWND window;
//Windows event handler
LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		gameover = true;
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(window, message, wParam, lParam); //Ĭ����Ϣ
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Initialize window settings
	WNDCLASSEX wc;
	wc.cbClsExtra		= 0;					//������󸽼��ֽ���
	wc.cbSize			= sizeof(WNDCLASSEX);	//WNDCLASSEX �Ĵ�С
	wc.cbWndExtra		= 0;					//����ʵ���󸽼��ֽ���
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//�������
	wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);		  //�����
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));		//ͼ����
	wc.hIconSm			= nullptr;		//Сͼ����
	wc.hInstance		= hInstance;	//ʵ�����
	wc.lpfnWndProc		= (WNDPROC)WinProc;			//������Ϣ������
	wc.lpszClassName	= "MainWindowClass";		//������ָ��
	wc.lpszMenuName		= nullptr;					//�˵�ָ��
	wc.style			= CS_VREDRAW | CS_HREDRAW; //������
	RegisterClassEx(&wc);
	//Init window
	window = CreateWindow(
		"MainWindowClass",
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

	if (!Game_Init(window)) return 1;

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

