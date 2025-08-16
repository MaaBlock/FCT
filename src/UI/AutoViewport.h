//
// Created by Administrator on 2025/5/10.
//

#ifndef FCT_AUTOVIEWPORT_H
#define FCT_AUTOVIEWPORT_H
#include "../RHI/CommandBuffer.h"
#include "./CallBackHandler.h"
namespace FCT
{
    class Context;
    class Window;
    class AutoViewport
    {
    public:
        AutoViewport();
        AutoViewport(Vec2 windowSize, Vec2 viewportSize);
        void ctx(FCT::Context* ctx);
        void window(Window* wnd);
        void enable(bool enable);
        void resize(int width, int height);
        void computeViewport();
        void submit(RHI::CommandBuffer* cmdBuf);
        bool wndPosToViewportPos(Vec2 wndPos,Vec2& viewportPos) const;
    private:
        bool m_needReviewport;
        float m_dstViewportWidth, m_dstViewPortHeight;
        float m_windowWidth, m_windowHeight;
        float m_viewportWidth, m_viewportHeight;
        float m_viewportOffsetX, m_viewportOffsetY;
        CallBackEventHandler::CallbackId m_resizeCallBack = 0;
        FCT::Context* m_ctx;
        Window* m_wnd;
    };
}
#endif //AUTOREVIEWPORT_H
