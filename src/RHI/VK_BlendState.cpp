#include "../FCTAPI.h"
namespace FCT
{
    VK_BlendState::VK_BlendState(VK_Context* ctx) : m_createInfo{}
    {
        m_ctx = ctx;
    }

    void VK_BlendState::create()
    {
        // 清理之前的状态
        m_attachmentStates.clear();
        m_attachmentStates.reserve(m_targets.size());

        // 为每个目标创建 attachment state
        for (const auto& target : m_targets) {
            vk::PipelineColorBlendAttachmentState attachmentState{};
            attachmentState.blendEnable = target.enable;
            attachmentState.srcColorBlendFactor = convertBlendFactor(target.srcColor);
            attachmentState.dstColorBlendFactor = convertBlendFactor(target.dstColor);
            attachmentState.colorBlendOp = convertBlendOp(target.colorOp);
            attachmentState.srcAlphaBlendFactor = convertBlendFactor(target.srcAlpha);
            attachmentState.dstAlphaBlendFactor = convertBlendFactor(target.dstAlpha);
            attachmentState.alphaBlendOp = convertBlendOp(target.alphaOp);
            attachmentState.colorWriteMask = static_cast<vk::ColorComponentFlags>(target.mask);
            
            m_attachmentStates.push_back(attachmentState);
        }

        m_createInfo = vk::PipelineColorBlendStateCreateInfo()
            .setLogicOpEnable(m_logicEnable)
            .setLogicOp(convertLogicOp(m_logicOp))
            .setAttachmentCount(static_cast<uint32_t>(m_attachmentStates.size()))
            .setPAttachments(m_attachmentStates.data())
            .setBlendConstants({0.0f, 0.0f, 0.0f, 0.0f});
    }

    vk::BlendFactor VK_BlendState::convertBlendFactor(BlendFactor factor) const
    {
        switch (factor)
        {
            case BlendFactor::Zero: return vk::BlendFactor::eZero;
            case BlendFactor::One: return vk::BlendFactor::eOne;
            case BlendFactor::SrcColor: return vk::BlendFactor::eSrcColor;
            case BlendFactor::OneMinusSrcColor: return vk::BlendFactor::eOneMinusSrcColor;
            case BlendFactor::DstColor: return vk::BlendFactor::eDstColor;
            case BlendFactor::OneMinusDstColor: return vk::BlendFactor::eOneMinusDstColor;
            case BlendFactor::SrcAlpha: return vk::BlendFactor::eSrcAlpha;
            case BlendFactor::OneMinusSrcAlpha: return vk::BlendFactor::eOneMinusSrcAlpha;
            case BlendFactor::DstAlpha: return vk::BlendFactor::eDstAlpha;
            case BlendFactor::OneMinusDstAlpha: return vk::BlendFactor::eOneMinusDstAlpha;
            case BlendFactor::ConstantColor: return vk::BlendFactor::eConstantColor;
            case BlendFactor::OneMinusConstantColor: return vk::BlendFactor::eOneMinusConstantColor;
            case BlendFactor::Src1Color: return vk::BlendFactor::eSrc1Color;
            case BlendFactor::OneMinusSrc1Color: return vk::BlendFactor::eOneMinusSrc1Color;
            case BlendFactor::Src1Alpha: return vk::BlendFactor::eSrc1Alpha;
            case BlendFactor::OneMinusSrc1Alpha: return vk::BlendFactor::eOneMinusSrc1Alpha;
            default: return vk::BlendFactor::eOne;
        }
    }

    vk::BlendOp VK_BlendState::convertBlendOp(BlendOp op) const
    {
        switch (op)
        {
            case BlendOp::Add: return vk::BlendOp::eAdd;
            case BlendOp::Subtract: return vk::BlendOp::eSubtract;
            case BlendOp::ReverseSubtract: return vk::BlendOp::eReverseSubtract;
            case BlendOp::Min: return vk::BlendOp::eMin;
            case BlendOp::Max: return vk::BlendOp::eMax;
            default: return vk::BlendOp::eAdd;
        }
    }

    vk::LogicOp VK_BlendState::convertLogicOp(LogicOp op) const
    {
        switch (op)
        {
            case LogicOp::Clear: return vk::LogicOp::eClear;
            case LogicOp::And: return vk::LogicOp::eAnd;
            case LogicOp::AndReverse: return vk::LogicOp::eAndReverse;
            case LogicOp::Copy: return vk::LogicOp::eCopy;
            case LogicOp::AndInverted: return vk::LogicOp::eAndInverted;
            case LogicOp::NoOp: return vk::LogicOp::eNoOp;
            case LogicOp::Xor: return vk::LogicOp::eXor;
            case LogicOp::Or: return vk::LogicOp::eOr;
            case LogicOp::Nor: return vk::LogicOp::eNor;
            case LogicOp::Equivalent: return vk::LogicOp::eEquivalent;
            case LogicOp::Invert: return vk::LogicOp::eInvert;
            case LogicOp::OrReverse: return vk::LogicOp::eOrReverse;
            case LogicOp::CopyInverted: return vk::LogicOp::eCopyInverted;
            case LogicOp::OrInverted: return vk::LogicOp::eOrInverted;
            case LogicOp::Nand: return vk::LogicOp::eNand;
            case LogicOp::Set: return vk::LogicOp::eSet;
            default: return vk::LogicOp::eCopy;
        }
    }
}