#include "hander.h"
namespace FCT {
	std::vector<_fct_object_t*> fct_object_list = std::vector<_fct_object_t*>(1024);
	void Init()
	{
#ifdef _WIN32
		Win32_D3D11_Window::Init();
		Win32_Input::Init();
		Directx11_Context::Init();
#endif // WIN32
	}
	unsigned RefCounted::nextId = 0;
};