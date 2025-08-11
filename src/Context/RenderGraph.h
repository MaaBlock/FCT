//
// Created by Administrator on 2025/8/10.
//

#ifndef RENDERGRAPH_H
#define RENDERGRAPH_H

#include "./ResourceManager.h"
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
#include "../Base/Graph.h"
#include "./SizeNode.h"
#include "../Base/UnionFind.h"
#include "../Base/IEventSystem.h"

namespace FCT
{
    class TextureEdge;
    class Context;
    class Window;
    namespace RHI
    {
        class CommandBuffer;
    }
}
#include "./RenderGraph_EnablePassClear.h"
#include "./RenderGraph_TextureSize.h"
#include "./RenderGraph_Texture.h"
#include "./RenderGraph_Target.h"
#include "./RenderGraph_DepthStencil.h"
#include "./RenderGraph_PassDesc.h"
namespace FCT
{
    /**
     * 大小约定：
     *  同一个Pass的Target和DepthStencil的大小 相同
     *  Texture如果Undefined Size，在未指定大小的情况下 等同于FullSize
     *  Target如果 Undefined Size就会自动根据同一个Pass的Target和DepthStencil的大小来推导大小
     */
    class RenderGraphNode
    {
    protected:
        std::string m_name;
    public:
        RenderGraphNode() = default;
        RenderGraphNode(const std::string& name) : m_name(name) {}
    };

    class Edge
    {
    public:

    };

    class TargetEdge : public Edge
    {
    public:
        std::string fromPass;
        std::string toImage;
        uint32_t order;
    };

    class DepthStencilEdge : public Edge
    {
    public:
        std::string fromPass;
        std::string toImage;
        uint32_t order;
    };

    class RenderGraphImageNode : public SizeNode, public RenderGraphNode
    {
    public:
        RenderGraphImageNode() = default;
        RenderGraphImageNode(const std::string& name) : RenderGraphNode(name), m_targetOrderCounter(0), m_depthStencilOrderCounter(0) {}
        virtual RenderGraphImageNode& operator|=(const Texture& other) = 0;
        virtual RenderGraphImageNode& operator|=(const Target& other) = 0;
        virtual RenderGraphImageNode& operator|=(const DepthStencil& other) = 0;

        void addOutgoingEdge(TextureEdge* edge) {
            m_textureOutgoingEdges.push_back(edge);
        }

        void addIncomingEdge(TargetEdge* edge) {
            edge->order = m_targetOrderCounter++;
            m_targetIncomingEdges.push_back(edge);
        }

        void addIncomingEdge(DepthStencilEdge* edge) {
            edge->order = m_depthStencilOrderCounter++;
            m_depthStencilIncomingEdges.push_back(edge);
        }

        const std::vector<TextureEdge*>& getTextureOutgoingEdges() const {
            return m_textureOutgoingEdges;
        }

        const std::vector<TargetEdge*>& getTargetIncomingEdges() const {
            return m_targetIncomingEdges;
        }

        const std::vector<DepthStencilEdge*>& getDepthStencilIncomingEdges() const {
            return m_depthStencilIncomingEdges;
        }
        virtual Image* getImage() const = 0;

    private:
        std::vector<TextureEdge*> m_textureOutgoingEdges;
        std::vector<TargetEdge*> m_targetIncomingEdges;
        std::vector<DepthStencilEdge*> m_depthStencilIncomingEdges;
        uint32_t m_targetOrderCounter;
        uint32_t m_depthStencilOrderCounter;
    };
}
#include "./RenderGraph_RenderGraphBufferNode.h"
namespace FCT
{
    class RenderGraphPassNode;
    class TextureEdge : public Edge
    {
    public:
        TextureSize size;
        std::string fromImage;
        std::string toPass;
        ShaderStage stage;
    };

    class RenderGraphPassNode : public RenderGraphNode
    {
    public:
        RenderGraphPassNode(){}

        RenderGraphPassNode(std::string name) : RenderGraphNode(name)
        {

        }

