//
// Created by Administrator on 2025/8/5.
//

#ifndef RENDERGRAPH_H
#define RENDERGRAPH_H

#include "../RHI/ImageAspect.h"
#include "../RHI/ImageLayout.h"
#include "../RHI/PipelineStage.h"
#include "../RHI/AccessFlags.h"

#include "../ThirdParty.h"
#include "./Format.h"
#include "../Base/TokenGraph.h"
#include "../Base/UnionFind.h"
#include "../RHI/ImageUsageFlags.h"
#include "./ShaderStage.h"
#include "./ClearTypes.h"
#include "Vec.h"

namespace FCT
{
    enum class RenderGraphNodeType : uint32_t
    {
        pass,
        image
    };
    enum class PassGroupRenderGraphNodeType : uint32_t
    {
        group,
        image
    };


    struct Size2
    {
        int32_t width;
        int32_t height;
        constexpr Size2() noexcept : width(0), height(0) {}
        constexpr Size2(int32_t width, int32_t height) : width(width), height(height) {}
        constexpr operator bool() const noexcept {
            return width > 0 && height > 0;
        }
        constexpr bool operator==(const Size2& other) const noexcept {
            return width == other.width && height == other.height;
        }
    };
    struct RenderGraphNode
    {
        std::string name;
        RenderGraphNodeType type;
        constexpr bool operator==(const RenderGraphNode& other) const noexcept {
            return name == other.name && type == other.type;
        }
    };

    struct PassGroupRenderGraphNode
    {
        std::string name;
        PassGroupRenderGraphNodeType type;
        constexpr bool operator==(const PassGroupRenderGraphNode& other) const noexcept {
            return name == other.name && type == other.type;
        }
    };

    struct NeedCreatedBufferDesc
    {
        std::string root;
        std::set<std::string> useInGroup;
        Samples samples;
        Format format;
        std::string imageName;
    };
}
namespace std
{
    template<>
    struct hash<FCT::Size2>
    {
        std::size_t operator()(const FCT::Size2& s) const noexcept
        {
            std::size_t seed = 0;
            boost::hash_combine(seed, s.width);
            boost::hash_combine(seed, s.height);
            return seed;
        }
    };
    template<>
    struct hash<FCT::RenderGraphNode>
    {
        std::size_t operator()(const FCT::RenderGraphNode& n) const noexcept
        {
            std::size_t seed = 0;
            boost::hash_combine(seed, n.name);
            boost::hash_combine(seed, n.type);
            return seed;
        }
    };
    template<>
    struct hash<FCT::PassGroupRenderGraphNode>
    {
        std::size_t operator()(const FCT::PassGroupRenderGraphNode& n) const noexcept
        {
            std::size_t seed = 0;
            boost::hash_combine(seed, n.name);
            boost::hash_combine(seed, n.type);
            return seed;
        }
    };

