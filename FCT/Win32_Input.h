
class Win32_Input : public Input {
protected:
public:
	static InputCallBack* m_nullcallback;
	Win32_Input(Window* wnd);
	static void Init();
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void registerInputCallBack(InputCallBack* callback);
private:
	Mutex* m_mutex;
	Window* m_window;
	InputCallBack* m_callback = m_nullcallback;
};