        void addIncomingEdge(TextureEdge* edge) {
            m_textureIncomingEdges.push_back(edge);
        }

        void addOutgoingEdge(TargetEdge* edge) {
            m_targetOutgoingEdges.push_back(edge);
        }

        void addOutgoingEdge(DepthStencilEdge* edge) {
            m_depthStencilOutgoingEdges.push_back(edge);
        }

        const std::vector<TextureEdge*>& getTextureIncomingEdges() const {
            return m_textureIncomingEdges;
        }

        const std::vector<TargetEdge*>& getTargetOutgoingEdges() const {
            return m_targetOutgoingEdges;
        }

        const std::vector<DepthStencilEdge*>& getDepthStencilOutgoingEdges() const {
            return m_depthStencilOutgoingEdges;
        }
        void applyPassDesc(const PassDesc& desc) {
            m_clearInfo = desc.clear;
        }
        const EnablePassClear& getClearInfo() const {
            return m_clearInfo;
        }
    private:
        std::vector<TextureEdge*> m_textureIncomingEdges;
        std::vector<TargetEdge*> m_targetOutgoingEdges;
        std::vector<DepthStencilEdge*> m_depthStencilOutgoingEdges;
        EnablePassClear m_clearInfo;
    };
    struct PassSubmitEvent
    {
        std::string passName;
        RHI::CommandBuffer* cmdBuf;
    };
    class RenderGraph : private IEventSystem<EventSystemConfig::TriggerOnly>{
    private:
        struct ImageState {
            ImageLayout currentLayout = ImageLayout::undefined;
            PipelineStage lastStage = PipelineStage::topOfPipe;
            AccessFlag lastAccess = AccessFlag::none;
            std::string lastWriterGroup;
            bool needsBarrier = false;
        };
        struct BarrierInfo {
            Image* image;
            ImageLayout oldLayout;
            ImageLayout newLayout;
            PipelineStage srcStage;
            PipelineStage dstStage;
            AccessFlag srcAccess;
            AccessFlag dstAccess;
            ImageAspect aspect;
        };
        std::unordered_map<std::string, std::vector<BarrierInfo>> m_passGroupBarriers;
        std::map<std::string, std::set<std::string>> m_passGroupDependencies;

        Context* m_ctx;
        std::unordered_map<std::string, std::unique_ptr<RenderGraphImageNode>> m_imageNodes;
        std::unordered_map<std::string,RenderGraphPassNode> m_passNodes;
        UnionFind<std::string,char> m_passesUnions;
        std::vector<std::unique_ptr<Edge>> m_edges;
        std::unordered_map<std::string, Image*> m_allocatedImages;
        std::unordered_map<std::string, RHI::Pass*> m_allocatedPasses;
        RenderGraphImageNode* getOrCreateImageNode(const std::string& name, const Texture& texture);
        RenderGraphImageNode* getOrCreateImageNode(const std::string& name, const Target& target);
        RenderGraphImageNode* getOrCreateImageNode(const std::string& name, const DepthStencil& depthStencil);
        void createTextureEdge(const std::string& passName, const std::string& textureName, const Texture& texture);
        void createTargetEdge(const std::string& passName, const std::string& targetName, const Target& target);
        void createDepthStencilEdge(const std::string& passName, const std::string& depthStencilName, const DepthStencil& depthStencil);
        void simulatePassGroupExecution(const std::string& groupLeader,
                                   const std::vector<std::string>& groupMembers,
                                   std::unordered_map<Image*, ImageState>& imageStates);
        void simulateExecutionAndAnalyzeBarriers();
        std::vector<BarrierInfo> checkBarriersBeforePassGroup(const std::string& groupLeader,
                                                                const std::vector<std::string>& groupMembers,
                                                                const std::unordered_map<Image*, ImageState>& imageStates);