    template<>
struct hash<FCT::NeedCreatedBufferDesc>
    {
        std::size_t operator()(const FCT::NeedCreatedBufferDesc& desc) const noexcept
        {
            std::size_t seed = 0;
            boost::hash_combine(seed, desc.root);
            boost::hash_combine(seed, desc.samples);
            boost::hash_combine(seed, desc.format);
            return seed;
        }
    };
}
namespace FCT {
    namespace RHI
    {
        class Pass;
    }
    class Context;
    class Device;
    struct Texture
    {
        std::string name;
        Size2 size;
        Format format;
        Samples samples;
        ShaderStages stages;
        Texture() noexcept {}
        template<typename... Args>
        Texture(std::string_view name,Args&&... args) noexcept
            : name(name),format(Format::UNDEFINED),samples(Samples::sample_undefined), size(),stages(ShaderStage::Fragment) {
            processArgs(std::forward<Args>(args)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Size2& other, Rest&&... rest) noexcept {
            size = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Samples& other, Rest&&... rest) noexcept {
            samples = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Format& other, Rest&&... rest) noexcept {
            format = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const ShaderStages& other, Rest&&... rest) noexcept
        {
            stages = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        constexpr void processArgs() noexcept {}
    };
    class Window;
    struct Target
    {
        std::string name;
        Window* wnd;
        Size2 size;
        Format format;
        Samples samples;
        Target() noexcept{}
        Target(Window* wnd) noexcept : wnd(wnd)
        {
            name = "Target_" + std::to_string(reinterpret_cast<uintptr_t>(wnd));
        }
        template<typename... Args>
        Target(std::string_view name, Args&&... args) noexcept
        {
            this->name = name;
            processArgs(std::forward<Args>(args)...);
        }
        template<typename... Rest>
        void processArgs(const Size2& other, Rest&&... rest) noexcept
        {
            size = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        void processArgs(const Samples& other, Rest&&... rest) noexcept
        {
            samples = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        void processArgs(const Format& other, Rest&&... rest) noexcept
        {
            format = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        void processArgs() noexcept {}
    };
    struct DepthStencil
    {
        std::string name;
        Size2 size;
        Format format;
        Samples samples;
        Window* wnd;
        constexpr DepthStencil() noexcept : name()
        {

        }
        DepthStencil(Window* wnd) noexcept : wnd(wnd)
        {
            name = "DepthStencil_" + std::to_string(reinterpret_cast<uintptr_t>(wnd));
        }
        template<typename... Args>
        DepthStencil(std::string_view name, Args&&... args) noexcept
        {
            this->name = name;
            processArgs(std::forward<Args>(args)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Size2& other, Rest&&... rest) noexcept
        {
            size = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Samples& other, Rest&&... rest) noexcept
        {
            samples = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Format& other, Rest&&... rest) noexcept
        {
            format = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        constexpr void processArgs() noexcept {}
    };
    namespace RenderGraphConstVar
    {
        constexpr uint32_t MAX_TEXTURE_COUNT = 96;
        constexpr uint32_t MAX_TARGET_COUNT = 8;
    }
     struct PassClear
    {
        ClearTypes types;
        Vec4 color;
        float depth;
        uint8_t stencil;
        PassClear() noexcept : types(0), color(0.0f, 0.0f, 0.0f, 1.0f), depth(1.0f), stencil(0) {}
        template<typename... Args>
        constexpr PassClear(Args&&... args) noexcept
        {
            processArgs(std::forward<Args>(args)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const ClearTypes& other, Rest&&... rest)
        {
            types = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Vec4& other, Rest&&... rest)
        {
            color = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const float& other, Rest&&... rest)
        {
            depth = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const uint8_t& other, Rest&&... rest)
        {
            stencil = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        constexpr void processArgs() noexcept {}
    };
    struct PassDesc
    {
        std::string name;
        Texture textures[RenderGraphConstVar::MAX_TEXTURE_COUNT];
        Target targets[RenderGraphConstVar::MAX_TARGET_COUNT];
        DepthStencil depthStencil;
        size_t m_textureCount;
        size_t m_targetsCount;
        PassClear m_clear = PassClear();
        PassDesc(std::string_view name) : name(name)
        {
            m_textureCount = 0;
            m_targetsCount = 0;
        }
        constexpr void addTexture(const Texture& texture) noexcept
        {
            if (m_textureCount < RenderGraphConstVar::MAX_TEXTURE_COUNT)
            {
                textures[m_textureCount++] = texture;
            }
        }
        constexpr void addTarget(const Target& target) noexcept
        {
            if (m_targetsCount < RenderGraphConstVar::MAX_TARGET_COUNT)
            {
                targets[m_targetsCount++] = target;
            }
        }
        constexpr void setDepthStencil(const DepthStencil& depthStencil) noexcept
        {
            this->depthStencil = depthStencil;
        }

        template<typename... Rest>
        constexpr void processArgs(const Texture& other, Rest&&... rest) noexcept {
            addTexture(other);
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        constexpr void processArgs(const Target& other, Rest&&... rest) noexcept
        {
            addTarget(other);
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const DepthStencil& other, Rest&&... rest) noexcept
        {
            setDepthStencil(other);
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const PassClear& other, Rest&&... rest)
        {
            m_clear = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        constexpr void processArgs() noexcept {}
    };
    struct CompiledPass
    {
        std::string name;
        std::string resourceGroup;
        RHI::Pass* pass;
    };

    struct BufferDesc
    {
        BufferDesc()
        {
            format = Format::R8G8B8A8_UNORM;
            samples = Samples::sample_1;
            wnd = nullptr;
        }
        ImageUsages usages;
        Format format;
        Size2 size;
        Samples samples;
        Window* wnd;
        std::set<std::string> consumerPasses;
        std::set<std::string> producerPasses;
    };
    class Image;
    struct RenderGraphBufferDesc
    {
        ImageUsages usages;
        Format format;
        Size2 size;
        Samples samples;
        bool allocated = false;
        Image* image = nullptr;
        bool filled = false;

        RenderGraphBufferDesc() = default;

        RenderGraphBufferDesc(const BufferDesc& bufferDesc)
            : usages(bufferDesc.usages)
            , format(bufferDesc.format)
            , size(bufferDesc.size)
            , samples(bufferDesc.samples)
            , filled(true)
        {
        }

        RenderGraphBufferDesc& operator|=(const BufferDesc& other)
        {
            if (filled)
            {
                usages |= other.usages;
                return *this;
            }
            *this = RenderGraphBufferDesc(other);
            return *this;
        }
    };

    /**
     * @cond CHINESE
     * @note  没有考虑中间的转换
     * @endcond
     */
    struct ImageBarrierDesc
    {
        std::string image;
        ImageLayout srcLayout;
        ImageLayout dstLayout;
        AccessFlags srcAccessMask;
        AccessFlags dstAccessMask;
        PipelineStage srcStageMask;
        PipelineStage dstStageMask;
        ImageAspect aspect;
    };
    struct CompiledGroup
    {
        std::vector<ImageBarrierDesc> imageBarriers;
        std::set<std::string> inputs;
        std::set<std::string> outputs;
        std::set<std::string> internals;
        std::vector<std::string> passes;
    };
    struct BufferUnionShared
    {
        Size2 size;
        Window* wnd = nullptr;
    };
    /**
     * @cond CHINESE
     * @note  RenderGraph  职责
     *        1.自动创建中间的图像资源
     *        2.转换Pass  为 RHI::Pass RHI::PassGroup，自动添加 屏障
     *        3.提供命令 封装CommandBuffer，并 实现CachePassResource
     * @endcond
     */
    class RenderGraph {
    private:
        Context* m_ctx;
        Device* m_device;
        std::unordered_map<std::string,PassDesc> m_originPasses;
        std::unordered_map<std::string,BufferDesc> m_originImages;
        std::unordered_map<std::string,BufferDesc> m_computedImages;
        UnionFind<std::string,BufferUnionShared> m_bufferUnions;
        std::set<std::string> m_hasSizeBuffers;
        TokenGraph<RenderGraphNode,RenderGraphNode> m_tokenGraph;
        std::unordered_map<std::string, CompiledPass> m_compiledPasses;
        UnionFind<std::string,char> m_passUnions;
        std::unordered_map<std::string,CompiledGroup> m_compiledGroups;
        TokenGraph<PassGroupRenderGraphNode,PassGroupRenderGraphNode> m_groupGraph;
        std::unordered_map<std::string,std::string> m_imageToBufferMap;
        std::unordered_map<std::string,RenderGraphBufferDesc> m_bufferNameToBufferDesc;
        /**
         * @cond CHINESE
         * @note 收集 所有Image,并收集其中有大小的Image
         * @endcond
         */
        void allocateRootImages(std::string name);
        void allocateImages(std::string name,std::string root);
        void allocateImages(std::string name,Window* wnd);
        void collectImages();
        void unionHasSizeBuffers();
        void computeBufferSize();
        void addNodeToTokenGraph(const PassDesc& pass)
        {
            RenderGraphNode passNode{pass.name, RenderGraphNodeType::pass};

            std::vector<RenderGraphNode> predecessors;
            for (size_t i = 0; i < pass.m_textureCount; ++i) {
                predecessors.emplace_back(RenderGraphNode{pass.textures[i].name, RenderGraphNodeType::image});
            }

            std::vector<RenderGraphNode> successors;
            for (size_t i = 0; i < pass.m_targetsCount; ++i) {
                successors.emplace_back(RenderGraphNode{pass.targets[i].name, RenderGraphNodeType::image});
            }

            if (!pass.depthStencil.name.empty()) {
                successors.emplace_back(RenderGraphNode{pass.depthStencil.name, RenderGraphNodeType::image});
            }

            m_tokenGraph[passNode] = {passNode, predecessors, successors};
        }
        bool isWallNode(std::string nodeNmae)
        {

        }
        bool isMutilInputNode(std::string nodeName)
        {
            std::string currentResourceGroup = m_compiledPasses[nodeName].resourceGroup;
            for (auto i = 0;i < m_originPasses[nodeName].m_textureCount;i++)
            {
                if (m_bufferUnions.find(m_originPasses[nodeName].textures[i].name) == currentResourceGroup)
                    return true;
            }
            return false;
        }
        bool isMutilOutputNode(std::string nodeName)
        {
            std::string currentResourceGroup = m_compiledPasses[nodeName].resourceGroup;
            auto outputPasses = m_tokenGraph.getActiveSuccessors({nodeName,RenderGraphNodeType::pass});
            for (auto& outputPass : outputPasses)
            {
                if (m_compiledPasses[outputPass.name].resourceGroup!= currentResourceGroup)
                    return true;
            }
            return false;
        }
        void partitionPassGroups()
        {
            m_tokenGraph.visitDFSFromRoots([this](RenderGraphNode node)
            {
                m_compiledPasses[node.name].name = node.name;
                auto getResourceGroup = [this](PassDesc& pass) -> std::string
                {
                    std::string resourceGroup;
                    if (pass.m_targetsCount > 0)
                    {
                        resourceGroup = m_bufferUnions.find(pass.targets[0].name);
                        return resourceGroup;
                    }
                    if (pass.depthStencil.name.size())
                    {
                        resourceGroup = m_bufferUnions.find(pass.depthStencil.name);
                        return resourceGroup;
                    }
                    return "error?";
                };
                m_compiledPasses[node.name].resourceGroup = getResourceGroup(m_originPasses[node.name]);
            });

            m_tokenGraph.visitDFSFromRoots([this](RenderGraphNode node)
            {
                auto inputPasses = m_tokenGraph.getActivePredecessors(
                    node);
                if (isMutilInputNode(node.name))
                {
                    m_passUnions.unite(node.name,node.name);
                    return;
                }
                for (auto& inputPass : inputPasses)
                {
                    if (isMutilOutputNode(inputPass.name))
                    {
                        m_passUnions.unite(node.name,node.name);
                        return;
                    }
                }
                for (auto& inputPass : inputPasses)
                {
                    m_passUnions.unite(node.name, inputPass.name);
                }
                //if (inputPasses.empty())
                //{
                m_passUnions.unite(node.name,node.name);
                //    return;
                //}
            });
            for (auto& [name,buffer] : m_computedImages)
            {
                if (buffer.producerPasses.size() > 1)
                {
                    for (auto& producerPass : buffer.producerPasses)
                    {
                        if (!buffer.producerPasses.empty()) {
                            auto firstProducer = *buffer.producerPasses.begin();
                            m_passUnions.unite(firstProducer, producerPass);
                        }
                    }
                }
            }
        }
                void buildPassGroupGraph()
        {
            auto unions = m_passUnions.getGroups();
            for (auto& [groupRoot, passes] : unions)
            {
                CompiledGroup compiledGroup;
                compiledGroup.passes = passes;
                /**
                 *@cond CHINESE
                 *@note 收集输入输出buffer，遍历每种然后看一眼是不是又 被生产 了，又被消费 了，那就是中间资源
                 *@endcond
                 */
                std::set<std::string> groupInputBuffers;
                std::set<std::string> groupOutputBuffers;
                std::set<std::string> internalBuffers;

                for (const auto& passName : passes)
                {
                    const auto& pass = m_originPasses[passName];

                    for (size_t i = 0; i < pass.m_textureCount; ++i)
                    {
                        const std::string& bufferName = pass.textures[i].name;

                        bool isInternal = false;
                        for (const auto& otherPassName : passes)
                        {
                            if (otherPassName == passName) continue;
                            const auto& otherPass = m_originPasses[otherPassName];

                            for (size_t j = 0; j < otherPass.m_targetsCount; ++j)
                            {
                                if (otherPass.targets[j].name == bufferName)
                                {
                                    isInternal = true;
                                    break;
                                }
                            }

                            if (!isInternal && otherPass.depthStencil.name == bufferName)
                            {
                                isInternal = true;
                            }

                            if (isInternal) break;
                        }

                        if (isInternal)
                        {
                            internalBuffers.insert(bufferName);
                        }
                        else
                        {
                            groupInputBuffers.insert(bufferName);
                        }
                    }

                    for (size_t i = 0; i < pass.m_targetsCount; ++i)
                    {
                        const std::string& bufferName = pass.targets[i].name;

                        bool isInternal = false;
                        for (const auto& otherPassName : passes)
                        {
                            if (otherPassName == passName) continue;
                            const auto& otherPass = m_originPasses[otherPassName];

                            for (size_t j = 0; j < otherPass.m_textureCount; ++j)
                            {
                                if (otherPass.textures[j].name == bufferName)
                                {
                                    isInternal = true;
                                    break;
                                }
                            }

                            if (isInternal) break;
                        }

                        if (isInternal)
                        {
                            internalBuffers.insert(bufferName);
                        }
                        else
                        {
                            groupOutputBuffers.insert(bufferName);
                        }
                    }

                    if (!pass.depthStencil.name.empty())
                    {
                        const std::string& bufferName = pass.depthStencil.name;

                        bool isInternal = false;
                        for (const auto& otherPassName : passes)
                        {
                            if (otherPassName == passName) continue;
                            const auto& otherPass = m_originPasses[otherPassName];

                            for (size_t j = 0; j < otherPass.m_textureCount; ++j)
                            {
                                if (otherPass.textures[j].name == bufferName)
                                {
                                    isInternal = true;
                                    break;
                                }
                            }

                            if (isInternal) break;
                        }

                        if (isInternal)
                        {
                            internalBuffers.insert(bufferName);
                        }
                        else
                        {
                            groupOutputBuffers.insert(bufferName);
                        }
                    }
                }

                compiledGroup.inputs = groupInputBuffers;
                compiledGroup.internals = internalBuffers;
                compiledGroup.outputs = groupOutputBuffers;

                m_compiledGroups[groupRoot] = compiledGroup;
                PassGroupRenderGraphNode groupNode{groupRoot, PassGroupRenderGraphNodeType::group};

                std::vector<PassGroupRenderGraphNode> predecessors;
                for (const auto& inputBuffer : compiledGroup.inputs) {
                    predecessors.emplace_back(PassGroupRenderGraphNode{inputBuffer, PassGroupRenderGraphNodeType::image});
                }

                std::vector<PassGroupRenderGraphNode> successors;
                for (const auto& outputBuffer : compiledGroup.outputs) {
                    successors.emplace_back(PassGroupRenderGraphNode{outputBuffer, PassGroupRenderGraphNodeType::image});
                }

                m_groupGraph[groupNode] = { groupNode, predecessors, successors};
            }
            m_groupGraph.update();
        }
        void createBuffers();
        void createPasses();
        void createPassGroups();

    public:
        RenderGraph(Context* ctx);
        ~RenderGraph();
        template<typename... Args>
        void addPass(std::string_view name,Args&&... args) {
            PassDesc pass(name);
            pass.processArgs(std::forward<Args>(args)...);
            m_originPasses[std::string(name)] = pass;
            addNodeToTokenGraph(pass);
        }
        void complie()
        {
            m_tokenGraph.update();
            collectImages();
            unionHasSizeBuffers();
            computeBufferSize();
            partitionPassGroups();
            buildPassGroupGraph();
            createBuffers();
            createPasses();
            createPassGroups();
        }
        Image* getImage(std::string name);
    };

} // FCT

#endif //RENDERGRAPH_H
