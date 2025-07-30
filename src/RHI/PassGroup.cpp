#include "./PassGroup.h"
namespace FCT {
    namespace RHI
    {
        void PassGroup::addPass(Pass* pass)
        {
            addPass(
                {
                    pass,
                    {
                        {Pass::begin},
                    },
                    {
                        {Pass::present},
                    }
                });
        }

        void PassGroup::addPass(const PassDesc& desc)
        {
            m_passDescs.push_back(desc);
            desc.pass->index(m_passes.size());
            m_passes.push_back(desc.pass);
        }

        void PassGroup::computeStage()
        {
            for (const auto& desc : m_passDescs)
            {
                computeStage(desc);
            }
        }

        void PassGroup::computeStage(PassDesc passDesc)
        {
            for (auto& pre : passDesc.predecessors)
            {
                if (pre.needComputeStage)
                {
                    if (pre.pass == Pass::begin)
                    {
                        pre.currentAccess = AccessFlag::colorAttachmentWrite | AccessFlag::depthStencilAttachmentWrite;
                        pre.currentStage = PipelineStage::colorAttachmentOutput | PipelineStage::earlyFragmentTests;

                        pre.neighborAccess = AccessFlag::none;  // 开始时没有访问
                        pre.neighborStage = PipelineStage::topOfPipe;  // 管线顶部
                        continue;
                    }
                    if (pre.pass == Pass::external)
                    {
                        continue;
                    }
                    /**
                     *Todo:自动推导逻辑
                     */
                }
            }
            for (auto post : passDesc.successors)
            {
                if (post.pass == Pass::present)
                {
                    post.currentAccess = AccessFlag::colorAttachmentWrite | AccessFlag::depthStencilAttachmentWrite;
                    post.currentStage = PipelineStage::colorAttachmentOutput | PipelineStage::lateFragmentTests;
                    post.neighborAccess = AccessFlag::memoryRead;
                    post.neighborStage = PipelineStage::bottomOfPipe;
                    continue;
                }
                if (post.pass == Pass::external)
                {
                    continue;
                }
                /**
                 *Todo:自动推导逻辑
                 */
            }
        }
    }
}