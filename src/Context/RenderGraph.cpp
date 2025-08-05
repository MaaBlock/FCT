//
// Created by Administrator on 2025/8/5.
//

#include "RenderGraph.h"
#include "Context.h"
namespace FCT {
    RenderGraph::RenderGraph(Context* ctx)
    {
        m_ctx = ctx;
        m_device = m_ctx->getModule<Device>();
    }

    RenderGraph::~RenderGraph()
    {

    }
} // FCT