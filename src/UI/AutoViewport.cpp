#include "../Context/Context.h"
#include "./Window.h"
namespace FCT
{
    AutoViewport::AutoViewport()
    {

    }

    AutoViewport::AutoViewport(Vec2 windowSize, Vec2 viewportSize)
    {
        m_needReviewport = false;
        resize(windowSize.x,windowSize.y);
        m_dstViewportWidth = viewportSize.x;
        m_dstViewPortHeight = viewportSize.y;
        m_viewportOffsetX = 0.0f;
        m_viewportOffsetY = 0.0f;
    }

    void AutoViewport::ctx(FCT::Context* ctx)
    {
        this->m_ctx = ctx;
    }

    void AutoViewport::window(Window* wnd)
    {
        m_wnd = wnd;
    }

    void AutoViewport::enable(bool enable)
    {
        if (m_resizeCallBack)
        {
            m_wnd->getCallBack()->removeResizeCallback(m_resizeCallBack);
        }
        m_resizeCallBack = m_wnd->getCallBack()->addResizeCallback([this](Window* w,int width,int height)
        {
            resize(width,height);
        });
    }

    void AutoViewport::resize(int width, int height)
    {
        m_windowWidth = static_cast<float>(width);
        m_windowHeight = static_cast<float>(height);
        m_needReviewport = true;
    }

    void AutoViewport::computeViewport()
    {
        float targetAspect = m_dstViewportWidth / m_dstViewPortHeight;
        float windowAspect = m_windowWidth / m_windowHeight;

        if (windowAspect > targetAspect) {
            m_viewportHeight = m_windowHeight;
            m_viewportWidth = m_windowHeight * targetAspect;
            m_viewportOffsetX = (m_windowWidth - m_viewportWidth) / 2.0f;
            m_viewportOffsetY = 0.0f;
            return;
        }
        m_viewportWidth = m_windowWidth;
        m_viewportHeight = m_windowWidth / targetAspect;
        m_viewportOffsetX = 0.0f;
        m_viewportOffsetY = (m_windowHeight - m_viewportHeight) / 2.0f;
        return;
    }

    void AutoViewport::submit(RHI::CommandBuffer* cmdBuf)
    {
        if (m_needReviewport) {
            computeViewport();
            m_needReviewport = false;
        }
        cmdBuf->viewport(FCT::Vec2(m_viewportOffsetX, m_viewportOffsetY), FCT::Vec2(m_viewportOffsetX + m_viewportWidth, m_viewportOffsetY + m_viewportHeight));
        cmdBuf->scissor(FCT::Vec2(m_viewportOffsetX, m_viewportOffsetY), FCT::Vec2(m_viewportOffsetX + m_viewportWidth, m_viewportOffsetY + m_viewportHeight));
    }


    bool AutoViewport::wndPosToViewportPos(Vec2 wndPos, Vec2& viewportPos) const
    {
        Vec2 srcViewportPos(0.0f, 0.0f);
        srcViewportPos.x = (wndPos.x - m_viewportOffsetX) / m_viewportWidth;
        srcViewportPos.y = (wndPos.y - m_viewportOffsetY) / m_viewportHeight;
        viewportPos = srcViewportPos * Vec2(m_dstViewportWidth, m_dstViewPortHeight);
        return srcViewportPos.x >= 0.0f && srcViewportPos.x <= 1.0f
            && srcViewportPos.y >= 0.0f && srcViewportPos.y <= 1.0f;
    }
}



