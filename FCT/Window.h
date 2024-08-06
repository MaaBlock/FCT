enum window_info_t {
	window_error = -2,
	window_error_has_created = -1,
	window_success = 0,
};

enum wnd_style_t {
	ws_deault = 0,
	ws_debug = 0x1,
	ws_user_softrenderer = 0x2,
};


class Window : public RefCounted {
public:
	virtual ~Window() {};
	virtual window_info_t create(uint32_t style = ws_deault) = 0;
	virtual void destroy() = 0;
	virtual void size(int w, int h) = 0;
	virtual void show() = 0;
	virtual void flush() = 0;
	virtual bool isFocus() = 0;
	virtual bool isMinimize() = 0;
	virtual bool isForeground() = 0;
	virtual bool isRunning() = 0;
	virtual int getx() = 0;
	virtual int gety() = 0;
	virtual int getwidth() = 0;
	virtual int getheight() = 0;
	virtual Color* getBuffer() = 0;
	virtual Input* getInput() = 0;
};