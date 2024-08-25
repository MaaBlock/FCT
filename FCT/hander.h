//使用图形调试时开启
//#define GRAPH_DEBUG

//宏
#define  COM_RELEASE(param) if(param) {param->Release(); param = NULL;}
#define	 FCT_RELEASE(param) if(param) {param->release(); param = NULL;}
//api or std

#include <iostream>
#include <cstdint>
#include <map>
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
#include <mutex>
namespace FCT {
	struct _fct_object_t {
		void* pointer;
		std::string describe;
		int refCounted;
	};
	extern std::vector<_fct_object_t*> fct_object_list;
	extern std::string fct_object_info;
	extern std::mutex fct_object_mutex; 
	extern int fct_object_count_delete_without_object;
	template <typename T, typename... Args>
	T* _fct_new(const Args&... arg) {
		T* ret = new T(arg...);
		_fct_object_t* object = new _fct_object_t;
		object->pointer = ret;
		object->refCounted = -1;
		object->describe = typeid(ret).name();
		fct_object_mutex.lock();
		fct_object_list.push_back(object);
		fct_object_mutex.unlock();
		return ret;
	}

	template <typename T, typename AUTO>
	T* _fct_news(AUTO size) {
		T* ret = new T[size];
		_fct_object_t* object = new _fct_object_t;
		object->pointer = ret;
		object->refCounted = -1;
		object->describe = typeid(ret).name();
		fct_object_mutex.lock();
		fct_object_list.push_back(object);
		fct_object_mutex.unlock();
		return ret;
	}
	template <typename T>
	void _fct_delete(T arg) {
		fct_object_mutex.lock();
		auto i = fct_object_list.begin();
		while (i != fct_object_list.end()) {
			if ((*i)->pointer == arg) {
				delete (*i);
				fct_object_list.erase(i);
				goto FinshWhile;
			}
			i++;
		}
		if (i == fct_object_list.end()) {
			fct_object_count_delete_without_object++;
		}
	FinshWhile:
		fct_object_mutex.unlock();
		delete arg;
	}
	template <typename T>
	void _fct_deletes(T arg) {
		auto i = fct_object_list.begin();
		for (; i != fct_object_list.end(); i++) {
			if ((*i)->pointer == arg) {
				delete (*i);
				fct_object_list.erase(i);
				goto FinshWhiles;
			}
		}
		if (i == fct_object_list.end()) {
			fct_object_count_delete_without_object++;
		}
	FinshWhiles:
		delete[] arg;
	}
	inline void _output_object_nums(std::ostream& out) {
		out << "当前对象总计:" << fct_object_list.size() << std::endl;
	}
	inline void _output_object(std::ostream& out) {
		//线程不安全
		for (auto i = fct_object_list.begin(); i != fct_object_list.end(); i++) {
			out << (*i)->describe << std::endl;
		}
		out <<  "不在object表里不delete的数量:" << fct_object_count_delete_without_object << std::endl;
		out << "未释放对象总计:" << fct_object_list.size() <<std::endl;
	}
}
#define FCT_NEW(type,...) _fct_new<type>(__VA_ARGS__)
#define FCT_NEWS(type,num) _fct_news<type>(num)
#define FCT_DELETE(args) _fct_delete<decltype(args)>(args)
#define FCT_DELETES(args) _fct_deletes<decltype(args)>(args)
#else
#define FCT_NEW(type) new type
#define FCT_DELETE(args) delete args
#define FCT_DELETES(args) delete[] args
#endif // FCT_MEMORY_CHEAK
#define FCT_PERFORMANCE_TEST 
#ifdef FCT_PERFORMANCE_TEST
namespace FCT {

}
#endif //FCT_PERFORMANCE_TEST



namespace FCT {
//引用计数
#include "RefCount.h"
//杂项类
#include "Atomic.h"
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
#include "TextDevice.h"
#include "Context.h"
#include "Thread.h"
#include "mutex.h"
#include "Renderer.h"
//适配创建

#ifdef _WIN32
#undef CreateWindow
#define CreateWindow Win32_D3D11_CreateWindow
#undef CreateMutex
#define CreateMutex Win32_CreateMutex
#endif
#ifdef ANDROID
#define CreateWindow Android_CreateWindow
#endif
//实现类 or 派生类

#ifdef _WIN32
#include "Win32_Mutex.h"
#include "DirectXMath_Matrix.h"
#include "UIManager.h"
#include "UIControl.h"
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
//#include "Android_Context.h"
#endif
#include "LibrayContext.h"
	void Init();
}