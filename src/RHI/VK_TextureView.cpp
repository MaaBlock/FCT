//
// Created by Administrator on 2025/4/15.
//

#include "VK_TextureView.h"

#include "VK_Image.h"
#include "../Context/VK_Context.h"

namespace FCT
{
    namespace RHI
    {
        VK_TextureView::VK_TextureView(VK_Context* ctx)
            : m_ctx(ctx), m_view(nullptr)
        {
        }

        VK_TextureView::~VK_TextureView()
        {
            if (m_view) {
                m_ctx->getDevice().destroyImageView(m_view);
                m_view = nullptr;
            }
        }

        void VK_TextureView::create()
        {
            if (!m_image) {
                ferr << "Cannot create texture view: no image set" << std::endl;
                return;
            }

            VK_Image* vkImage = dynamic_cast<VK_Image*>(m_image);
            if (!vkImage) {
                ferr << "Cannot create texture view: image is not a VK_Image" << std::endl;
                return;
            }

            Format format = m_image->format();
            vk::ImageViewType viewType = vk::ImageViewType::e2D;

            vk::ImageAspectFlags aspectMask = getImageAspectFlags(ToVkFormat(format));


            vk::ImageViewCreateInfo viewInfo;
            viewInfo.setImage(vkImage->getVkImage());
            viewInfo.setViewType(viewType);
            viewInfo.setFormat(ToVkFormat(format));

            viewInfo.components.r = vk::ComponentSwizzle::eR;
            viewInfo.components.g = vk::ComponentSwizzle::eG;
            viewInfo.components.b = vk::ComponentSwizzle::eB;
            viewInfo.components.a = vk::ComponentSwizzle::eA;

            viewInfo.subresourceRange.aspectMask = aspectMask;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            try {
                m_view = m_ctx->getDevice().createImageView(viewInfo);
            }
            catch (const std::exception& e) {
                ferr << "Failed to create texture view: " << e.what() << std::endl;
                m_view = nullptr;
            }
        }
        vk::ImageAspectFlags VK_TextureView::getImageAspectFlags(vk::Format format)
        {
            if (format == vk::Format::eD16Unorm ||
                format == vk::Format::eD32Sfloat ||
                format == vk::Format::eX8D24UnormPack32) {
                return vk::ImageAspectFlagBits::eDepth;
                }

            if (format == vk::Format::eD24UnormS8Uint ||
                format == vk::Format::eD32SfloatS8Uint ||
                format == vk::Format::eD16UnormS8Uint) {
                return vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil;
                }

            if (format == vk::Format::eS8Uint) {
                return vk::ImageAspectFlagBits::eStencil;
            }

            return vk::ImageAspectFlagBits::eColor;
        }
    }
}