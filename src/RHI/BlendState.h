#include "./IPipelineResource.h"
#include <vector>

#ifndef BLENDSTATE_H
#define BLENDSTATE_H

namespace FCT {
    enum class BlendFactor {
        Zero, One, SrcColor, OneMinusSrcColor, DstColor, OneMinusDstColor,
        SrcAlpha, OneMinusSrcAlpha, DstAlpha, OneMinusDstAlpha,
        ConstantColor, OneMinusConstantColor, Src1Color, OneMinusSrc1Color,
        Src1Alpha, OneMinusSrc1Alpha
    };

    enum class BlendOp { Add, Subtract, ReverseSubtract, Min, Max };

    enum class LogicOp {
        Clear, And, AndReverse, Copy, AndInverted, NoOp, Xor, Or, Nor,
        Equivalent, Invert, OrReverse, CopyInverted, OrInverted, Nand, Set
    };

    class BlendState : public IPipelineResource {
    public:
        virtual ~BlendState() override = default;
        virtual void create() = 0;

        BlendState& enable(bool enable, int target = -1) {
            setForTargets(target, [=](auto& t) { t.enable = enable; });
            return *this;
        }

        BlendState& factors(BlendFactor src, BlendFactor dst, int target = -1) {
            setForTargets(target, [=](auto& t) {
                t.srcColor = t.srcAlpha = src;
                t.dstColor = t.dstAlpha = dst;
            });
            return *this;
        }

        BlendState& colorFactors(BlendFactor src, BlendFactor dst, int target = -1) {
            setForTargets(target, [=](auto& t) { t.srcColor = src; t.dstColor = dst; });
            return *this;
        }

        BlendState& alphaFactors(BlendFactor src, BlendFactor dst, int target = -1) {
            setForTargets(target, [=](auto& t) { t.srcAlpha = src; t.dstAlpha = dst; });
            return *this;
        }

        BlendState& op(BlendOp operation, int target = -1) {
            setForTargets(target, [=](auto& t) { t.colorOp = t.alphaOp = operation; });
            return *this;
        }

        BlendState& mask(uint8_t writeMask, int target = -1) {
            setForTargets(target, [=](auto& t) { t.mask = writeMask; });
            return *this;
        }

        BlendState& logic(LogicOp logicOp, bool enable = true) {
            m_logicOp = logicOp;
            m_logicEnable = enable;
            return *this;
        }

        BlendState& alpha(int target = -1) {
            return enable(true, target)
                  .factors(BlendFactor::SrcAlpha, BlendFactor::OneMinusSrcAlpha, target)
                  .op(BlendOp::Add, target);
        }

        BlendState& additive(int target = -1) {
            return enable(true, target)
                  .colorFactors(BlendFactor::SrcAlpha, BlendFactor::One, target)
                  .alphaFactors(BlendFactor::Zero, BlendFactor::One, target)
                  .op(BlendOp::Add, target);
        }

        BlendState& multiply(int target = -1) {
            return enable(true, target)
                  .factors(BlendFactor::DstColor, BlendFactor::Zero, target)
                  .op(BlendOp::Add, target);
        }

        BlendState& opaque(int target = -1) {
            return enable(false, target)
                  .factors(BlendFactor::One, BlendFactor::Zero, target);
        }

        BlendState& targets(int count) {
            m_targets.resize(count);
            return *this;
        }

        bool blendEnable() const { return m_targets.empty() ? false : m_targets[0].enable; }
        BlendFactor srcColorBlendFactor() const { return m_targets.empty() ? BlendFactor::One : m_targets[0].srcColor; }

        PipelineResourceType getType() const override { return PipelineResourceType::BlendState; }

    protected:
        struct Target {
            bool enable = false;
            BlendFactor srcColor = BlendFactor::One, dstColor = BlendFactor::Zero;
            BlendFactor srcAlpha = BlendFactor::One, dstAlpha = BlendFactor::Zero;
            BlendOp colorOp = BlendOp::Add, alphaOp = BlendOp::Add;
            uint8_t mask = 0xF;
        };

        std::vector<Target> m_targets{1};
        bool m_logicEnable = false;
        LogicOp m_logicOp = LogicOp::Copy;

        template<typename Func>
        void setForTargets(int target, Func func) {
            if (target == -1) {
                for (auto& t : m_targets) func(t);
            } else if (target < m_targets.size()) {
                func(m_targets[target]);
            }
        }
    };
}

#endif //BLENDSTATE_H