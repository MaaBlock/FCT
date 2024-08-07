//使用图形调试时开启
//#define GRAPH_DEBUG

//宏
#define  COM_RELEASE(param) if(param) {param->Release(); param = NULL;}
#define	 FCT_RELEASE(param) if(param) {param->release(); param = NULL;}
//api or std

#include <iostream>
#include <cstdint>
#include <vector>

//注意WIN32宏是定义在Windows.h里面
#ifdef _WIN32
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
#ifdef  _WIN32
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3dCompiler.lib")
#pragma comment(lib,"DXGI.lib")
#endif
#ifdef ANDROID
#include <unistd.h>
#include <EGL/egl.h>
#include "AndroidOut.h"
#include "GameActivity.h"
#endif

#define FCT_MEMORY_CHEAK
#ifdef FCT_MEMORY_CHEAK
#include <typeinfo>
namespace FCT {
	struct _fct_object_t {
		void* pointer;
		std::string describe;
	};
	extern std::vector<_fct_object_t*> fct_object_list;
	template <typename T>
	T* _fct_new() {
		T* ret = new T;
		_fct_object_t* object = new _fct_object_t;
		object->pointer = ret;
		object->describe = typeid(ret).name();

		return new T;
	}
	template <typename T>
	void _fct_delete(T arg) {
		fct_object_list.erase(std::find(
			fct_object_list.begin(), fct_object_list.end(),
			[arg](_fct_object_t* object) {
				return object->pointer == arg;
			}
		));
		delete arg;
	}
	template <typename T>
	void _fct_deletes(T arg) {
		delete[] arg;
	}
	inline void _output_object(std::ostream out) {
		//线程不安全
		for (auto i = fct_object_list.begin(); i != fct_object_list.end(); i++) {
			out << (*i)->describe;
		}
	}
}

#define FCT_NEW(type) _fct_new<type>()
#define FCT_DELETE(args) _fct_delete<auto>(args)
#define FCT_DELETES(args) _fct_deletes<auto>(args)
#else
#define FCT_NEW(type) new type
#define FCT_DELETE(args) delete args
#define FCT_DELETES(args) delete[] args
#endif // FCT_MEMORY_CHEAK


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

#ifdef _WIN32
#undef CreateWindow
#define CreateWindow Win32_D3D11_CreateWindow
#endif

//实现类 or 派生类

#ifdef _WIN32
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
#include "GLES3_0_Context.h"
#include "GLES3_0_Image.h"
#define CreateWindow Android_CreateWindow
//#include "Android_Context.h"
#endif

	void Init();
}