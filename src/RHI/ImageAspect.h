#ifndef IMAGEASPECT_H
#define IMAGEASPECT_H
#include "../Base/Flags.h"
namespace FCT
{
    enum class ImageAspect
    {
        color = 1 << 0,
        depth = 1 << 1,
        stencil = 1 << 2
    };
    FCT_DECLARE_FLAGS(ImageAspect);
#ifdef FCT_USE_VULKAN
    FCT_TO_VK_FLAG_BIT_BEGIN(ImageAspect)
    FCT_TO_VK_FLAG_BIT_CASE(ImageAspect,color, Color)
    FCT_TO_VK_FLAG_BIT_CASE(ImageAspect, depth, Depth)
    FCT_TO_VK_FLAG_BIT_CASE(ImageAspect, stencil, Stencil)
    FCT_TO_VK_FLAG_BIT_END(ImageAspect)
    FCT_TO_VK_FLAGS(ImageAspect)
#endif
}
#endif //IMAGEASPECT_H
