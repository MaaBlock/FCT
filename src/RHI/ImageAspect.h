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
    inline vk::ImageAspectFlagBits ToVkImageAspect(ImageAspect bit)
    {
        switch (bit)
        {
        case ImageAspect::color:
            return vk::ImageAspectFlagBits::eColor;
        case ImageAspect::depth:
            return vk::ImageAspectFlagBits::eDepth;
        case ImageAspect::stencil:
            return vk::ImageAspectFlagBits::eStencil;
        default:
            return vk::ImageAspectFlagBits(0);
        }
    }
    inline auto ToVkImageAspects(ImageAspects flags)
    {
        auto result = ToVkImageAspect(static_cast<ImageAspect>(0)) | ToVkImageAspect(static_cast<ImageAspect>(0));
        for (uint32_t i = 0; i < 32; ++i) {
            ImageAspect singleFlag = static_cast<ImageAspect>(1u << i);
            if (flags & singleFlag) {
                result |= ToVkImageAspect(singleFlag);
            }
        }
        return result;
    }
#endif
}
#endif //IMAGEASPECT_H
