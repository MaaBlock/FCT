//
// Created by Administrator on 2025/3/26.
//
#include "Fence.h"
#include "../MutilThreadBase/RefCount.h"
#include "../Context/Format.h"
#include "../Context/ImageRenderTarget.h"
#include "../RHI/Semaphore.h"
#ifndef FCT_SWAPCAIN_H
#define FCT_SWAPCAIN_H
namespace FCT
{
    namespace RHI
    {
        class Swapchain : public RefCount
        {
        public:
            Swapchain()
            {
                m_nativeHandle = nullptr;
                m_width = 0;
                m_height = 0;
                m_hasRecreatedInThisFrame = false;
            }
            /**
             * @cond CHINESE
             * @return 缓存数
             * @endcond
             */
            virtual uint32_t getImageCount() const = 0;
            /**
             * @cond CHINESE
             * @return 与getSamples相同
             * @endcond
             */
            virtual Samples getSampleCount() const = 0;
            virtual ~Swapchain() = default;
            /**
             * @cond CHINESE
             * @brief 传递 surface
             * @param handle 传递了surface
             * @endcond
             */
            void nativeHandle(void* handle)
            {
                m_nativeHandle = handle;
            }
            /**
             * @cond CHINESE
             * @param width 目标宽度
             * @param height 目标高度
             * @endcond
             */
            void size(int width,int height)
            {
                m_dstWidth = width;
                m_dstHeight = height;
            }

            /**
             * @cond CHINESE
             * @return 交换链对应的图像，是一个多缓存图像
             * @endcond
             */
            virtual FCT::Image* image() const = 0;
            /**
             * @cond CHINESE
             * @brief 启用深度模板 缓存
             * @param format 深度模板缓存的格式
             * @endcond
             */
            virtual void enableDepthBuffer(Format format) = 0;
            virtual void create() = 0;
            /**
             * @cond CHINESE
             * @brief 提交present命令
             * @note 其中 包含提交present命令和获取下一个图像俩个 命令，
             * 失败任一一个会触发重建交换 链（如果是因为交换链过时（既窗口改变大小）导致的话）
             * @endcond
             */
            virtual void present() = 0;
            virtual Format getFormat() const = 0;
            /**
             * @cond CHINESE
             * @return 交换链对应的图像的 采样 数
             * @endcond
             */
            virtual Samples getSamples() const = 0;
            virtual bool acquireFirstImage() = 0;
            /**
             * @cond CHINESE
             * @brief 获取交换链对应的target
             * @return 交换链对应的target
             * @endcond
             */
            virtual ImageRenderTarget* target() const = 0;
            /**
             * @cond CHINESE
             * @brief 用于渲染命令同步的，获取到 图像，gpu可以执行渲染命令
             * @return gpu获取到图像发出的信号量
             * @endcond
             */
            virtual RHI::Semaphore* getImageAvailableSemaphore() = 0;
            virtual void setPresentFinshSemaphore(RHI::Semaphore* semaphore) = 0;
            /**
             * @cond CHINESE
             * @brief 用于窗口通知需要 recreate
             * @param width 新的width
             * @param height 新的height
             * @endcond
             */
            virtual void needRecreate(int width,int height) = 0;
            /**
             * @cond CHINESE
             * @note 主要用来实现max frame in flight，该fence是渲染所必须的
             * @param fence 在提交完present后，获取下一帧图像前等待的fence，
             *      既下一个渲染帧的资源渲染完毕的fence
             * @endcond
             */
            void addRenderFinshFence(RHI::Fence* fence)
            {
                m_renderFinshFences.push_back(fence);
            }
            void clearRenderFinshFences()
            {
                m_renderFinshFences.clear();
            }
            /**
             * @cond CHINESE
             * @brief 渲染完毕以后发出的 信号，是present命令所必须的
             * @param semaphore 渲染完毕以后发出的 信号，是present命令所必须的
             * @endcond
             */
            void addRenderFinshSemaphore(RHI::Semaphore* semaphore)  {
                m_renderFinshSemaphores.push_back(semaphore);
            }
            void clearRenderFinshSemaphores()  {
                m_renderFinshSemaphores.clear();
            }
            virtual void sync() = 0;
            /**
             * @cond CHINESE
             * @brief 在syncGraph里 的判断是否要recreate节点是否进行了重建交换链， 可持续一帧
             * @return 是否进行了重建交换链
             * @endcond
             */
            bool hasRecreatedInThisFrame() const
            {
                return m_hasRecreatedInThisFrame;
            }
        protected:
            std::vector<RHI::Fence*> m_renderFinshFences;
            std::vector<RHI::Semaphore*> m_renderFinshSemaphores;
            /**
             * @cond CHINESE
             * @brief 交换链对应的surface
             * @endcond
             */
            void* m_nativeHandle;
            /**
             * @cond CHINESE
             * @brief 创建交换链后得到的实际大小
             * @endcond
             * @cond ENGLISH
             * @brief The actual size after creating the swapchain
             * @endcond
             */
            uint32_t m_width;
            /**
             * @cond CHINESE
             * @brief 创建交换链后得到的实际大小
             * @endcond
             * @cond ENGLISH
             * @brief The actual size after creating the swapchain
             * @endcond
             */
            uint32_t m_height;
            /**
             * @cond CHINESE
             * @brief 目标大小
             * @endcond
             * @cond ENGLISH
             * @brief The target size
             * @endcond
             */
            uint32_t m_dstWidth = 0;
            /**
             * @cond CHINESE
             * @brief 目标大小
             * @endcond
             * @cond ENGLISH
             * @brief The target size
             * @endcond
             */
            uint32_t m_dstHeight = 0;
            bool m_hasRecreatedInThisFrame;
        };
    }
}
#endif //FCT_SWAPCAIN_H
