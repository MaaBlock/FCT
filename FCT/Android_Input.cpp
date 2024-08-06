//
// Created by DEEP on 2024/8/6.
//

#include "hander.h"

namespace FCT {
    void Android_Input::registerInputCallBack(InputCallBack* callback){
        m_callback = callback;
    }
} // FCT