class AndroidActivitySwap : public RefCounted{
public:
    static void onStart() {

    }
private:

};
/*�����̨
 *pasuse
 activityState���ı�
 onWindowFocusChanged()
 NativeWindowDestroyed()
 android_app_set_window()
 APP_CMD_TERM_WINDOW()
 �˳���̨
 onStart_native
 activityState���ı�
 Resume
 activityState���ı�
 WindowInsetsChanged
 NativeWindowCreated
 android_app_set_window
 APP_CMD_INIT_WINDOW
 NativeWindowRedrawNeeded
 */
