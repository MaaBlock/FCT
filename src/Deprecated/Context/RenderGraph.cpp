//
// Created by Administrator on 2025/8/5.
//

#include "RenderGraph.h"
#include "Context.h"
#include "../RHI/Pass.h"
#include "../RHI/PassGroup.h"
namespace FCT {

    void RenderGraph::collectImages()
    {
        for (auto& [name, pass] : m_originPasses)
        {
            for (size_t i = 0; i < pass.m_textureCount; ++i)
            {
                auto& texture = pass.textures[i];
                if (texture.format != Format::UNDEFINED)
                {
                    m_originImages[texture.name].format = texture.format;
                }
                if (texture.size)
                {
                    m_originImages[texture.name].size = texture.size;
                }
                if (texture.samples!= Samples::sample_undefined)
                {
                    m_originImages[texture.name].samples = texture.samples;
                }
                m_originImages[texture.name].usages |= ImageUsage::Texture;
                m_originImages[texture.name].consumerPasses.insert(name);
            }
            for (size_t i = 0; i < pass.m_targetsCount; ++i)
            {
                auto& target = pass.targets[i];
                if (target.wnd)
                {
                    m_originImages[target.name].wnd = target.wnd;
                    m_originImages[target.name].usages |= ImageUsage::RenderTarget;
                    continue;
                }
                if (target.size)
                {
                    m_originImages[target.name].size = target.size;
                    m_hasSizeBuffers.emplace(target.name);
                }
                if (target.format!= Format::UNDEFINED)
                {
                    m_originImages[target.name].format = target.format;
                }
                if (target.samples!= Samples::sample_undefined)
                {
                    m_originImages[target.name].samples = target.samples;
                }
                m_originImages[target.name].usages |= ImageUsage::RenderTarget;
                m_originImages[target.name].producerPasses.insert(name);
            }
            if (pass.depthStencil.name.data())
            {
                auto& depthStencil = pass.depthStencil;
                if (depthStencil.wnd)
                {
                    m_originImages[depthStencil.name].wnd = depthStencil.wnd;
                    m_originImages[depthStencil.name].usages |= ImageUsage::DepthStencil;
                    continue;
                }
                if (depthStencil.format!= Format::UNDEFINED)
                {
                    m_originImages[depthStencil.name].format = depthStencil.format;
                }
                if (depthStencil.size)
                {
                    m_originImages[depthStencil.name].size = depthStencil.size;
                    m_hasSizeBuffers.emplace(depthStencil.name);
                }
                if (depthStencil.samples != Samples::sample_undefined)
                {
                    m_originImages[depthStencil.name].samples = depthStencil.samples;
                }
                m_originImages[depthStencil.name].usages |= ImageUsage::DepthStencil;
                m_originImages[depthStencil.name].producerPasses.insert(name);
            }
        }
    }

    void RenderGraph::unionHasSizeBuffers()
    {
        std::unordered_map<Size2, std::vector<std::string>> sizeGroups;

        for (auto& name : m_hasSizeBuffers)
        {
            auto& buffer = m_originImages[name];
            if (buffer.size)
            {
                sizeGroups[buffer.size].push_back(name);
            }
        }
        for (auto& [size, names] : sizeGroups)
        {
            if (names.size() > 1)
            {
                for (size_t i = 1; i < names.size(); ++i)
                {
                    m_bufferUnions.unite(names[0], names[i]);
                }
                BufferUnionShared shared;
                shared.size = size;
                m_bufferUnions.shared(names[0],shared);
            }
            else if (names.size() == 1)
            {
                BufferUnionShared shared;
                shared.size = size;
                m_bufferUnions.unite(names[0],names[0]);
                m_bufferUnions.shared(names[0],shared);
            }
        }
    }

