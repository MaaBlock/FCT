class AndroidActivitySwap : public RefCounted{
public:
    static void onStart() {

    }
private:

};
/*进入后台
 *pasuse
 activityState被改变
 onWindowFocusChanged()
 NativeWindowDestroyed()
 android_app_set_window()
 APP_CMD_TERM_WINDOW()
 退出后台
 onStart_native
 activityState被改变
 Resume
 activityState被改变
 WindowInsetsChanged
 NativeWindowCreated
 android_app_set_window
 APP_CMD_INIT_WINDOW
 NativeWindowRedrawNeeded
 */
