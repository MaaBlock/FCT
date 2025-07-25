//
// Created by Administrator on 2025/3/4.
//
#include "../ThirdParty.h"
#include "../ToolDefine.h"
#include "../Context//VK_Context.h"
#include "./Swapcain.h"
#include "./VK_Image.h"
#include "VK_Semaphore.h"
#include "../Context/ImageRenderTarget.h"
#include "../Context/MutilBufferImage.h"
#ifndef FCT_VK_SWAPCHAIN_H
#define FCT_VK_SWAPCHAIN_H
namespace FCT{
    namespace RHI
    {
        class VK_Swapchain : public Swapchain {
        public:
            VK_Swapchain(VK_Context* ctx);
            ~VK_Swapchain();
            void create(vk::SurfaceKHR surface, uint32_t width, uint32_t height);
            void create() override;
            void destroy();
            uint32_t getCurrentImageIndex() const;
            void present() override;
            bool acquireFirstImage();
            void needRecreate(int width, int height) override;
            bool processRecreate(bool waitFence = false);
            void enableDepthBuffer(Format format) override;
            /*
            vk::Semaphore getImageAvailableSemaphore() const;
            vk::Semaphore getRenderFinishedSemaphore() const;*/
            vk::Fence getInFlightFence() const;
            vk::Extent2D getExtent() const;
            Format getFormat() const override;
            Samples getSamples() const override;
            ImageRenderTarget* target() const override ;
            void setPresentFinshSemaphore(RHI::Semaphore* semaphore) override;
            RHI::Semaphore* getImageAvailableSemaphore() override;
            uint32_t getImageCount() const override
            {
                return m_fctImages.size();
            }
            Samples getSampleCount() const override;
            FCT::Image* image() const override
            {
                return m_fctImage;
            }
            bool doRecreate();
            void sync() override;
        private:

            void cleanupOldResources();
            void setupQueueFamilies();
            vk::SwapchainCreateInfoKHR buildSwapchainCreateInfo(const vk::SurfaceFormatKHR& format,
                                                                vk::PresentModeKHR presentMode,
                                                                const vk::Extent2D& extent, uint32_t imageCount,
                                                                const vk::SurfaceCapabilitiesKHR& capabilities,
                                                                uint32_t graphicsQueueFamily);
            void createSwapchain(uint32_t width, uint32_t height);
            void createImagesAndTargets();
            bool m_recreated;
            bool m_needRecreated;
            bool m_recreatedFlag;
            MutilBufferImage* m_fctImage;
            MutilBufferImage* m_depthStencilImage;
            std::vector<RHI::Image*> m_fctImages;
            ImageRenderTarget* m_target;
            vk::Format m_imageFormat;
            std::vector<vk::Queue> m_presentQueues;
            vk::Queue m_presentQueue;
            uint32_t m_presentQueueFamilyIndex;
            VK_Context* m_ctx;
            vk::SurfaceKHR m_surface;
            vk::SwapchainKHR m_swapchain;
            vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
            vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes);
            std::vector<vk::Image> m_images;
            //std::vector<vk::ImageView> m_imageViews;
            size_t m_currentFrame = 0;
            vk::Extent2D m_extent;
            uint32_t m_currentImageIndex = 0;
            RHI::VK_Semaphore* m_prensentFinshSemphore;
            static constexpr uint32_t RECREATE_DEBOUNCE_MS = 50;
            std::chrono::high_resolution_clock::time_point m_lastRecreateRequestTime;
            /**
             * @cond CHINESE
             * @brief 窗口resize的时候传递的大小
             * @endcond
             * @cond ENGLISH
             * @brief The size passed to the window resize callback
             * @endcond
             */
            uint32_t m_pendingWidth = 0, m_pendingHeight = 0;
        };

        inline void VK_Swapchain::enableDepthBuffer(Format format)
        {
            m_depthStencilImage = new MutilBufferImage(m_ctx);
            m_depthStencilImage->width(m_width);
            m_depthStencilImage->height(m_height);
            m_depthStencilImage->format(format);
            m_depthStencilImage->samples(Samples::sample_1);
            m_depthStencilImage->as(ImageUsage::DepthStencil);
            m_depthStencilImage->imageCount(m_images.size());
            m_depthStencilImage->create();
            m_target->setDepthStencilBuffer(m_depthStencilImage);
        }
    }
}

#endif //FCT_VK_SWAPCHAIN_H