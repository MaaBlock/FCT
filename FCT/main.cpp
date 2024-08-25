#include <jni.h>

#include "hander.h"

#include "GameActivity.cpp"
#include "gametextinput.cpp"
#include "android_native_app_glue.cpp"
using namespace FCT;
int main(){
    Window* wnd = CreateWindow();
    while (wnd->isRunning()){
        usleep(1000);
    }
}