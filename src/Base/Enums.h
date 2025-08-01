//
// Created by Administrator on 2025/8/2.
//

#ifndef ENUMS_H
#define ENUMS_H
#include "../ThirdParty.h"
namespace FCT {

#ifdef FCT_USE_VULKAN
    #define FCT_TO_VK_ENUM_BEGIN(Enums) \
        inline vk::##Enums ToVk##Enums(Enums e) \
        { \
            switch (e) \
            {
#define FCT_TO_VK_ENUM_CASE(Enums,value,Value) \
            case Enums::value: \
                return vk::##Enums::e##Value;
#define FCT_TO_VK_ENUM_END(Enums) \
            default: \
                return vk::##Enums(0); \
            } \
        }

#endif
}
#endif //ENUMS_H
