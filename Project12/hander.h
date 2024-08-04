//#define GRAPH_DEBUG

//��
#define  COM_RELEASE(param) if(param) {param->Release(); param = NULL;}
#define	 FCT_RELEASE(param) if(param) {param->release(); param = NULL;}
//api or std
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <cstdint>
#include <windowsx.h>
#include <iostream>
#include <DirectXMath.h>
#include <vector>

#include <DXGItype.h>  
#include <dxgi1_2.h>  
#include <dxgi1_3.h>  
#include <DXProgrammableCapture.h>

#include "stb_truetype.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3dCompiler.lib")
#pragma comment(lib,"DXGI.lib")
namespace FCT {
	//���ü���
#include "RefCount.h"
//������
#include "Vector.h"
#include "struct.h"
#include "Queue.h"
#include "stack.h"
#include "Tree.h"
#include "Geometry.h"
#include "ComputationalGeometryAlgorithm.h"
//��ǰ��������
#include "preclass.h"
//�ӿ��� or ����
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
//���䴴��
#undef CreateWindow
#define CreateWindow Win32_D3D11_CreateWindow


//ʵ���� or ������
#include "DirectXMath_Matrix.h"
#include "UIManager.h"
#include "Win32_File.h"
#include "Win32_Input.h"
#include "Win32_Window.h"
#include "Directx11_Image.h"
#include "Directx11_Target.h"
#include "Directx11_ContextResouce.h"
#include "Directx11_Context.h"



	void Init();
}