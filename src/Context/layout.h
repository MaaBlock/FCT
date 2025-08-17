//
// Created by Administrator on 2025/8/17.
//

#ifndef LAYOUT_H
#define LAYOUT_H
#include "ShaderStage.h"
#include "Context.h"
#include "UniformWrapper.h"
namespace FCT {
    class DepthStencilState;
    struct TextureSlot
    {
        std::string name;
    };
    struct PassName
    {
        std::string name;
    };
    using UniformSlot = FCT::ConstLayout;
    using UniformVar = FCT::ConstElement;
    using UniformType = FCT::ConstType;
    using SamplerSlot = FCT::SamplerElement;
    class Layout {
    public:
        template<typename... Args>
        void proccessArgs(FCT::VertexLayout vertexLayout, Args... args)
        {
            uint32_t index = findNextAvailableIndex();
            m_vertexLayouts[index] = vertexLayout;
            m_hasVertexLayout = true;
            processUnhandledTextureSlots();
            proccessArgs(args...);
        }
        template<typename... Args>
        void proccessArgs(SamplerSlot samplerSlot, Args... args)
        {
            m_resourceLayout.addSampler(samplerSlot);

            if (samplerSlot.getShaderStages() & FCT::ShaderStage::Vertex)
            {
                m_vertexResourceLayout.addSampler(samplerSlot);
            }
            if (samplerSlot.getShaderStages() & FCT::ShaderStage::Fragment)
            {
                m_pixelResourceLayout.addSampler(samplerSlot);
            }
            m_resourceLayout.addSampler(samplerSlot);

            proccessArgs(args...);
        }
        template<typename... Args>
        void proccessArgs(PassName passName, Args... args)
        {
            if (m_ctx && m_ctx->getModule<FCT::RenderGraph>()) {
                attachPass(m_ctx->getModule<FCT::RenderGraph>(), passName.name);
            }
            proccessArgs(args...);
        }

        template<typename... Args>
        void proccessArgs(uint32_t index, FCT::VertexLayout vertexLayout, Args... args)
        {
            m_vertexLayouts[index] = vertexLayout;
            m_hasVertexLayout = true;
            processUnhandledTextureSlots();
            proccessArgs(args...);
        }


        template<typename... Args>
        void proccessArgs(FCT::PixelLayout pixelLayout, Args... args)
        {
            m_pixelLayout = pixelLayout;
            m_hasPixelLayout = true;
            processUnhandledTextureSlots();
            proccessArgs(args...);
        }

        template<typename... Args>
        void proccessArgs(TextureSlot textureSlot, Args... args)
        {
            m_unhandledTextureSlots.push_back(textureSlot);
            processUnhandledTextureSlots();
            proccessArgs(args...);
        }
        template<typename... Args>
        void proccessArgs(UniformSlot uniformSlot, Args... args)
        {
            m_uniformLayouts[uniformSlot.getName()] = uniformSlot;
            proccessArgs(args...);
        }

        void proccessArgs()
        {
            if (!m_hasPixelLayout && m_hasVertexLayout)
            {
                m_pixelLayout = m_vertexLayouts.begin()->second;
            }
        }

        template<typename... Args>
        Layout(FCT::Context* ctx,Args... args) : m_ctx(ctx)
        {
            proccessArgs(args...);
        }
        void ctx(FCT::Context* ctx);
        void setFixedImage(std::string name, FCT::Image* image);
        void addTextureSlot(FCT::TextureElement element);
        void attachPass(FCT::RenderGraph* graph,std::string passName);
        Uniform allocateUniform(std::string name);
        FCT::VertexShader* allocateVertexShader(std::string code);
        FCT::PixelShader* allocatePixelShader(std::string code);
        void begin();
        //passresource
        void bindUniform(const Uniform& uniform);
        void bindTexture(std::string name, FCT::Image* image);
        void bindSampler(std::string name, FCT::Sampler* sampler);
        //pipeline
        void bindVertexShader(FCT::VertexShader* shader);
        void bindPixelShader(FCT::PixelShader* shader);
        //void drawMesh(FCT::RHI::CommandBuffer* cmdBuffer,FCT::StaticMesh<uint32_t>* mesh);
        template<typename T>
        void drawMesh(RHI::CommandBuffer* cmdBuffer,T* mesh);
        template<typename T>
        void drawMesh(RHI::CommandBuffer* cmdBuffer,T& mesh);
        void end();
    private:
        struct TraditionPipelineState
        {
            FCT::VertexShader* vertexShader = nullptr;
            FCT::PixelShader* pixelShader = nullptr;
            FCT::BlendState* blendState = nullptr;
            FCT::RasterizationState* rasterizationState = nullptr;
            FCT::DepthStencilState* depthStencilState = nullptr;
            size_t hash() const;
            bool operator==(const TraditionPipelineState& other) const;
        };
        struct PassResourceState
        {
            std::unordered_map<std::string, FCT::Image*> boundTextures;
            std::unordered_map<std::string, FCT::Sampler*> boundSamplers;
            std::unordered_map<std::string, FCT::RHI::ConstBuffer*> boundUniforms;
            void clear();
            void bindTexture(const std::string& name, FCT::Image* image);
            void bindSampler(const std::string& name, FCT::Sampler* sampler);
            void bindUniform(const std::string& name, const Uniform& uniform);
            size_t hash() const;
        };
        struct PassResourceCache
        {
            std::unordered_map<size_t,FCT::PassResource*> m_passResources;
            FCT::PassResource* get(const PassResourceState& state, const std::function<FCT::PassResource*(const PassResourceState& state)>& creator);
        };
        struct PipelineCache
        {
            std::unordered_map<size_t, FCT::RHI::RasterizationPipeline*> m_pipelines;
            FCT::RHI::RasterizationPipeline* get(const TraditionPipelineState& state, const std::function<FCT::RHI::RasterizationPipeline*(const TraditionPipelineState& state)>& creator);
        };
        void processUnhandledTextureSlots();
        uint32_t findNextAvailableIndex();
        FCT::Context* m_ctx;
        std::map<uint32_t, FCT::VertexLayout> m_vertexLayouts;
        std::map<std::string, FCT::ConstLayout> m_uniformLayouts;
        FCT::PixelLayout m_pixelLayout;
        FCT::ResourceLayout m_resourceLayout;
        FCT::ResourceLayout m_vertexResourceLayout;
        FCT::ResourceLayout m_pixelResourceLayout;
        std::unordered_map<std::string, FCT::Image*> m_fixedImages;
        uint32_t m_nextAvailableIndex = 0;
        std::vector<TextureSlot> m_unhandledTextureSlots;
        bool m_hasVertexLayout = false;
        bool m_hasPixelLayout = false;
        FCT::PassResource* getCurrentPassResource();
        PassResourceState m_passResourceState;
        PassResourceCache m_passResourceCache;
        FCT::RHI::Pass* m_pass;
        TraditionPipelineState m_pipelineState;
        PipelineCache m_pipelineCache;
        FCT::RHI::RasterizationPipeline* getCurrentPipeline();
        std::unordered_map<std::string,const char*> m_textureNames;
    };

}
#endif //LAYOUT_H
