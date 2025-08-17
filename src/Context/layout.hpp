//
// Created by Administrator on 2025/8/17.
//

#ifndef LAYOUT_HPP
#define LAYOUT_HPP
#include "layout.h"
#include "../RHI/RasterizationPipeline.h"
#include "PassResource.h"

namespace FCT
{
    template <typename T>
    void Layout::drawMesh(RHI::CommandBuffer* cmdBuffer, T* mesh)
    {
        auto resource = getCurrentPassResource();
        auto pipeline = getCurrentPipeline();

        pipeline->bind(cmdBuffer);
        resource->bind(cmdBuffer,pipeline);
        mesh->bind(cmdBuffer);
        mesh->draw(cmdBuffer);
    }

    template <typename T>
    void Layout::drawMesh(RHI::CommandBuffer* cmdBuffer, T& mesh)
    {
        auto resource = getCurrentPassResource();
        auto pipeline = getCurrentPipeline();

        pipeline->bind(cmdBuffer);
        resource->bind(cmdBuffer,pipeline);
        mesh.bind(cmdBuffer);
        mesh.draw(cmdBuffer);
    }
}
#endif //LAYOUTS_H
