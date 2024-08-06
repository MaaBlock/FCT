//使用图形调试时开启
//#define GRAPH_DEBUG

//宏
#define  COM_RELEASE(param) if(param) {param->Release(); param = NULL;}
#define	 FCT_RELEASE(param) if(param) {param->release(); param = NULL;}
//api or std

#include <iostream>
#include <cstdint>
#include <vector>
#ifdef WIN32
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <windowsx.h>
#include <DirectXMath.h>

#include <DXGItype.h>  
#include <dxgi1_2.h>  
#include <dxgi1_3.h>  
#include <DXProgrammableCapture.h>
#endif

#include "stb_truetype.h"
#ifdef  WIN32
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3dCompiler.lib")
#pragma comment(lib,"DXGI.lib")
#endif
#ifdef ANDROID
#include "AndroidOut.h"
#include "GameActivity.h"
#endif

namespace FCT {
	//引用计数
#include "RefCount.h"
//杂项类
#include "Vector.h"
#include "struct.h"
#include "Queue.h"
#include "stack.h"
#include "Tree.h"
#include "Geometry.h"
#include "ComputationalGeometryAlgorithm.h"
//提前声明的类
#include "preclass.h"
//接口类 or 基类
#include "Matrix.h"
#include "FileProcess.h"
#include "Image.h"
#include "Target.h"
#include "Input.h"
#include "Window.h"
#include "Object.h"
#include "ContextResouce.h"
#include "Shape.h"
#include "Text.h"
#include "Context.h"
//适配创建

#ifdef WIN32
#undef CreateWindow
#define CreateWindow Win32_D3D11_CreateWindow
#endif

//实现类 or 派生类

#ifdef WIN32
#include "DirectXMath_Matrix.h"
#include "UIManager.h"
#include "Win32_File.h"
#include "Win32_Input.h"
#include "Win32_Window.h"
#include "Directx11_Image.h"
#include "Directx11_Target.h"
#include "Directx11_ContextResouce.h"
#include "Directx11_Context.h"
#endif
#ifdef ANDROID
#include "AndroidActivitySwap.h"
//#include "android_File.h"
//#include "android_Input.h"
//#include "android_Window.h"
//#include "android_Image.h"
//#include "android_Target.h"
//#include "android_ContextResouce.h"
#include "Android_Window.h"
#include "Android_Input.h"
#define CreateWindow Android_CreateWindow
//#include "Android_Context.h"
#endif

	void Init();
}