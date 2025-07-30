//
// Created by Administrator on 2025/3/31.
//

#include "../FCTAPI.h"
namespace FCT
{
    namespace RHI
    {
        VK_CommandBuffer::VK_CommandBuffer(VK_CommandPool* pool) : m_allocateInfo{}
        {
            m_pool = pool;
        }

        void VK_CommandBuffer::create()
        {
            switch (m_level)
            {
            case CommandBufferLevel::Primary:
                m_allocateInfo.level = vk::CommandBufferLevel::ePrimary;
                break;
            case CommandBufferLevel::Secondary:
                m_allocateInfo.level = vk::CommandBufferLevel::eSecondary;
                break;
            }
            m_allocateInfo.commandPool = m_pool->pool();
            m_allocateInfo.commandBufferCount = 1;
            m_commandBuffer = m_pool->context()->device().allocateCommandBuffers(m_allocateInfo)[0];
        }

        void VK_CommandBuffer::scissor(Vec2 lt, Vec2 rb)
        {
            vk::Rect2D scissor{};
            scissor.offset.x = static_cast<int32_t>(lt.x);
            scissor.offset.y = static_cast<int32_t>(lt.y);
            scissor.extent.width = static_cast<uint32_t>(rb.x - lt.x);
            scissor.extent.height = static_cast<uint32_t>(rb.y - lt.y);
            m_commandBuffer.setScissor(0,1, &scissor);
        }

        void VK_CommandBuffer::bindPipieline(RasterizationPipeline* pipeline)
        {
            switch (pipeline->getType())
            {
            case PipelineType::Traditional:
                {
                    auto vkPipeline = static_cast<VK_TraditionalPipeline*>(pipeline);
                    m_commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics,vkPipeline->pipeline());
                }
                break;
            }
        }

        void VK_CommandBuffer::submit()
        {
            vk::SubmitInfo submitInfo{};
            submitInfo.setCommandBuffers(m_commandBuffer);
            std::vector<vk::Semaphore> waitSemaphores;
            std::vector<vk::PipelineStageFlags> waitStages;
            for (auto& desc : m_waitSemaphores)
            {
                waitSemaphores.push_back(static_cast<VK_Semaphore*>(desc.semaphore)->semaphore());
                waitStages.push_back(ToVkPipelineStageFlags(desc.stages));
            }
            submitInfo.setWaitSemaphores(waitSemaphores);
            submitInfo.setWaitDstStageMask(waitStages);
            std::vector<vk::Semaphore> signalSemaphores;
            for (auto& signalSemaphore : m_signalSemaphores)
            {
                signalSemaphores.push_back(static_cast<VK_Semaphore*>(signalSemaphore)->semaphore());
            }
            submitInfo.setSignalSemaphores(signalSemaphores);
            m_pool->context()->getGraphicsQueue().submit(submitInfo,
                static_cast<VK_Fence*>(m_fence)->fence());
        }
    }
}
