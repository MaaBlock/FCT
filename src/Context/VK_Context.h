//
// Created by Administrator on 2025/3/1.
//
#ifndef VK_CONTEXT_H
#define VK_CONTEXT_H
#include "../ThirdParty.h"
#include "./Context.h"

namespace FCT {
    class VK_ContextCommon;
    class VK_Context : public Context {
    public:
        VK_Context(VK_ContextCommon* common);
        ~VK_Context() override;
        RHI::RasterizationPipeline* createTraditionPipeline() override;
        //void create(IRenderTarget* target) override;
        uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties);
        void createPlatform();
        auto device()
        {
            return m_device;
        }
        auto getDevice() const {
            return m_device;
        }
        auto getPhysicalDevice() const {
            return m_phyDevice;
        }

        vk::Instance getVkInstance();
        void beginCommandBuffer(int index);
        void endCommandBuffer(int index);
        void submitCommandBuffer();

        void clear(Vec4 color,float depth = 1.0,float stencil = 0.0){

        }
        uint32_t getGraphicsQueueFamily() const;
        void createTransferCommandPool();
        vk::CommandBuffer beginSingleTimeTransferCommands();
        void endSingleTimeTransferCommands(vk::CommandBuffer commandBuffer, vk::Fence* outFence);

        vk::Queue getGraphicsQueue()
        {
            return m_graphicsQueue;
        }

        vk::CommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(vk::CommandBuffer commandBuffer);
        void transferDataToBuffer(vk::Buffer dstBuffer, size_t size, const void* data);
        void transferDataToImage(vk::Image dstImage, uint32_t width, uint32_t height, vk::Format format,
                                 const void* data,
                                 size_t dataSize, vk::Fence* outFence = nullptr, std::function<void()>* cleanUpCallback = nullptr);
        void transferDataToImage(vk::Image dstImage, uint32_t width, uint32_t height, uint32_t depth, vk::Format format,
                                 uint32_t mipLevels, uint32_t arrayLayers, vk::ImageAspectFlags aspectMask,
                                 const void* data,
                                 size_t dataSize, vk::Fence* outFence = nullptr, std::function<void()>* cleanUpCallback = nullptr);

    private:
        void createCommandPoolAndBuffers();
        VK_ContextCommon* m_common;
        uint32_t m_graphicsQueueFamilyIndex;
        vk::Device m_device;
        vk::PhysicalDevice m_phyDevice;
        vk::Queue m_graphicsQueue;
        vk::CommandPool m_commandPool;
        std::vector<vk::CommandBuffer> m_commandBuffers;

        uint32_t m_transferQueueFamilyIndex;
        vk::Queue m_transferQueue;
        vk::CommandPool m_transferCommandPool;
    };
}

#endif //VK_CONTEXT_H