    void RenderGraph::computeBufferSize()
    {
        /**
             *@cond CHINESE
             *@note  将同一pass的所有target和depth stencil 加入进一个集合
             *@endcond
             */
        for (auto& [passName, passDesc] : m_originPasses)
        {
            Window* wnd = nullptr;
            std::vector<std::string> passBuffers;

            for (size_t i = 0; i < passDesc.m_targetsCount; ++i)
            {
                const auto& target = passDesc.targets[i];
                if (target.wnd)
                    wnd = target.wnd;
                if (!target.name.empty())
                {
                    passBuffers.push_back(target.name);
                }
            }

            if (!passDesc.depthStencil.name.empty())
            {
                if (passDesc.depthStencil.wnd)
                    wnd = passDesc.depthStencil.wnd;
                passBuffers.push_back(passDesc.depthStencil.name);
            }

            if (passBuffers.size() > 1)
            {
                for (size_t i = 1; i < passBuffers.size(); ++i)
                {
                    m_bufferUnions.unite(passBuffers[0], passBuffers[i]);
                }
            }
            else if (passBuffers.size() == 1)
            {
                m_bufferUnions.unite(passBuffers[0], passBuffers[0]);
            }
            if (wnd && passBuffers.size())
            {
                BufferUnionShared shared;
                shared.size = Size2();
                shared.wnd = wnd;
            }
        }

        m_computedImages = m_originImages;
        for (auto& [imageName, bufferDesc] : m_computedImages)
        {
            auto computedSize = m_bufferUnions.shared(imageName);

            if (computedSize.has_value() && computedSize.value().size)
            {
                bufferDesc.size = computedSize.value().size;
            }
        }
    }


    void RenderGraph::allocateRootImages(std::string name)
    {
        auto resourceManager = m_ctx->getModule<ResourceManager>();
        auto bufferName = m_imageToBufferMap[name];
        auto desc = m_bufferNameToBufferDesc[bufferName];
        if (desc.allocated)
            return;

        desc.image = resourceManager->allocateTarget(bufferName,{
            desc.size.width,
            desc.size.height,
            desc.samples,
            desc.format,
            desc.usages
        });
    }

    void RenderGraph::allocateImages(std::string name, std::string root)
    {
        auto resourceManager = m_ctx->getModule<ResourceManager>();
        auto desc = m_bufferNameToBufferDesc[name];
        auto bufferName = m_imageToBufferMap[name];
        auto rootName = m_imageToBufferMap[root];
        if (desc.allocated)
            return;
        desc.image = resourceManager->allocateImage(
            bufferName,
            rootName,
         {
             desc.format,
             desc.samples,
             desc.usages
         });
    }

    void RenderGraph::allocateImages(std::string name, Window* wnd)
    {
        auto resourceManager = m_ctx->getModule<ResourceManager>();
        auto desc = m_bufferNameToBufferDesc[name];
        auto bufferName = m_imageToBufferMap[name];
        if (desc.allocated)
            return;
        desc.image = resourceManager->allocateImage(
            bufferName,
            wnd,
         {
             desc.format,
             desc.samples,
             desc.usages
         });
    }

