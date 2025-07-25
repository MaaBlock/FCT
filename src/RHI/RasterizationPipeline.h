//
// Created by Administrator on 2025/3/24.
//
#include "../MutilThreadBase/RefCount.h"
#include "./IPipelineResource.h"
#include "./Pipeline.h"
#include "./CommandBuffer.h"
#ifndef RASTERIZATION_PIPELINE_H
#define RASTERIZATION_PIPELINE_H
namespace FCT
{
    namespace RHI
    {
        class Pass;

        class RasterizationPipeline : public Pipeline
        {
        public:
            RasterizationPipeline() {}
            virtual ~RasterizationPipeline() {}
            virtual void addResources(IPipelineResource* resource) = 0;
            virtual void create() = 0;
            void bind(RHI::CommandBuffer* cmdBuffer)
            {
                cmdBuffer->bindPipieline(this);
            }
            /**
             * @pre must do this before call create()
             * @pre the Pass Group of the pass must be created
             * @param pass pass,The Pass Group of the pass must be created
             */
            virtual void bindPass(FCT::RHI::Pass* pass) = 0;
        protected:

        };

    }
}
#endif //RASTERIZATION_PIPELINE_H
