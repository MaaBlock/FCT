//
// Created by Administrator on 2025/7/27.
//
#include "./VK_Context.h"
#include "./VK_Device.h"
#include "./VertexShader.h"
#include "./PixelShader.h"
#include "../RHI/VK_VertexShader.h"
#include "../RHI/VK_PixelShader.h"
#include "../RHI/VK_ConstBuffer.h"
#include "../RHI/VK_InputLayout.h"
#include "./SingleBufferImage.h"
#include "./MutilBufferImage.h"
#include "../RHI/VK_Image.h"
#include "../RHI/VK_Swapchain.h"
#include "../RHI/VK_PassGroup.h"
#include "../RHI/VK_Pass.h"
#include "../RHI/VK_Fence.h"
#include "../RHI/VK_Semaphore.h"
#include "../RHI/VK_CommandPool.h"
#include "../RHI/VK_VertexBuffer.h"
#include "../RHI/VK_IndexBuffer.h"
#include "../RHI/VK_DescriptorPool.h"
#include "../RHI/VK_DepthStencilView.h"
#include "../RHI/VK_TextureView.h"
#include "../RHI/VK_BlendState.h"
#include "../RHI/VK_Sampler.h"
#include "./VK_PassResource.h"
#include "./VK_SemaphorePool.h"
#include "./VK_FencePool.h"

namespace FCT
{
    VK_Device::VK_Device(VK_Context* ctx)
    {
        m_ctx = ctx;
    }

    VertexShader* VK_Device::newVertexShader()
    {
        return new VertexShader(m_ctx);
    }

    PixelShader* VK_Device::newPixelShader()
    {
        return new PixelShader(m_ctx);
    }

    RHI::VertexShader* VK_Device::newRhiVertexShader()
    {
        return new RHI::VK_VertexShader(m_ctx);
    }

    RHI::PixelShader* VK_Device::newRhiPixelShader()
    {
        return new RHI::VK_PixelShader(m_ctx);
    }

    RHI::ConstBuffer* VK_Device::newRhiConstBuffer()
    {
        return new RHI::VK_ConstBuffer(m_ctx);
    }

    RHI::InputLayout* VK_Device::newRhiInputLayout()
    {
        return new RHI::VK_InputLayout(m_ctx);
    }

    SingleBufferImage* VK_Device::newSingleBufferImage()
    {
        return new SingleBufferImage(m_ctx);
    }

    MutilBufferImage* VK_Device::newMutilBufferImage()
    {
        return new MutilBufferImage(m_ctx);
    }

    RHI::Image* VK_Device::newRhiImage()
    {
        return new RHI::VK_Image(m_ctx);
    }

    RHI::Swapchain* VK_Device::newRhiSwapchain()
    {
        return new RHI::VK_Swapchain(m_ctx);
    }

    RHI::PassGroup* VK_Device::newRhiPassGroup()
    {
        return new RHI::VK_PassGroup(m_ctx);
    }

    RHI::Pass* VK_Device::newRhiPass()
    {
        return new RHI::VK_Pass(m_ctx);
    }

    RHI::Fence* VK_Device::newRhiFence()
    {
        return new RHI::VK_Fence(m_ctx);
    }

    RHI::Semaphore* VK_Device::newRhiSemaphore()
    {
        return new RHI::VK_Semaphore(m_ctx);
    }

    RHI::CommandPool* VK_Device::newRhiCommandPool()
    {
        return new RHI::VK_CommandPool(m_ctx);
    }

    RHI::VertexBuffer* VK_Device::newRhiVertexBuffer()
    {
        return new RHI::VK_VertexBuffer(m_ctx);
    }

    RHI::IndexBuffer* VK_Device::newRhiIndexBuffer()
    {
        return new RHI::VK_IndexBuffer(m_ctx);
    }

    RHI::DescriptorPool* VK_Device::newRhiDescriptorPool()
    {
        return new RHI::VK_DescriptorPool(m_ctx);
    }

    RHI::DepthStencilView* VK_Device::newRhiDepthStencilView()
    {
        return new RHI::VK_DepthStencilView(m_ctx);
    }

    RHI::TextureView* VK_Device::newRhiTextureView()
    {
        return new RHI::VK_TextureView(m_ctx);
    }

    BlendState* VK_Device::newBlendState()
    {
        return new VK_BlendState(m_ctx);
    }

    Sampler* VK_Device::newSampler()
    {
        return new RHI::VK_Sampler(m_ctx);
    }

    PassResource* VK_Device::newPassResource()
    {
        return new VK_PassResource(m_ctx);
    }

    SemaphorePool* VK_Device::newSemaphorePool()
    {
        return new VK_SemaphorePool(m_ctx);
    }

    FencePool* VK_Device::newFencePool()
    {
        return new VK_FencePool(m_ctx);
    }
}