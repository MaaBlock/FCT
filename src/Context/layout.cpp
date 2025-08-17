#include "layout.h"
#include "layout.hpp"
#include "./PixelShader.h"
#include "./VertexShader.h"
#include "PassResource.h"
#include "../RHI/RasterizationPipeline.h"
#include "../RHI/BlendState.h"
#include "../RHI/RasterizationState.h"
#include "../RHI/DepthStencilState.h"
#include "Context.hpp"

namespace FCT
{
    void Layout::ctx(FCT::Context* ctx)
    {
        m_ctx = ctx;
    }

    void Layout::setFixedImage(std::string name, FCT::Image* image)
    {
        m_fixedImages[name] = image;
    }

    void Layout::addTextureSlot(FCT::TextureElement element)
    {
        m_resourceLayout.addTexture(element);
        if (element.getShaderStages() & FCT::ShaderStage::Vertex)
        {
            m_vertexResourceLayout.addTexture(element);
        }
        if (element.getShaderStages() & FCT::ShaderStage::Fragment)
        {
            m_pixelResourceLayout.addTexture(element);
        }
    }

    void Layout::attachPass(FCT::RenderGraph* graph, std::string passName)
    {
        auto edges = graph->getTextureEdges(passName);
        for (auto edge : edges)
        {
            FCT::TextureElement element(FCT::TextureType::Texture2D,edge->fromImage.c_str(),getAllAfterTheStage(edge->stage),FCT::UpdateFrequency::PerFrame);
            addTextureSlot(element);
            setFixedImage(edge->fromImage,graph->getImage(edge->fromImage));
        }
        m_pass = graph->getPass(passName);
    }

    Uniform Layout::allocateUniform(std::string name)
    {
        return std::move(Uniform(m_ctx,m_uniformLayouts[name]));
    }

    FCT::VertexShader* Layout::allocateVertexShader(std::string code)
    {
        auto ret = m_ctx->createResource<FCT::ContextResource::VertexShader>();
        for (auto& layout : m_vertexLayouts)
        {
            ret->addLayout(layout.first,layout.second);
        }
        ret->pixelLayout(m_pixelLayout);
        for (auto& uniform : m_uniformLayouts)
        {
            ret->addUniform(uniform.second);
        }
        ret->resourceLayout(m_vertexResourceLayout);
        ret->code(code);
        ret->create();
        return ret;
    }

    FCT::PixelShader* Layout::allocatePixelShader(std::string code)
    {
        auto ret = m_ctx->createResource<FCT::ContextResource::PixelShader>();

        for (auto& layout : m_uniformLayouts)
        {
            ret->addUniform(layout.second);
        }
        ret->pixelLayout(m_pixelLayout);
        ret->resourceLayout(m_pixelResourceLayout);
        ret->code(code);
        ret->create();
        return ret;
    }

    void Layout::begin()
    {
        m_passResourceState.clear();

        for (const auto& fixedImage : m_fixedImages)
        {
            m_passResourceState.bindTexture(fixedImage.first, fixedImage.second);
        }

        m_pipelineState = TraditionPipelineState();
    }

    void Layout::bindUniform(const Uniform& uniform)
    {
        std::string name = (static_cast<FCT::RHI::ConstBuffer*>(uniform))->layout().getName(); // 你可能需要在 Uniform 类中添加这个方法
        m_passResourceState.bindUniform(name, uniform);
    }

    void Layout::bindTexture(std::string name, FCT::Image* image)
    {
        m_passResourceState.bindTexture(name, image);
    }

    void Layout::bindSampler(std::string name, FCT::Sampler* sampler)
    {
        m_passResourceState.bindSampler(name, sampler);
    }

    void Layout::bindVertexShader(FCT::VertexShader* shader)
    {
        m_pipelineState.vertexShader = shader;
    }

    void Layout::bindPixelShader(FCT::PixelShader* shader)
    {
        m_pipelineState.pixelShader = shader;
    }

    /*
    void Layout::drawMesh(FCT::RHI::CommandBuffer* cmdBuffer, FCT::StaticMesh<uint32_t>* mesh)
    {
        auto resource = getCurrentPassResource();
        auto pipeline = getCurrentPipeline();

        pipeline->bind(cmdBuffer);
        resource->bind(cmdBuffer,pipeline);
        mesh->bind(cmdBuffer);
        mesh->draw(cmdBuffer);
    }*/

    void Layout::end()
    {

    }

    size_t Layout::TraditionPipelineState::hash() const
    {
        size_t hash = 0;
        boost::hash_combine(hash, vertexShader);
        boost::hash_combine(hash, pixelShader);
        boost::hash_combine(hash, blendState);
        boost::hash_combine(hash, rasterizationState);
        boost::hash_combine(hash, depthStencilState);
        return hash;
    }

    bool Layout::TraditionPipelineState::operator==(const TraditionPipelineState& other) const
    {
        return vertexShader == other.vertexShader &&
            pixelShader == other.pixelShader &&
            blendState == other.blendState &&
            rasterizationState == other.rasterizationState &&
            depthStencilState == other.depthStencilState;
    }