    void RenderGraph::createBuffers()
    {

        for (const auto& [imageName, bufferDesc] : m_computedImages)
        {
            m_imageToBufferMap[imageName] = imageName;
            m_bufferNameToBufferDesc[imageName] = RenderGraphBufferDesc(bufferDesc);
        }

        std::set<std::string> internalImages;
        std::unordered_map<std::string, std::string> imageToGroup; // image -> group mapping

        for (auto& [groupRoot, group] : m_compiledGroups)
        {
            for (const auto& internalImage : group.internals)
            {
                internalImages.insert(internalImage);
                imageToGroup[internalImage] = groupRoot;
            }
        }
        std::unordered_map<NeedCreatedBufferDesc, std::vector<std::string>> shareableImages;

        for (const auto& imageName : internalImages)
        {
            const auto& bufferDesc = m_computedImages[imageName];
            std::string bufferRoot = m_bufferUnions.find(imageName);

            NeedCreatedBufferDesc desc;
            desc.root = bufferRoot;
            desc.samples = bufferDesc.samples;
            desc.format = bufferDesc.format;
            desc.imageName = imageName;

            shareableImages[desc].push_back(imageName);
        }

        for (auto& [desc, images] : shareableImages)
        {
            std::set<std::string> involvedGroups;
            for (const auto& imageName : images)
            {
                involvedGroups.insert(imageToGroup[imageName]);
            }

            if (involvedGroups.size() > 1)
            {
                std::string sharedBufferName = "s_" + desc.root + "_" +
                    std::to_string(static_cast<uint32_t>(desc.samples)) + "_" +
                    std::to_string(static_cast<uint32_t>(desc.format));

                for (const auto& imageName : images)
                {
                    m_imageToBufferMap[imageName] = sharedBufferName;
                    m_bufferNameToBufferDesc.erase(imageName);
                    m_bufferNameToBufferDesc[sharedBufferName] |= m_computedImages[imageName];
                }
            }
            else
            {
                for (const auto& imageName : images)
                {
                    m_imageToBufferMap[imageName] = imageName;
                }
            }
        }
        auto resourceManager = m_ctx->getModule<ResourceManager>();
        auto group = m_bufferUnions.getGroups();
        for (const auto& [groupRoot, group] : group)
        {
            auto shared = m_bufferUnions.shared(groupRoot);
            if (shared.has_value())
            {
                if (shared->wnd)
                {
                    for (auto image : group)
                    {
                        if (!m_originImages[image].wnd)
                        {
                            allocateImages(image, shared->wnd);
                        }
                    }
                } else
                {
                    allocateRootImages(groupRoot);
                    for (auto image : group)
                    {
                        if (image != groupRoot)
                        {
                            allocateImages(image,groupRoot);
                        }
                    }
                }
            } else
            {
                //error
            }
        }
    }

    void RenderGraph::createPasses()
    {
        for (auto& [passName, passDesc] : m_compiledPasses)
        {
            passDesc.pass = m_ctx->createResource<RHI::Pass>();
            auto pass = passDesc.pass;
            auto desc = m_originPasses[passName];
            if (desc.m_clear.types)
            {
                passDesc.pass->enableClear(desc.m_clear.types,desc.m_clear.color,desc.m_clear.depth,desc.m_clear.stencil);
            }
            for (size_t i = 0; i < desc.m_targetsCount; ++i)
            {
                pass->bindTarget(i,getImage(desc.targets[i].name));
            }
            if (!desc.depthStencil.name.empty())
            {
                pass->depthStencil(getImage(desc.depthStencil.name));
            }
        }
    }

    void RenderGraph::createPassGroups()
    {
        auto groupOrder = m_groupGraph.order();
        std::string thePresentGroup = std::string();
        for (const auto& groupIndex : groupOrder)
        {
            auto& group = m_compiledGroups[groupIndex.name];
        }
        for (auto& [groupName, group] : m_compiledGroups)
        {
            std::vector<ImageBarrierDesc> barrierDescs;
            auto groupPass = m_ctx->createResource<RHI::PassGroup>();
            /**
             *@cond CHINESE
             *@note  解析 规则，
             *       texture  如果存在本group里的pass作为 target，则添加对哪个pass的依赖
             *       如果 不存在，则添加外部 依赖
             *@endcond
             */
            for (const auto& passName : group.passes)
            {
                std::vector<RHI::PassNeighbors> predecessors;
                RHI::Pass* pass = m_compiledPasses[passName].pass;
                auto srcPassDesc = m_originPasses[passName];
                for (size_t i = 0; i < srcPassDesc.m_textureCount; ++i) {
                    const auto& texture = srcPassDesc.textures[i];
                    const auto image = m_originImages[texture.name];
                     for (auto producer : image.producerPasses)
                     {
                         if (find(group.passes.begin(), group.passes.end(), producer)!= group.passes.end())
                         {

                         } else
                         {

                         }
                     }
                }

            }
        }
    }

    RenderGraph::RenderGraph(Context* ctx)
    {
        m_ctx = ctx;
        m_device = m_ctx->getModule<Device>();
    }

    RenderGraph::~RenderGraph()
    {

    }

    Image* RenderGraph::getImage(std::string name)
    {
        return m_bufferNameToBufferDesc[m_imageToBufferMap[name]].image;
    }
} // FCT