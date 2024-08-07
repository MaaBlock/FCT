
Window* Android_CreateWindow();

class Android_Window : public Window {
    static Android_Window* Instance;
public:
    static inline Android_Window* getInstance(){
        return Instance;
    }
	// 通过 Window 继承
	window_info_t create(uint32_t style);

	void destroy();

	void size(int w, int h);

	void show();

	void flush();

	bool isRunning();
	bool isFocus();
	bool isMinimize();
	bool isForeground();
	int getx();

	int gety();

	int getwidth();

	int getheight();

	Color* getBuffer();

	Input* getInput();

    //内部函数，调用无效
    Image* getTarget();
    void setTarget(Image* target);

    GameActivity* getActivity();
    ANativeWindow* getNativeWindow();
private:
    pthread_t m_mainThread = NULL;
	bool m_running = false;
	bool m_focus = false;
	bool m_foreground = false;
	bool m_minmize = false;
    GameActivity* m_activity;
    ANativeWindow* m_nativeWindow = NULL;
    Context* m_context = NULL;
    Image* m_target = NULL;
public:
    static void* MainThread(void* param);
    static void Init(GameActivity* activity);
    static void onStart(GameActivity* activity);
    static void onResume(GameActivity* activity);
    static void onPause(GameActivity* activity);
    static void onStop(GameActivity* activity);
    static void onDestroy(GameActivity* activity);
    static void onWindowFocusChanged(GameActivity* activity, bool hasFocus);
	static void onWindowInsetsChanged(GameActivity* activity);
	static void onTextInputEvent(GameActivity* activity,
		const GameTextInputState* state);
	static bool onKey(GameActivity* activity, const GameActivityKeyEvent* event);
    static bool onTouchEvent(GameActivity* activity,
		const GameActivityMotionEvent* event);
	static void onNativeWindowResized(GameActivity* activity, ANativeWindow* window,
		int32_t width, int32_t height);
	static void onNativeWindowRedrawNeeded(GameActivity* activity,
		ANativeWindow* window);
	static void onNativeWindowDestroyed(GameActivity* activity,
		ANativeWindow* window);
	static void onNativeWindowCreated(GameActivity* activity,
		ANativeWindow* window);
	static void onTrimMemory(GameActivity* activity, int level);
	static void onConfigurationChanged(GameActivity* activity);
	static void onSaveInstanceState(GameActivity* activity,
		SaveInstanceStateRecallback recallback,
		void* context);;

};