    void Layout::PassResourceState::clear()
    {
        boundTextures.clear();
        boundSamplers.clear();
        boundUniforms.clear();
    }

    void Layout::PassResourceState::bindTexture(const std::string& name, FCT::Image* image)
    {
        boundTextures[name] = image;
    }

    void Layout::PassResourceState::bindSampler(const std::string& name, FCT::Sampler* sampler)
    {
        boundSamplers[name] = sampler;
    }

    void Layout::PassResourceState::bindUniform(const std::string& name, const Uniform& uniform)
    {
        boundUniforms[name] = uniform;
    }

    size_t Layout::PassResourceState::hash() const
    {
        size_t hash = 0;

        for (const auto& tex : boundTextures) {
            boost::hash_combine(hash, tex.first);
            boost::hash_combine(hash, tex.second);
        }

        for (const auto& samp : boundSamplers) {
            boost::hash_combine(hash, samp.first);
            boost::hash_combine(hash, samp.second);
        }

        for (const auto& uni : boundUniforms) {
            boost::hash_combine(hash, uni.first);
            boost::hash_combine(hash, uni.second);
        }

        return hash;
    }

    FCT::PassResource* Layout::PassResourceCache::get(const PassResourceState& state,
        const std::function<FCT::PassResource*(const PassResourceState& state)>& creator)
    {
        auto hash = state.hash();
        if (m_passResources.count(hash))
        {
            return m_passResources[hash];
        } else
        {
            auto passResource = creator(state);
            m_passResources[hash] = passResource;
            return passResource;
        }
    }

    FCT::RHI::RasterizationPipeline* Layout::PipelineCache::get(const TraditionPipelineState& state,
        const std::function<FCT::RHI::RasterizationPipeline*(const TraditionPipelineState& state)>& creator)
    {
        auto hash = state.hash();
        if (m_pipelines.count(hash))
        {
            return m_pipelines[hash];
        } else
        {
            auto pipeline = creator(state);
            m_pipelines[hash] = pipeline;
            return pipeline;
        }
    }

    void Layout::processUnhandledTextureSlots()
    {
        auto it = m_unhandledTextureSlots.begin();
        while (it != m_unhandledTextureSlots.end())
        {
            FCT::ShaderStages usage;

            if (!m_hasVertexLayout && !m_hasPixelLayout)
            {
                ++it;
                continue;
            }
            else if (m_hasVertexLayout && !m_hasPixelLayout)
            {
                usage = FCT::ShaderStage::Vertex | FCT::ShaderStage::Fragment;
            }
            else if (!m_hasVertexLayout && m_hasPixelLayout)
            {
                usage = FCT::ShaderStage::Vertex | FCT::ShaderStage::Fragment;
            }
            else
            {
                usage = FCT::ShaderStage::Fragment;
            }
            m_textureNames[it->name] = nullptr;
            m_textureNames[it->name] =  m_textureNames.find(it->name)->first.c_str();
            FCT::TextureElement element(FCT::TextureType::Texture2D, m_textureNames[it->name], usage, FCT::UpdateFrequency::PerFrame);
            addTextureSlot(element);

            it = m_unhandledTextureSlots.erase(it);
        }
    }

    uint32_t Layout::findNextAvailableIndex()
    {
        while (m_vertexLayouts.find(m_nextAvailableIndex) != m_vertexLayouts.end()) {
            ++m_nextAvailableIndex;
        }
        return m_nextAvailableIndex++;
    }

    FCT::PassResource* Layout::getCurrentPassResource()
    {
        return m_passResourceCache.get(m_passResourceState, [this](const PassResourceState& state)
        {
            auto ret = m_ctx->createResource<FCT::PassResource>();
            for (const auto& tex : state.boundTextures) {
                ret->addTexture( tex.second,m_resourceLayout.findTexture(tex.first.c_str()));
            }
            for (const auto& samp : state.boundSamplers) {
                ret->addSampler(samp.second,m_resourceLayout.findSampler(samp.first.c_str()));
            }
            for (const auto& uni : state.boundUniforms) {
                ret->addConstBuffer(uni.second);
            }
            ret->create();
            return ret;
        });
    }

    FCT::RHI::RasterizationPipeline* Layout::getCurrentPipeline()
    {
        return m_pipelineCache.get(m_pipelineState, [this](const TraditionPipelineState& state)
        {
            auto ret = m_ctx->createTraditionPipeline();

            for (auto& layout : m_vertexLayouts)
            {
                ret->vertexLayout(layout.second);
            }

            ret->pixelLayout(m_pixelLayout);

            if (state.vertexShader) {
                ret->addResources(state.vertexShader);
            }
            if (state.pixelShader) {
                ret->addResources(state.pixelShader);
            }

            if (state.blendState) {
                ret->addResources(state.blendState);
            }
            if (state.rasterizationState) {
                ret->addResources(state.rasterizationState);
            }
            if (state.depthStencilState) {
                ret->addResources(state.depthStencilState);
            }

            if (m_pass) {
                ret->bindPass(m_pass);
            }

            ret->create();
            return ret;
        });
    }
}
