#include "hander.h"
namespace FCT {
	std::vector<_fct_object_t*> fct_object_list = std::vector<_fct_object_t*>();
	std::string fct_object_info = std::string();
	int fct_object_count_delete_without_object = 0;
	std::mutex fct_object_mutex;
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