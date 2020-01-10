# GameItem
Direct3D9 learning  path

这是pitao的Direct3D9学习路径与源码项目

欢迎Star和Fork

书籍采用 
《Beginning Game Programming (Fourth Edition) 》
Author Jonathan S. Harbour



<!-- TOC -->
- [第一章 Windows初步](#第一章-windows初步)
  - [1.1 Windows编程概述](#11-windows编程概述)  
    - [1.1.1“获取”Windows](#111获取windows)
    - [1.1.2理解Windows消息机制](#112理解windows消息机制)
    - [1.1.3多任务](#113多任务)
    - [1.1.4多线程](#114多线程)
    - [1.1.5事件处理](#115事件处理)
  - [1.2DirectX快速概览](#12directx快速概览)
- [第五章 从键盘、鼠标和控制器获得输入](#第五章-从键盘鼠标和控制器获得输入)
  - [5.1 键盘输入](#51-键盘输入)
    - [5.1.1 DirectInput对象和设备](#511-directinput对象和设备)
    - [5.1.2 初始化键盘](#512-初始化键盘)
<!-- /TOC -->

第一部分 Windows和DirectX游戏编程

Windows初步  
如何侦听Windows消息   
如何初始化Direct3D
# 第一章 Windows初步
编写简单Windows程序、在VS中创建项目、键入代码以及运行整个程序  
1、如何正确看待游戏编程  
2、如何按需选择最好的编译器  
3、如何创建Win32应用程序项目  
4、如何编写简单的WIndows程序
## 1.1 Windows编程概述
DirectSDK 最广泛的游戏编程库  
Windows多线程、多任务操作系统
### 1.1.1“获取”Windows
兼容性  
GUI 图形用户界面  
消息驱动  
64位
### 1.1.2理解Windows消息机制
外部事件-->系统总线-->应用程序  
操作系统取向于模仿神经系统  
### 1.1.3多任务
计算机 时间分片 “同时”运行多个程序  
Windows通过为内存中的每个程序创建虚拟地址空间来处理时间分片  
当Windows跳到下一个程序时，会储存当前程序的状态，当重新运行到该程  
序时会正确返回  
### 1.1.4多线程
多线程是将程序分解成多个线程的进程，每个线程就像一个独立运行的程序  
### 1.1.5事件处理
Windows如何与这么多同时运行的程序保持联系？  
1、程序必须是事件驱动  
2、Windows使用全系统范围内的消息来通信  

消息内容：
1、Windows句柄
2、实例标识符
3、消息类型

事件：鼠标按下、键盘按下、控制器、网络端口
## 1.2DirectX快速概览

# 第五章 从键盘、鼠标和控制器获得输入
演示在游戏中使用键盘、鼠标和控制器  
1、如何创建DirectInput设备  
2、如何从键盘获得输入  
3、如何从鼠标获得输入  
4、如何从控制器（手柄）获得输入  
5、如何创建并移动一个精灵  
6、如何制作你的第一个游戏
## 5.1 键盘输入
IDirectInput8 主DirectInput对象
用LPDirectInput8引用
DirectInput库文件名为“dinput8.lib”
### 5.1.1 DirectInput对象和设备
初始化：  
1、定义变量
``` cpp
LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 dinputdev;
```
2、调用DirectInputCreate8初始化DirectInput
``` cpp
HRESULT WINAPT DirectInputCreate8(
    HINSTANCE hinst,    //当前程序的实例句柄，
                        //可用GetModuleHandle(NULL)获取
    DWORD dwVersion,    //DirectInput版本，
                        //用DIRECTINPUT_VERSION宏
    REFIID riidltf,     //目标DirectInput版本的引用表示符，  
                        //用IID_IDirectInput8
    LPVOID *ppvOut,     //指向主DirectInput对象的指针
    LPUNKNOWN punkOuter);//总是nullptr
```
3、调用CreateDevice来创建新的DirectInput设备
``` cpp
HRESULT CreateDevice(
    REFGUID rguid,  //指定要创建的对象类型（比如键盘或鼠标）
                    //宏 GUID_SysKeyboard 或 GUID_SysMouse
    LPDIRECTINPUTDEVICE *lplpDirectInputDevice,
                    //接收DirectInput设备句柄的地址的设备指针
    LPUNKNOWN pUnkOuter);//总为nullptr
```
### 5.1.2 初始化键盘
告诉DirectInput如何将数据传回给程序，因为市场上有上百种输入设备，  
必须要有统一的能够读取他们的方式  
4、设置键盘数据格式  
SetDataFormat为DirectInput设备指定数据格式
```cpp
HRESULT SetDataFormat(LPCDIDATAFORMAT lpdf);
//设备类型参数，键盘和鼠标分别传 c_dfDIKeyboard 和 c_dfDIMouse
```
例子
```cpp
HRESULT result = dikeyboard->SetDataFormat(c-dfDIKeyboard);
```
5、设置协作级别  
协作级别按优先级决定DirectInput将键盘输入传递给程序的程度如果想获  
得对键盘的排他使用，DirectInput有可能会抱怨，所以可以前台应用程序  
优先级请求非排他访问
```cpp
HRESULT LPDIRECTINPUTDEVICE8::SetCooperativeLevel(
    HWND hwnd,          //窗口句柄
    DWORD dwFlags);     //指定优先级
```
```cpp
HRESULT result = dikeyboard->SetCooperativeLevel(
    hwnd,
    DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
```
3、获取设备
使用Acquire函数取得键盘设备
```cpp
HRASULT Acquire();
```
return DI_OK 成功获取
注意：Shutdown时需要调用Unacquire()释放设备