//
// Created by Administrator on 2025/7/30.
//

#ifndef PIPELINESTAGE_H
#define PIPELINESTAGE_H
#include "../ThirdParty.h"
#include "../Base/Flags.h"
namespace FCT {
    enum class PipelineStage : uint32_t {

        colorAttachmentOutput = 1 << 0,
        earlyFragmentTests = 1 << 1,
        bottomOfPipe = 1 << 2,
        topOfPipe = 1 << 3,
        lateFragmentTests = 1 << 4,
    };
    FCT_DECLARE_FLAGS(PipelineStage);
#ifdef FCT_USE_VULKAN
    inline vk::PipelineStageFlagBits ToVkFlagBits(FCT::PipelineStage pipelineStage)
    {
        switch (pipelineStage) {
            case FCT::PipelineStage::colorAttachmentOutput:
                return vk::PipelineStageFlagBits::eColorAttachmentOutput;
            case FCT::PipelineStage::earlyFragmentTests:
                return vk::PipelineStageFlagBits::eEarlyFragmentTests;
            case FCT::PipelineStage::bottomOfPipe:
                return vk::PipelineStageFlagBits::eBottomOfPipe;
            case FCT::PipelineStage::topOfPipe:
                return vk::PipelineStageFlagBits::eTopOfPipe;
            case FCT::PipelineStage::lateFragmentTests:
                return vk::PipelineStageFlagBits::eLateFragmentTests;
            default:
                return static_cast<vk::PipelineStageFlagBits>(0);
        }
    }
    inline vk::PipelineStageFlags ToVkPipelineStageFlags(FCT::PipelineStages pipelineStages)
    {
        vk::PipelineStageFlags result;

        for (uint32_t i = 0; i < 32; ++i) {
            FCT::PipelineStage singleStage = static_cast<FCT::PipelineStage>(1u << i);
            if (pipelineStages & singleStage) {
                result |= ToVkFlagBits(singleStage);
            }
        }

        return result;
    }
#endif
}
#endif //PIPELINESTAGE_H
