#include "hander.h"
#include <iostream>

namespace FCT {
	InputCallBack* Win32_Input::m_nullcallback = NULL;

	void Win32_Input::Init()
	{
		m_nullcallback = FCT_NEW( InputCallBack);
	}
	Win32_Input::Win32_Input(Window* wnd)
	{
		REF_CLASS_BEGIN();
		m_window = wnd;
	}
	;

	LRESULT Win32_Input::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_PAINT:
			m_callback->onPaint();
			return 0;
		case WM_LBUTTONDOWN:
			m_callback->onMouseLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_LBUTTONUP:
			m_callback->onMouseLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_RBUTTONUP:
			m_callback->onMouseRButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_RBUTTONDOWN:
			m_callback->onMouseRButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_KEYDOWN:
			return 0;
		case WM_NCHITTEST:
			switch (m_callback->onNCTest(GET_X_LPARAM(lParam) - m_window->getx()
				, GET_Y_LPARAM(lParam) - m_window->gety()))
			{
			case nctest_clent:
				return HTCLIENT;
			case nctest_caption:
				return HTCAPTION;
			case nctest_size_top_left:
				return HTTOPLEFT;
			case nctest_size_top:
				return HTTOP;
			case nctest_size_top_right:
				return HTTOPRIGHT;
			case nctest_size_right:
				return HTRIGHT;
			case nctest_size_bottom_right:
				return HTBOTTOMRIGHT;
			case nctest_size_bottom:
				return HTBOTTOM;
			case nctest_size_bottom_left:
				return HTBOTTOMLEFT;
			case nctest_size_left:
				return HTLEFT;
			default:
				return HTCLIENT;
			}
		case WM_CHAR:
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	void Win32_Input::registerInputCallBack(InputCallBack* callback)
	{
		m_callback = callback;
	}
}
