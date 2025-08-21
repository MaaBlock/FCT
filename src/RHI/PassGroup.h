//
// Created by Administrator on 2025/3/25.
//
#ifndef FCT_RHI_PASSGROUP_H
#define FCT_RHI_PASSGROUP_H
#include "../MutilThreadBase/RefCount.h"
#include "../Context/IRenderTarget.h"
#include "./CommandBuffer.h"
#include "./Pass.h"
#include "./PipelineStage.h"
#include "./AccessFlags.h"
namespace FCT
{
    namespace RHI
    {
        struct PassNeighbors
        {
            PassNeighbors(Pass* pass) :
                pass(pass),needComputeStage(true)
            {

            }
            PassNeighbors(Pass* pass,
                PipelineStages neighborStage,AccessFlags neighborAccess,
                PipelineStages currentStage, AccessFlags currentAccess)
                : pass(pass),
                neighborStage(neighborStage),
                neighborAccess(neighborAccess),
                currentStage(currentStage),
                currentAccess(currentAccess),
                needComputeStage(false)
            {
            }
            Pass* pass;
            PipelineStages neighborStage;
            AccessFlags neighborAccess;
            PipelineStages currentStage;
            AccessFlags currentAccess;
            bool needComputeStage;
        };
        struct PassDesc
        {
            Pass* pass;
            std::vector<PassNeighbors> predecessors;
            std::vector<PassNeighbors> successors;
        };
        class PassGroup : public RefCount
        {
        public:
            PassGroup()
            {

            }
            virtual ~PassGroup()
            {

            }
            virtual void beginSubmit(CommandBuffer* cmdBuf) = 0;
            virtual void endSubmit(CommandBuffer* cmdBuf) = 0;
            virtual void create() = 0;
            /**
             * @cond CHINESE
             * @brief 开始下一个pass的 提交
             * @note pass提交顺序等于pass添加顺序不等于pass执行顺序
             *       pass提交顺序只是把pass里的命令提交到 gpu的顺序，在gpu里的执行顺序由pass间的依赖关系决定
             * @param cmdBuf
             * @endcond
             */
            virtual void nextPass(CommandBuffer* cmdBuf) = 0;
            void addPass(Pass* pass);
            void addPass(const PassDesc& desc);
        protected:
            void computeStage();
            void computeStage(PassDesc passDesc);
            std::vector<PassGroup*> m_prevPassGroup;
            std::vector<PassGroup*> m_nextPassGroup;
            std::vector<Pass*> m_passes;
            std::vector<PassDesc> m_passDescs;
        };
    }
}
#endif //FCT_RHI_PASSGROUP_H
