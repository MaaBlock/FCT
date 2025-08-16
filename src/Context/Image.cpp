//
// Created by Administrator on 2025/3/27.
//

#include "./Context.h"
#include "../RHI/Image.h"
#include "./Image.h"
namespace FCT
{
    BeforeCreateImageBehavior::BeforeCreateImageBehavior(Image* image)
    {
        m_image = image;
    }

    Format BeforeCreateImageBehavior::format() const
    {
        return m_image->m_format;
    }

    Samples BeforeCreateImageBehavior::samples() const
    {
        return m_image->m_samples;
    }

    void UpdateResult::waitFor()
    {
        fence->waitFor();
        fence->release();
        if (cleanUpCallback) {
            cleanUpCallback();
        }
        delete this;
    }

    Image::Image(Context* ctx) : m_ctx(ctx), m_behavior(nullptr), m_renderTargetType(RenderTargetType::ImageTarget),
                                 m_width(0), m_height(0)
    {
        m_samples = Samples::sample_1;
    }

    Image::~Image() {
        if (m_behavior)
        {
            delete m_behavior;
            m_behavior = nullptr;
        }
    }

}
