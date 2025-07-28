//
// Created by Administrator on 2025/7/28.
//

#ifndef SWAPCHAINEVENT_H
#define SWAPCHAINEVENT_H
namespace FCT
{
    namespace RHI
    {
        class Swapchain;
    }
    namespace SwapchainEvent
    {
        struct Recreate
        {
            uint32_t width;
            uint32_t height;
            RHI::Swapchain* swapchain;
        };
    }
}
#endif //SWAPCHAINEVENT_H
