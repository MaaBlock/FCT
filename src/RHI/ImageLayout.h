//
// Created by Administrator on 2025/8/2.
//

#ifndef IMAGELAYOUT_H
#define IMAGELAYOUT_H
#include "../Base/Enums.h"
namespace FCT {
    enum class ImageLayout
    {
        undefined,
        general,
        colorAttachmentOptimal,
        depthStencilAttachmentOptimal,
        depthStencilReadOnlyOptimal,
        shaderReadOnlyOptimal,
        transferSrcOptimal,
        transferDstOptimal,
        preinitialized,
        depthReadOnlyStencilAttachmentOptimal,
        depthAttachmentStencilReadOnlyOptimal,
        depthAttachmentOptimal,
        depthReadOnlyOptimal,
        stencilAttachmentOptimal,
        stencilReadOnlyOptimal,
        readOnlyOptimal,
        attachmentOptimal,
        renderingLocalRead,
        presentSrcKHR,
        videoDecodeDstKHR,
        videoDecodeSrcKHR,
        videoDecodeDpbKHR,
        sharedPresentKHR,
        fragmentDensityMapOptimalEXT,
        fragmentShadingRateAttachmentOptimalKHR,
        shadingRateOptimalNV,
        videoEncodeDstKHR,
        videoEncodeSrcKHR,
        videoEncodeDpbKHR,
        attachmentFeedbackLoopOptimalEXT,
        videoEncodeQuantizationMapKHR
    };
#ifdef FCT_USE_VULKAN
    FCT_TO_VK_ENUM_BEGIN(ImageLayout)
    FCT_TO_VK_ENUM_CASE(ImageLayout, undefined, Undefined)
    FCT_TO_VK_ENUM_CASE(ImageLayout, general, General)
    FCT_TO_VK_ENUM_CASE(ImageLayout, colorAttachmentOptimal, ColorAttachmentOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, depthStencilAttachmentOptimal, DepthStencilAttachmentOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, depthStencilReadOnlyOptimal, DepthStencilReadOnlyOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, shaderReadOnlyOptimal, ShaderReadOnlyOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, transferSrcOptimal, TransferSrcOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, transferDstOptimal, TransferDstOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, preinitialized, Preinitialized)
    FCT_TO_VK_ENUM_CASE(ImageLayout, depthReadOnlyStencilAttachmentOptimal, DepthReadOnlyStencilAttachmentOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, depthAttachmentStencilReadOnlyOptimal, DepthAttachmentStencilReadOnlyOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, depthAttachmentOptimal, DepthAttachmentOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, depthReadOnlyOptimal, DepthReadOnlyOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, stencilAttachmentOptimal, StencilAttachmentOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, stencilReadOnlyOptimal, StencilReadOnlyOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, readOnlyOptimal, ReadOnlyOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, attachmentOptimal, AttachmentOptimal)
    FCT_TO_VK_ENUM_CASE(ImageLayout, renderingLocalRead, RenderingLocalRead)
    FCT_TO_VK_ENUM_CASE(ImageLayout, presentSrcKHR, PresentSrcKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, videoDecodeDstKHR, VideoDecodeDstKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, videoDecodeSrcKHR, VideoDecodeSrcKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, videoDecodeDpbKHR, VideoDecodeDpbKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, sharedPresentKHR, SharedPresentKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, fragmentDensityMapOptimalEXT, FragmentDensityMapOptimalEXT)
    FCT_TO_VK_ENUM_CASE(ImageLayout, fragmentShadingRateAttachmentOptimalKHR, FragmentShadingRateAttachmentOptimalKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, shadingRateOptimalNV, ShadingRateOptimalNV)
    FCT_TO_VK_ENUM_CASE(ImageLayout, videoEncodeDstKHR, VideoEncodeDstKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, videoEncodeSrcKHR, VideoEncodeSrcKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, videoEncodeDpbKHR, VideoEncodeDpbKHR)
    FCT_TO_VK_ENUM_CASE(ImageLayout, attachmentFeedbackLoopOptimalEXT, AttachmentFeedbackLoopOptimalEXT)
    FCT_TO_VK_ENUM_CASE(ImageLayout, videoEncodeQuantizationMapKHR, VideoEncodeQuantizationMapKHR)
    FCT_TO_VK_ENUM_END(ImageLayout)
#endif
}
#endif //IMAGELAYOUT_H
