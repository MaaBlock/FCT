//
// Created by Administrator on 2025/8/5.
//

#ifndef RENDERGRAPH_H
#define RENDERGRAPH_H
#include "./Format.h"
#include "../Base/UnionFind.h"

namespace FCT {
    class Context;
    class Device;
    struct Size
    {
        int32_t width;
        int32_t height;
        constexpr Size() noexcept : width(0), height(0) {}
        constexpr Size(int32_t width, int32_t height) : width(width), height(height) {}
    };
    struct Texture
    {
        std::string_view name;
        Size size;
        Format format;
        Samples samples;
        constexpr Texture() noexcept {}
        template<typename... Args>
        constexpr Texture(std::string_view name,Args&&... args) noexcept
            : name(name),format(Format::UNDEFINED),samples(Samples::sample_undefined), size() {
            processArgs(std::forward<Args>(args)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Size& other, Rest&&... rest) noexcept {
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
        constexpr void processArgs() noexcept {}
    };
    class Window;
    struct Target
    {
        std::string_view name;
        Window* wnd;
        Size size;
        Format format;
        Samples samples;
        constexpr Target() noexcept{}
        constexpr Target(Window* wnd) noexcept
        {
            this->wnd = wnd;
        }
        template<typename... Args>
        constexpr Target(std::string_view name, Args&&... args) noexcept
        {
            this->name = name;
            processArgs(std::forward<Args>(args)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Size& other, Rest&&... rest) noexcept
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
    struct DepthStencil
    {
        std::string_view name;
        Size size;
        Format format;
        Samples samples;
        constexpr DepthStencil() noexcept {}
        template<typename... Args>
        constexpr DepthStencil(std::string_view name, Args&&... args) noexcept
        {
            this->name = name;
            processArgs(std::forward<Args>(args)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const Size& other, Rest&&... rest) noexcept
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
    struct PassDesc
    {
        std::string_view name;
        Texture textures[RenderGraphConstVar::MAX_TEXTURE_COUNT];
        Target targets[RenderGraphConstVar::MAX_TARGET_COUNT];
        DepthStencil depthStencil;
        size_t m_textureCount;
        size_t m_targetsCount;
        constexpr PassDesc(std::string_view name) : name(name)
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
        constexpr void processArgs() noexcept {}
    };
    class RenderGraph {
    private:
        Context* m_ctx;
        Device* m_device;
        std::unordered_map<std::string,PassDesc> m_originPasses;
    public:
        RenderGraph(Context* ctx);
        ~RenderGraph();
        template<typename... Args>
        void addPass(std::string_view name,Args&&... args) {
            PassDesc pass(name);
            pass.processArgs(std::forward<Args>(args)...);
        }
        void complie()
        {

        }
    };

} // FCT

#endif //RENDERGRAPH_H