        void executeBarriers(RHI::CommandBuffer* cmdBuffer, const std::vector<BarrierInfo>& barriers);
        void addPass(const PassDesc& desc);
        /**
         * @cond CHINESE
         * @note 在compile调用时执行，遍历每个pass，
         *       然后遍历pass的texture边，
         *       如果TextureSize.type=Undefined，
         *       并且调用对应texture的SizeNode的isSizeDetermined为false，
         *       那么就调用SizeNode的
         *       bool unite(SizeNode* other, const Scale2D& scale = Scale2D())
         *       把texture和任意一个target或depthStencilunite起来，
         *       如果TextureSize.type=Relative，
         *       不管texture的size决定没有，
         *       把texture和（target或depth stencil 其中的一个）unite起来，
         *       并把传
         *       Scale2D(TextureSize.relativeWidth,TextureSize.relativeHeight)
         *       进去
         * @endcond
         */
        void resolveTextureSizes();
        /**
          * @cond CHINESE
          * @note 在compile时调用，用于将Pass分组到PassGroup中
          *       1. 遍历所有pass，首先pass先unite自己
          *       2. 遍历texture边对应的image和(任一target或depthStencil)是否相同大小
          *       3. 如果相同大小，找到把texture当target的pass，unite起来
          *       4. 遍历所有image，遍历他们的target边和depthstencil边，fromPass全部unite起来
          * @endcond
          */
        void groupPasses();

        void allocateResources();
        /**
        * @cond CHINESE
        * @note 创建所有RHI Pass并绑定对应的图片资源
        *       遍历所有pass节点，为每个pass创建RHI::Pass
        *       通过ImageNode的getImage()获取对应的Image并绑定到Pass
        *       Target按order绑定，DepthStencil直接绑定，Texture不绑定
        * @endcond
        */
        void createRHIPasses();
        void analyzePassGroupDependencies(const std::string& groupLeader, const std::vector<std::string>& groupMembers,
                                          std::map<std::string, std::set<std::string>>& dependencies) const;
        std::vector<std::string> topologicalSort(const std::map<std::string, std::set<std::string>>& dependencies) const;
        void analyzePassGroupBarriers();
        void computePassGroupExecutionOrder();
        std::unordered_map<std::string, RHI::PassGroup*> m_allocatedPassGroups; // 存储创建的PassGroup
        /**
          * @cond CHINESE
          * @note 创建PassGroup并设置Pass之间的依赖关系
          *       根据m_passesUnions的分组结果创建PassGroup
          *       通过TextureEdge分析Pass之间的依赖关系
          *       设置正确的PipelineStage和AccessFlags
          *       注意点:
          *       1.PassGroup内部在create的时候会把找不到的Pass*设置为external
          *       2.
          * @endcond
          */
        void createPassGroups();
    public:
        template<typename Func>
        SubscribeId subscribe(std::string passName,Func&& func)
        {
            SubscribeId subId = subscribe<PassSubmitEvent>([passName, func](const PassSubmitEvent& env)
            {
                if (env.passName == passName)
                {
                    func(env);
                }
            });
            return subId;
        }
        void unsubscribe(SubscribeId subscribeId)
        {
            IEventSystem<EventSystemConfig::TriggerOnly>::unsubscribe(subscribeId);
        }
        RenderGraph(Context* ctx);
        template<typename... Args>
        void addPass(std::string name,Args&&... args)
        {
            PassDesc desc(name);
            desc.processArgs(std::forward<Args>(args)...);
            addPass(desc);
        }
        void compile()
        {
            resolveTextureSizes();
            groupPasses();
            allocateResources();
            createRHIPasses();
            createPassGroups();
            computePassGroupExecutionOrder();
        }
        void executeAllPassGroups(RHI::CommandBuffer* cmdBuffer);
        RHI::Pass* getPass(const std::string& name) const;
    private:
        PipelineStage convertShaderStageToPipelineStage(ShaderStage stage) const;
        std::unordered_map<std::string, std::vector<std::string>> m_passGroupOrders;
        std::vector<std::string> m_passGroupExecutionOrder;
        void submitPassGroup(RHI::CommandBuffer* cmdBuffer,
                             const std::string& groupLeader);
    };

} // FCT

#endif //RENDERGRAPH_H
