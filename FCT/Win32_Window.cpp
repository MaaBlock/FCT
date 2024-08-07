#include "hander.h"
namespace FCT {
	Window* Win32_D3D11_CreateWindow()
	{
		return new Win32_D3D11_Window;
	}

	void Win32_D3D11_Window::Init()
	{
		WNDCLASSEXW wcex = {};

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = NULL;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = L"DeaultWindowClass";
		wcex.hIconSm = NULL;

		RegisterClassExW(&wcex);
	}

	void Win32_D3D11_Window::WndThread(Win32_D3D11_Window* wnd)
	{
		wnd->addRef();
		RECT rc;
		SetRect(&rc, 0, 0, wnd->m_width, wnd->m_height);
		AdjustWindowRect(&rc, WS_POPUP | ((wnd->m_style & ws_debug) ? WS_CAPTION | WS_SYSMENU : 0), FALSE);
		if (wnd->m_width == CW_USEDEFAULT) {
			rc.left = 0;
			rc.right = CW_USEDEFAULT;
		}
		if (wnd->m_height == CW_USEDEFAULT) {
			rc.top = 0;
			rc.bottom = CW_USEDEFAULT;
		}
		//
		wnd->m_input = new Win32_Input(wnd);
		//创建无边框窗口
		//创建窗口
		wnd->m_wnd = CreateWindowExW(0
			, L"DeaultWindowClass"
			, wnd->m_name,
			WS_POPUP | ((wnd->m_style & ws_debug) ? WS_CAPTION | WS_SYSMENU : 0)
			, wnd->m_x, wnd->m_y, rc.right - rc.left, rc.bottom - rc.top,
			NULL, NULL, NULL,
			(LPVOID)wnd);
		do {
			if (!wnd->m_wnd) {
				wnd->m_input->release();
				break;
			}
			wnd->m_created = true;
			MSG msg;
			while (GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
#ifdef Test
#endif // Test


		} while (0);
		wnd->m_runing = false;
		wnd->m_created = false;
		wnd->release();
	}

	window_info_t Win32_D3D11_Window::create(uint32_t style)
	{

		m_style = style;
		if (m_created) {
			return window_error_has_created;
		}
		m_runing = true;
		m_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WndThread, this, 0, NULL);
		while (!m_created && m_runing) {
			Sleep(1);
		}
		if (!m_runing) {
			return window_error;
		}
		return window_success;
	}

	Win32_D3D11_Window::Win32_D3D11_Window()
	{
		REF_CLASS_BEGIN();
		m_buffer = NULL;
		m_input = NULL;
		m_wnd = NULL;
		m_thread = NULL;
		m_name = L"Unnamed";
		m_width = CW_USEDEFAULT;
		m_height = CW_USEDEFAULT;
		m_x = CW_USEDEFAULT;
		m_y = CW_USEDEFAULT;
		m_nMaxWidth = 0;
		m_nMaxHeight = 0;
		m_nMinWidth = 0;
		m_nMinHeight = 0;
		m_style = 0;
		m_created = false;
		m_runing = false;
		m_samplerState = NULL;
		m_device = NULL;
		m_context = NULL;
		m_bufferTexture = NULL;
		m_bufferTextureView = NULL;
		m_swapChain = NULL;
		m_renderTargetView = NULL;
		m_depthStencilBuffer = NULL;
		m_depthStencilView = NULL;
		m_inputLayout = NULL;
		m_featureLevel = {};
		m_vertexShader = NULL;
		m_pixelShader = NULL;
		m_vertexBuffer = NULL;
	}

	Win32_D3D11_Window::~Win32_D3D11_Window()
	{
		destroy();
	}

	void Win32_D3D11_Window::destroy()
	{
		if (m_runing) {
			DestroyWindow(m_wnd);
			CloseHandle(m_thread);
			m_runing = false;
			m_wnd = NULL;
			m_thread = NULL;
		}

		if (m_buffer) {
			delete[] m_buffer;
			m_buffer = NULL;
		}
		FCT_RELEASE(m_input);
		COM_RELEASE(m_samplerState);
		COM_RELEASE(m_device);
		COM_RELEASE(m_context);
		COM_RELEASE(m_bufferTexture);
		COM_RELEASE(m_bufferTextureView);
		COM_RELEASE(m_swapChain);
		COM_RELEASE(m_renderTargetView);
		COM_RELEASE(m_depthStencilBuffer);
		COM_RELEASE(m_depthStencilView);
		COM_RELEASE(m_inputLayout);
		COM_RELEASE(m_vertexShader);
		COM_RELEASE(m_pixelShader);
		COM_RELEASE(m_vertexBuffer);
	}
	void Win32_D3D11_Window::size(int w, int h)
	{
		if (m_created) {
			if (m_height == h && m_width == w)
				return;
			SetWindowPos(m_wnd, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
			return;
		}
		m_width = w;
		m_height = h;
		return;
	}

	void Win32_D3D11_Window::show()
	{
		ShowWindow(m_wnd, SW_SHOW);
	}

	void Win32_D3D11_Window::name(const wchar_t* name)
	{
		if (m_created) {

			return;
		}
		m_name = name;
		return;
	}

	void Win32_D3D11_Window::flush()
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;

		m_context->Map(m_bufferTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, m_buffer, sizeof(Color) * m_width * m_height);
		m_context->Unmap(m_bufferTexture, 0);
		float color[4] = { 0, 0, 1.0f, 0 };
		m_context->ClearRenderTargetView(m_renderTargetView, color);
		m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		m_context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_context->Draw(4, 0);
		m_swapChain->Present(0, 0);
	}

	bool Win32_D3D11_Window::isRunning()
	{
		return m_runing;
	}

	Color* Win32_D3D11_Window::getBuffer()
	{
		return m_buffer;
	}

	int Win32_D3D11_Window::getx()
	{
		return m_x;
	}

	int Win32_D3D11_Window::gety()
	{
		return m_y;
	}

	int Win32_D3D11_Window::getwidth()
	{
		return m_width;
	}

	int Win32_D3D11_Window::getheight()
	{
		return m_height;
	}

	Input* Win32_D3D11_Window::getInput()
	{
		return m_input;
	}

	bool Win32_D3D11_Window::isFocus()
	{
		return false;
	}

	bool Win32_D3D11_Window::isMinimize()
	{
		return false;
	}

	bool Win32_D3D11_Window::isForeground()
	{
		return false;
	}

}