#include "hander.h"


extern int main();
namespace FCT{
    void FCTAPI_PreInit(){
    }
    Android_Window* Android_Window::Instance = NULL;
    Window* Android_CreateWindow(){
        return Android_Window::getInstance();
    }

    window_info_t Android_Window::create(uint32_t style)
    {
        return window_info_t();
    }
    void* Android_Window::MainThread(void* param){
        while (getInstance()->getNativeWindow()) {
            usleep(1000);
        }
        ((GLES3_0_Context*)getInstance()->m_context)->setTarget(Instance);
        //ToDo:已创建完surface,从此继续
        main();
        return NULL;
    }

    void Android_Window::Init(GameActivity* activity) {
        Instance = new Android_Window;
        Instance->m_activity = activity;
        Instance->m_running = true;
        Instance->m_context =
                GLES3_0_Context::Init(); //创建一个GLES3_0_Context,
                //并且context type为window

        Instance->m_context->create();
        FCTAPI_PreInit();
        //注意，destory之后running变为false，
        // 若在线程内设为true，要注意destroy后刚好线程内设为true
        pthread_create(&Instance->m_mainThread, NULL, Android_Window::MainThread, Instance);
    }
    void Android_Window::destroy()
    {
    }

    void Android_Window::size(int w, int h)
    {
    }

    void Android_Window::show()
    {
    }

    void Android_Window::flush()
    {
    }

    bool Android_Window::isRunning()
    {
        return m_running;
    }

    int Android_Window::getx()
    {
        return 0;
    }

    int Android_Window::gety()
    {
        return 0;
    }

    int Android_Window::getwidth()
    {
        return 0;
    }

    int Android_Window::getheight()
    {
        return 0;
    }

    Color* Android_Window::getBuffer()
    {
        return nullptr;
    }

    Input* Android_Window::getInput()
    {
        return nullptr;
    }
//translate 部分
    void Android_Window::onStart(GameActivity* activity)
    {
        aout << "Android_Window::onStart" << std::endl;
    }

    void Android_Window::onResume(GameActivity* activity)
    {
        aout << "Android_Window::onResume" << std::endl;
    }

    void Android_Window::onPause(GameActivity* activity)
    {
        aout << "Android_Window::onPause" << std::endl;
    }

    void Android_Window::onStop(GameActivity* activity)
    {
        aout << "Android_Window::onStop" << std::endl;
    }

    void Android_Window::onDestroy(GameActivity* activity)
    {
        aout << "Android_Window::onDestroy" << std::endl;
        Instance->m_running = false;
    }

    void Android_Window::onWindowFocusChanged(GameActivity* activity, bool hasFocus)
    {
        aout << "Android_Window::onWindowFocusChanged" << std::endl;

    }

    void Android_Window::onTrimMemory(GameActivity* activity, int level)
    {
        aout << "Android_Window::onTrimMemory" << std::endl;

    }

    void Android_Window::onConfigurationChanged(GameActivity* activity)
    {
        aout << "Android_Window::onConfigurationChanged" << std::endl;
    }

    void Android_Window::onSaveInstanceState(GameActivity* activity, SaveInstanceStateRecallback recallback, void* context)
    {
        aout << "Android_Window::onSaveInstanceState" << std::endl;
    }

    bool Android_Window::isFocus()
    {
        return m_focus;
    }

    bool Android_Window::isMinimize()
    {
        return m_minmize;
    }

    bool Android_Window::isForeground()
    {
        return m_foreground;
    }

    void Android_Window::onWindowInsetsChanged(GameActivity* activity)
    {
        aout << "Android_Window::onWindowInsetsChanged" << std::endl;
    }

    void Android_Window::onTextInputEvent(GameActivity* activity, const GameTextInputState* state)
    {
        aout << "Android_Window::onTextInputEvent" << std::endl;
    }

    bool Android_Window::onKey(GameActivity* activity, const GameActivityKeyEvent* event)
    {
        aout << "Android_Window::onKey" << std::endl;
        return false;
    }

    bool Android_Window::onTouchEvent(GameActivity* activity, const GameActivityMotionEvent* event)
    {
        aout << "Android_Window::onTouchEvent" << std::endl;
        return false;
    }

    void Android_Window::onNativeWindowResized(GameActivity* activity, ANativeWindow* window, int32_t width, int32_t height)
    {
        aout << "Android_Window::onNativeWindowResized" << std::endl;
    }

    void Android_Window::onNativeWindowRedrawNeeded(GameActivity* activity, ANativeWindow* window)
    {
        aout << "Android_Window::onNativeWindowRedrawNeeded" << std::endl;
    }

    void Android_Window::onNativeWindowDestroyed(GameActivity* activity, ANativeWindow* window)
    {
        aout << "Android_Window::onNativeWindowDestroyed" << std::endl;
    }

    void Android_Window::onNativeWindowCreated(GameActivity* activity, ANativeWindow* window)
    {

        aout << "Android_Window::onNativeWindowCreated" << std::endl;
        getInstance()->m_nativeWindow = window;
    }

    GameActivity* Android_Window::getActivity() {
        return m_activity;
    }

    ANativeWindow *Android_Window::getNativeWindow() {
        return m_nativeWindow;
    }
}

JNIEXPORT
void GameActivity_onCreate(GameActivity* activity, void* savedState,
                           size_t savedStateSize) {
    activity->callbacks->onDestroy = FCT::Android_Window::onDestroy;
    activity->callbacks->onStart = FCT::Android_Window::onStart;
    activity->callbacks->onResume = FCT::Android_Window::onResume;
    activity->callbacks->onSaveInstanceState = FCT::Android_Window::onSaveInstanceState;
    activity->callbacks->onPause = FCT::Android_Window::onPause;
    activity->callbacks->onStop = FCT::Android_Window::onStop;
    activity->callbacks->onTouchEvent = FCT::Android_Window::onTouchEvent;
    activity->callbacks->onKeyDown = FCT::Android_Window::onKey;
    activity->callbacks->onKeyUp = FCT::Android_Window::onKey;
    activity->callbacks->onTextInputEvent = FCT::Android_Window::onTextInputEvent;
    activity->callbacks->onConfigurationChanged = FCT::Android_Window::onConfigurationChanged;
    activity->callbacks->onTrimMemory = FCT::Android_Window::onTrimMemory;
    activity->callbacks->onWindowFocusChanged = FCT::Android_Window::onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = FCT::Android_Window::onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = FCT::Android_Window::onNativeWindowDestroyed;
    activity->callbacks->onNativeWindowRedrawNeeded = FCT::Android_Window::onNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowResized = FCT::Android_Window::onNativeWindowResized;
    activity->callbacks->onWindowInsetsChanged = FCT::Android_Window::onWindowInsetsChanged;
    //LOGV("Callbacks set: %p", activity->callbacks);
    FCT::Android_Window::Init(activity);
}